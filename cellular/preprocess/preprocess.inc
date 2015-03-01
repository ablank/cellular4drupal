<?php
/**
 * @file
 * Template preprocess variables.
 */

/**
 * Cellular template_preprocess_html().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_html(&$vars) {
  cellular_http_headers();
  cellular_html_attributes($vars);
  cellular_rdf($vars);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars);
}

/**
 * Cellular template_preprocess_node().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];

  $vars['title_attributes_array']['class'] = array('node-title');
  $vars['content_attributes_array']['class'] = array('node-content');

  // Customize articles & blog posts:
  if ($node->type === 'article' || 'blog') {
    // Get $author info:
    cellular_set_author($vars);
  }
}

/**
 * Cellular template_preprocess_page().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_page(&$vars) {
  // Add template suggestions for custom Content types(page--content-type.tpl.php)
  isset($vars['node']->type) ? $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type : NULL;

  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page--error.tpl if http error status is returned.
  cellular_error_page($vars);

  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e. error page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';
}

/**
 * Cellular template_preprocess_block().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  // Hide block titles in the headers region:
  switch ($block->region) {
    case 'header':
    case 'header-top':
    case 'header-bottom':

      $vars['title_attributes']['class'][] = 'element-invisible';

      break;
  }
}

/**
 * Cellular template_preprocess_comment().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_comment(&$vars) {
  // $vars['comment_wrapper'] = NULL;
  $vars['theme_hook_suggestions'][] = 'comment';
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';

  $vars['submitted'] = t('Submitted by !username on !datetime', array(
    '!username' => $vars['author'],
    '!datetime' => $vars['created'],
  ));


/* */
 }
 
/**
 * Cellular template_preprocess_comment_wrapper.
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_comment_wrapper(&$vars) {
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Cellular template_ preprocess_username().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_username(&$vars) {
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }
}
