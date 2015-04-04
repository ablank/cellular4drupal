<?php
/**
 * @file
 * Add and update javascript.
 */

/**
 * Subcellular hook_js_alter().
 *
 * Path to file is (/build/ || /buildtest/) file extensions (.min.js || .js)
 * will be added automatically based on the 'dev' theme setting:
 * if(theme_get_setting('dev') == FALSE){
 *  "yourTheme/build/js/$script.min.js"
 * }
 * if(theme_get_setting('dev') == TRUE){
 *  "yourTheme/buildtest/js/$script.js"
 * }
 */
function subcellular_js_alter() {

  $add_js = array(
    /*
     // Plugins will be loaded automatically if selected in Drupal admin.
    'plugins' => array(
      'file' => "plugins",
      'weight' => 10,
    ),*/
    'cellularUI' => array(
      'file' => 'jquery.cellularUI',
      'group' => JS_THEME,
      'weight' => -10,
    ),
    'script' => array(
      'file' => "script",
      'weight' => 11,
    ),
  /*
    'anotherScript' => array(// default params
    'file' => "anotherScript", // Path to file, from /yourTheme/js/
    ),
    'cdn' => array(// CDN script w/ local fallback
    'object' => 'CDNscript',
    'cdn' => '//ajax.googleapis.com/ajax/libs/somescript.js',
    'file' => "somescript",
    ),
   */
  );

  cellular_add_js($add_js);
  // Pass a variable to js as Drupal.settings.myVar:
  /*
    drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
   */
}
