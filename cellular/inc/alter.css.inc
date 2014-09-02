<?php

/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Cellular hook_css_alter().
 */
function cellular_css_alter(&$css) {
  // Show $css before alteration.
  cellular_dev($css);

// Add stylesheets to theme.
  $add_css = array(
  // Paths are relative to /yourTheme/css/
    'drupal' => array(
      'file' => 'drupal.css',
      'weight' => 1,
    ),
    'style' => array(
      'file' => 'style.css',
      'weight' => 2,
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

  // Add stylesheets for js plugins (including jQueryUI).
  cellular_add_plugin_css($css);

  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  // Push styles to page.
  // $css = drupal_get_css($css);
  // Show $css after alteration.
  cellular_dev($css);
}
