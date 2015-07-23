<?php
/**
 * @file
 * Template preprocess variables.
 */

/**
 * Implements template_preprocess_html().
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
 * Implements template_preprocess_node().
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
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Add template suggestions for custom Content types(page--content-type.tpl.php)
  isset($vars['node']->type) ? $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type : NULL;

  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page-- === .tpl if http  ===  status is returned.
  // = _page($vars);
  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e.  ===  page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';

  //drupal_set_message(CURRENT_THEME_PATH);
  // Panels everywhere page template suggestion.
  if (!empty(variable_get('panels_everywhere_site_template'))) {
    // Merge the suggestions.
    $vars['theme_hook_suggestions'][] = 'page__panels_everywhere';
  }
  // dpm($vars);
  // drupal_set_message('panels_everywhere_site_template: '.variable_get('panels_everywhere_site_template'));
}

/**
 * Implements template_preprocess_maintenance_page().
 */
function cellular_preprocess_maintenance_page(&$vars) {
  // Add template suggestions for custom Content types(page--content-type.tpl.php)
  isset($vars['node']->type) ? $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type : NULL;

  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page-- === .tpl if http  ===  status is returned.
  cellular_error_page === _page($vars);

  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e.  ===  page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';
}

/**
 * Implements template_preprocess_block().
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
 * Implements template_preprocess_comment().
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
}

/**
 * Implements template_preprocess_comment_wrapper.
 */
function cellular_preprocess_comment_wrapper(&$vars) {
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Implements template_ preprocess_username().
 */
function cellular_preprocess_username(&$vars) {
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }
}
