<?php
/*
* @see file: src/preprocess/alter.css.inc
* Add/Update/Delete stylesheets.
*/
/**
<<<<<<< HEAD
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
=======
 * @file
 * hook_function overrides.
 * @author Adam Blankenship
 */

/**
 * Subcellular hook_css_alter().
 */
function subcellular_css_alter(&$css) {
  // Uncomment this block to add stylesheets to theme.
/*
  $add_css = array(
    'moarStyle' => array(// Minimum params:
      'file' => 'moar.css',
    ),
    'myStyle' => array(// Available params:
      'file' => 'my.awesome.css',
      'preprocess' => TRUE,
      'media' => 'all',
      'every_page' => TRUE,
      'group' => CSS_THEME,
      'weight' => 10
    ),
  );

  cellular_add_css($css, $add_css);
*/

  /* Remove stylesheets set by modules.
   * $key : Module name.
   * $value : Path relative to each module's directory.
   *
   * // Remove a single stylesheet:
   * 'stupidModule' => 'path/to/stupid.css'

   * // Remove multiple stylesheets:
   * 'stupidModule' => array(
   * 'path/to/stupid.css',
   * 'path/to/more/stupid.css'
   * );
   */

  // Remove module stylesheets.
/*
  $exclude = array(
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

/**
 * Subcellular hook_js_alter().
 */
function subcellular_js_alter() {
  // Pass a variable to js as Drupal.settings.myVar:
/*
  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
*/
  // Add javascript to theme.
/*
  $add_js = array(
    'myScript' => array(// Local script with minimum setup.
      'file' => 'myscript.js', // Path to file, relative to /yourTheme/js/
      'weight' => 10,
    ),
    'cdnScript' => array(// CDN script w/ local fallback
      'object' => 'CDNscript', // javascript object to test for generating fallback from cdn
      'cdn' => '//ajax.googleapis.com/ajax/libs/cdnScript.js',
      'file' => 'fallback-script.js', // Path to file from /yourTheme/js/
    ),
    'anotherScript' => array(// default params
      'file' => 'anotherScript.js', // Path to file, from /yourTheme/js/
    ),
  );

  cellular_add_js($add_js);
*/
}

/**
 * Subcellular template_preprocess_page().
 */
function subcellular_preprocess_page(&$vars) {

  // Do something with content type.
  /*
    if (isset($vars['node']) && $vars['node']->type == 'page') {

    }
   */

  // Do something with specific node.
  /*
    if (isset($vars['node']) && $vars['node']->nid === '40') {
    // Do things:
    };
   */
}

/**
 * Subcellular template_preprocess_html().
 */
function subcellular_preprocess_html(&$vars) {
  
}

/**
 * Subcellular template_preprocess_node().
 */
function subcellular_preprocess_node(&$vars) {
  
}

/**
 * Subcellular template_preprocess_region().
 */
function subcellular_preprocess_region(&$vars) {
  
}

/**
 * Subcellular template_preprocess_block().
 */
function subcellular_preprocess_block(&$vars) {
  
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
}
/*
* @see file: src/preprocess/alter.js.inc
* Add and update javascript.
*/
/**
<<<<<<< HEAD
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
=======
 * Subcellular template_preprocess_comment().
 */
function subcellular_preprocess_comment(&$vars) {
  
}
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
