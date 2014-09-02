<?php

/**
 * @file
 * Template preprocess variables.
 */

/**
 * template_preprocess_html()
 */
function cellular_preprocess_html(&$vars) {
  global $language, $theme_path;

  cellular_html_attributes($vars, $language);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars);
}

/**
 * template_preprocess_node()
 */
function cellular_preprocess_node(&$vars) {
  $vars['hook'] = 'node';
  $node = $vars['node'];

  $vars['title_attributes_array']['class'] = array('node-title');
  $vars['content_attributes_array']['class'] = array('node-content');

// Customize articles & blog posts:
  if ($node->type == 'article' || 'blog') {
// Get $author info:
    $uid = user_load($node->uid);
    $safe_value = "['LANGUAGE_NONE'][0]['safe_value']";
    $author = array(
      'name' => l($node->name, 'user/' . $node->uid),
      'description' => isset($author->field_description[$safe_value]) ?
        '<div class="author-description">' . $uid->field_description[$safe_value] . '</div>' : NULL,
      'image' => !empty($uid->picture->uri) ? theme('image_style', array(
          // 'style_name' => 'blog-author-image',
          'path' => $node->picture->uri,
          'width' => NULL,
          'height' => NULL,
          'alt' => t('User') . ' ' . $node->name,
          'title' => t('User') . ' ' . $node->name,
          'attributes' => array('class' => 'author-image'),
        )) : NULL,
    );

// Return $author:
    $vars['author'] = $author['image'] . $author['name'] . $author['description'];
  }
}

/**
 * template_preprocess_page()
 */
function cellular_preprocess_page(&$vars) {
  // Set custom page templates for CCK Content (page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set main_menu as full-tree or top-level as defined in settings:
  $vars['main_menu'] = cellular_main_menu($vars);
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
    "&copy; " . date("Y") . " " . $copyright : NULL;
  // Set search block variable for addition to templates:
  $vars['page']['search_box'] = drupal_get_form('search_form');

  // Set classes for content & sidebars.
  cellular_sidebar_classes($vars);

  // Use page--error.tpl if http error status is returned.
  cellular_error_page($vars);

  // Dev.
  // cellular_dev($vars);
}

/**
 * template_preprocess_region()
 */
function cellular_preprocess_region(&$vars) {

}

/**
 * template_preprocess_block()
 */
function cellular_preprocess_block(&$vars) {
  $vars['hook'] = 'block';
  $block = $vars['block'];
  $vars['title'] = isset($block->subject) ? $block->subject : NULL;
  $vars['classes_array'] = array('block');
  $vars['title_attributes_array'] ['class'] = array('block-title');
  $vars['content_attributes_array']['class'] = array('block-content');

  // Hide block titles in the headers region:
  if (($block->region == 'header')
  // || ($block->region == 'header_top')
  // || ($block->region == 'header_bottom')
  ) {
    $vars['title_attributes_array']['class'] = array('hidden');
  }
}

/**
 * template_preprocess_comment()
 */
function cellular_preprocess_comment(&$vars) {
  $vars['hook'] = 'comment';

  $vars['title_attributes_array']['class'] = array('comment-title');
  $vars['content_attributes_array']['class'] = array('comment-content');

  $vars['submitted'] = t('Submitted by !username on !datetime', array(
    '!username' => $vars['author'],
    '!datetime' => $vars['created'],
  ));

  $vars['comment_wrapper'] = FALSE;
}

/**
 * template_ preprocess_username()
 */
function cellular_preprocess_username(&$vars) {
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }
}
