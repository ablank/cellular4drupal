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
  cellular_js_vars();

  // Scripts to add, relative to /yourTheme/js/
  $scripts['script'] = array(
    'file' => 'script.js',
    'group' => JS_THEME,
    'weight' => 100,
  );
  cellular_add_js($scripts);

  // Get array of js plugins to add.
  $js_plugins = cellular_plugins_js();

  // Add Modernizr & query based on theme settings.
  theme_get_setting('modernizr') == 1 ? cellular_modernizr() : NULL;

  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    $jquery = cellular_jquery_info();
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
    // Add jQuery.migrate to support older plugins if v >= 1.9
    if ($jquery['version'] !== '1.8.24') {
      $js_plugins['migrate'] = array(
        'version' => '1.2.1',
        'file' => 'plugins/jquery.migrate.min.js',
        'group' => JS_LIBRARY,
        'weight' => -96,
      );
    }
  }

  // Add js after override.
  cellular_add_js($js_plugins, TRUE);

  // Dev.
  // cellular_dev($javascript);
}
