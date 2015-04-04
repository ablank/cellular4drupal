<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Subcellular hook_css_alter().
 */
function subcellular_css_alter(&$css) {
  // Add stylesheets to theme.
    // Paths are relative to /yourTheme/build || build-test/css/
  // Extensions
  $add_css = array(
    'drupal' => array(
      'file' => 'drupal',
      'weight' => 10,
    ),
    'style' => array(
      'file' => 'style',
      'weight' => 11,
    ),
    'print' => array(
      'file' => 'print',
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

  // Remove module stylesheets.
  /* // Remove a single stylesheet set by a module:
   * 'stupidModule' => 'path/to/stupid.css'

   * // Remove multiple stylesheets set by a module:
   * 'moduleName' => array(
   * 'path/to/stupid.css',
   * 'path/to/more/stupid.css'
   * );
   */

  // Uncomment this block to remove module stylesheets.
  /* $exclude = array(
    'calendar' => 'css/calendar_multiday.css',
    'ctools' => 'css/ctools.css',
    'views' => 'css/views.css',
    'logintoboggan' => 'logintoboggan.css',
    'panels' => array(
    'css/panels.css',
    'plugins/layouts/flexible/flexible.css'
    ),
    );

    cellular_remove_css($css, $exclude);
   */
}
