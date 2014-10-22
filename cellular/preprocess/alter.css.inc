<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Cellular hook_css_alter().
 *
 * @param array $css
 * Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_css_alter(&$css) {
  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') === 1) {
    cellular_jqueryui_update_css($css);
  }
  isset($plugins) ? cellular_add_css($css, $plugins, TRUE) : NULL;

  // Add stylesheets to theme.
  $add_css = array(
    // Paths are relative to /yourTheme/css/
    'drupal' => array(
      'file' => 'drupal.css',
      'weight' => 10,
    ),
    'style' => array(
      'file' => 'style.css',
      'weight' => 11,
    ),
    'print' => array(
      'file' => 'print.css',
      'media' => 'print',
      'weight' => 100,
      'preprocess' => FALSE,
    ),
    'ie' => array(
      // Single stylesheet used to hack old internet explorer quirks.
      // Minimal support for deprecated breowsers is fine imo...
      'file' => 'ie.css',
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'weight' => 999,
    ),
  );
  cellular_add_css($css, $add_css);
}
