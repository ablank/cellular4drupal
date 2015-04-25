<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Implements hook_css_alter().
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_css_alter(&$css) {
  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  $ext = theme_get_setting('min_style') == 1 ? '.min.css' : '.css';
  // Add stylesheets to theme.
  // Paths are relative to /yourTheme/css/
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

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_update_css($css);
  }
  !empty($plugins) ? cellular_add_css($css, $plugins, TRUE) : NULL;
}
