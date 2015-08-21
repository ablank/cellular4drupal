<?php
/**
 * @file
 * Add and update javascript.
 */

/**
 * Subcellular hook_js_alter().
 */
function subcellular_js_alter(&$javascript) {
  // 
  /* Pass a variable to js as Drupal.settings.myVar: */
  /*
    drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
   */
  /*
   * Add javascript to theme.
   */
  $add_js = array(
    // Local script with minimum setup.
    'localScript' => array(
      // Path to the file, relative to /yourTheme/js/
      'file' => 'myscript.js',
      'weight' => 10,
    ),
    'cdnScript' => array(
      'cdn' => '//ajax.googleapis.com/ajax/libs/cdnScript.js',
    ),
    // Add a script using all available parameters.
    'anotherScript' => array(
      // URL of the external script.
      'cdn' => '//ajax.googleapis.com/ajax/libs/anotherScript.js',
      // DOM object to test for generating fallback.
      'object' => 'Ascript',
      // Path to the file, relative to /yourTheme/js/
      'file' => 'anotherScript.js',
      'group' => JS_THEME,
      'every_page' => TRUE,
      'weight' => 1,
      'version' => '1.0.9',
    ),
  );

  cellular_add_js($add_js);

  /* Add a new yepnope query with modernizr.
   * @see http://modernizr.com/docs/#load
   */
  /*
   */
  // File paths are relative to the active theme's root directory.
  $css_dir = '/css/';
  $js_dir = '/js/';
  // File extensions based on theme settings to minify css or js.
  $ext = cellular_ext();

  $tests = array(
    // Test browser SVG support.
    'svg' => array(
      'test' => 'Modernizr.svg',
      'yep' => $css_dir . 'icons-svg' . $ext['css'],
      'nope' => $css_dir . 'icons-png' . $ext['css'],
      //'both' => '/path/to/some/file' . $ext['js'],
      //'complete' => 'window.location.assign('.$GLOBALS['base_url'].')',
    ),
  );

  cellular_modernizr($tests);
  /////
}
