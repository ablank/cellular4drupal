<?php
/**
 * @file
 * Template page preprocess functions.
 */

/**
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Set main_menu as full-tree or top-level as defined in settings.
  cellular_main_menu($vars);
  // Set classes for content & sidebar regions.
  cellular_test_sidebar($vars);
  // Link site name to frontpage.
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links.
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to page templates.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright info if provided.
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
  "&copy; " . date("Y") . " $copyright" : '';
  // Add template suggestion for custom content types(page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Automate error pages.
  cellular_error_page($vars);

  /* Work in progress... */
  // Panels everywhere page template suggestion.
  $panels_everywhere = variable_get('panels_everywhere_site_template', 0);
  if (!empty($panels_everywhere)) {
    $vars['theme_hook_suggestions'][] = 'page__panels_everywhere';
  }
}

/**
 * Implements template_preprocess_maintenance_page().
 *
 * Duplicate page variables for the maintenance page.
 */
function cellular_preprocess_maintenance_page(&$vars) {
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Set main_menu as full-tree or top-level as defined in settings.
  cellular_main_menu($vars);
  // Set classes for content & sidebar regions.
  cellular_test_sidebar($vars);
  // Link site name to frontpage.
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links.
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to page templates.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright info if provided.
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
  "&copy; " . date("Y") . " $copyright" : '';
  // Add template suggestion for custom content types(page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Automate error pages.
  cellular_error_page($vars);
}
