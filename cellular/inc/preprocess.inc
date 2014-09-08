<?php
/**
 * @file
 * Template preprocess variables.
 */

/**
 * Cellular template_preprocess_html().
 */
function cellular_preprocess_html(&$vars) {
  cellular_html_attributes($vars);
  cellular_rdf($vars);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars);
}

/**
 * Cellular template_preprocess_node().
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];
  // Prevent empty datatype from rendering.
  unset($vars['title_attributes_array']['datatype']);
  // Push modified $css onto page.
  $vars['styles'] = drupal_get_css();

  $vars['title_attributes_array']['class'] = array('node-title');
  $vars['content_attributes_array']['class'] = array('node-content');

// Customize articles & blog posts:
  if ($node->type == 'article' || 'blog') {
// Get $author info:
    cellular_set_author($vars);
  }
}

/**
 * Cellular template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Set custom page templates for CCK Content (page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e. error page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
    "&copy; " . date("Y") . " " . $copyright : NULL;

  // Set classes for content & sidebars.
  cellular_sidebar_classes($vars);

  // Use page--error.tpl if http error status is returned.
  cellular_error_page($vars);

  // Dev.
  cellular_dev($vars);
}

/**
 * Cellular template_preprocess_region().
 */
function cellular_preprocess_region(&$vars) {

}

/**
 * Cellular template_preprocess_block().
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  $title_attributes = array();
  // Hide block titles in the headers region:
  if (($block->region == 'header')
  // || ($block->region == 'header_top')
  // || ($block->region == 'header_bottom')
  ) {
    $title_attributes['class'][] = 'hidden';
  }

  $vars['title_attributes'][] = $title_attributes;
}

/**
 * Cellular template_preprocess_comment().
 */
function cellular_preprocess_comment(&$vars) {
  $vars['title_attributes_array']['class'] = array('comment-title');
  $vars['content_attributes_array']['class'] = array('comment-content');

  $vars['submitted'] = t('Submitted by !username on !datetime', array(
    '!username' => $vars['author'],
    '!datetime' => $vars['created'],
  ));

  $vars['comment_wrapper'] = FALSE;
}

/**
 * Cellular template_ preprocess_username().
function cellular_preprocess_username(&$vars) {  
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }
}
 */
