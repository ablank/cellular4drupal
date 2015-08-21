<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Implements hook_css_alter().
 */
function cellular_css_alter(&$css) {
  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  if (!empty($plugins)) {
    cellular_add_css($css, $plugins, TRUE);
  }
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_update_css($css);
  }
  // Check for minified or standard style extension.
  $ext = CELLULAR_CSS_EXT;
  // Add default stylesheets to theme, paths are relative to /YourTheme/css/
  $add_css = array(
    'drupal' => array(
      'file' => 'drupal' . $ext,
      'weight' => 10,
    ),
    'style' => array(
      'file' => 'style' . $ext,
      'weight' => 11,
    ),
    'print' => array(
      'file' => 'print' . $ext,
      'media' => 'print',
      'weight' => 100,
      'preprocess' => FALSE,
    ),
    'ie' => array(
      // Single stylesheet used to hack old internet explorer quirks.
      // Minimal support for deprecated breowsers is fine imo...
      'file' => 'ie' . $ext,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'weight' => 999,
    ),
  );
  cellular_add_css($css, $add_css);
}
