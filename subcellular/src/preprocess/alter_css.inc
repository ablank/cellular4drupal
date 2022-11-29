<?php

/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Yoga hook_css_alter().
 */
function subcellular_css_alter(&$css) {
  /* Remove stylesheets:
   * $key : Module name.
   * $value : Path relative to each module's directory.
   *
   * // Remove a single stylesheet set by a module:
   * 'stupidModule' => 'path/to/stupid.css'

   * // Remove multiple stylesheets set by a module:
   * 'stupidModule' => array(
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
