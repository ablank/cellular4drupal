<?php
/**
 * @file
 * Add/Update/Delete javascript.
 */

/**
 * Implements hook_js_alter().
 */
function cellular_js_alter(&$javascript) {
  // Pass variables from drupal to js.
  cellular_js();

  // Get array of js plugins to add.
  $js_plugins = cellular_plugins_js();

  // Add Modernizr & query based on theme settings.
  theme_get_setting('modernizr') == 1 ? cellular_modernizr_default() : NULL;

  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
  }

  // Add js after override.
  cellular_add_js($js_plugins, TRUE);

  // Dev.
  // cellular_dev($javascript);
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js() {
  $ext = theme_get_setting('min_script') == 1 ? '.min.js' : '.js';

  // Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
  $js_plugins = array();

  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = TRUE : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = TRUE : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = TRUE : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = TRUE : NULL;
  theme_get_setting('masonry') == 1 ? $js_plugins['masonry'] = TRUE : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = TRUE : NULL;

  // Add to Cellular plugin settings to Drupal.settings.
  drupal_add_js(array('cellular' => $js_plugins), 'setting');

  $scripts = array();
  // Add script by extension. The minified source should compile ALL js in
  // /yourTheme/js/ into script.min.js.
  // Add Cellular UI
  if (theme_get_setting('cellularui') == 1) {
    $scripts['cellularui'] = array(
      'object' => 'cellular',
      'file' => 'cellular-ui/jquery.cellular-ui' . $ext,
      'weight' => 98,
    );
    // Add to Drupal.settings.
    drupal_add_js(array('cellular' => array('cellularui' => TRUE)), 'setting');
  }
  // Add plugins.js if plugins are set.
  if ($js_plugins || theme_get_setting('cellularui') == 1) {
    $scripts['plugins'] = array(
      'file' => 'plugins' . $ext,
      'group' => JS_DEFAULT,
      'weight' => 99,
    );
  }
  // Add script.js.
  $scripts['script'] = array(
    'file' => 'script' . $ext,
    'group' => JS_THEME,
    'weight' => 100,
  );

  cellular_add_js($scripts);
}
