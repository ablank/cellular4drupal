<?php
/**
 * @file
 * Add/Update/Delete javascript.
 */

/**
 * Cellular hook_js_alter().
 */
function cellular_js_alter(&$javascript) {
  // Pass variables from drupal to js.
  cellular_js();

  // Get array of js plugins to add.
  $js_plugins = cellular_plugins_js();

  // Add Modernizr & query based on theme settings.
  theme_get_setting('modernizr') === 1 ? cellular_modernizr() : NULL;

  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') === 1) {
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
  }

  // Add js after override.
  cellular_add_js($js_plugins, TRUE);

  // Dev.
  // cellular_dev($javascript);
}
