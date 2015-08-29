<?php
/**
 * @file
 * SubCellular Starter Theme for Drupal 7.
 *
 * @author Adam Blankenship
 * 
 * @see http://live-cellular.gotpantheon.com
 * @see https://github.com/ablank/cellular
 */

/*
 * @see file: preprocess/_init.inc
 * Initialize constants & globals
 */

/* Cellular defined constants:
'CURRENT_THEME_PATH' : (string) Path to the active theme dirrectory
                    i.e.: CURRENT_THEME_PATH . '/css/lib/thing.css';
'CELLULAR_CSS_EXT' : (string) File extension for stylesheets (.min.css or .css).
                    default: .css
'CELLULAR_JS_EXT' : (string) File extension for javascript (.min.js or .js).
                    default: .js
'CELLULAR_INPUT_SIZE' : (int) Size of the default textfield input.
                        default: 20
// May convert to use Libraries module at some point...
'CELLULAR_LIB' : (string) Path to the Cellular library.
                  default: /sites/all/libraries/cellular

// These values can be overridden if necessary by implementing the php runkit,
 * i.e.:
 runkit_constant_redefine('CELLULAR_LIB', '/path/to/lib');
*/

/*
 * @see file: preprocess/alter.inc
 * Alter hooks for templates.
 */

/**
 * Implements hook_page_alter().
function subcellular_page_alter(&$vars) {
  $styles = array(
    'mystyle' => array(
      'file' => 'myStyle.css',
      'weight' => 10,
    ),
    'moarstyle' => array(
      // CELLULAR_CSS_EXT = .css || .min.css based on theme settings.
      'file' => 'moar' . CELLULAR_CSS_EXT,
      'weight' => 9,
    ),
    // Single stylesheet used to hack old internet explorer quirks.
    // Minimal support for deprecated breowsers is fine imo...
    'ie' => array(
      'file' => 'ie' . CELLULAR_CSS_EXT,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'group' => CSS_THEME,
      'weight' => 999,
    ),
    'print' => array(
      'file' => 'print' . CELLULAR_CSS_EXT,
      'media' => 'print',
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'weight' => 101,
    ),
  );

  $scripts = array(
    'script' => array(
      'cdn' => '//mycdnlink.com/myJavascript.js',
      'file' => 'myJavascript.js',
      'object' => 'myTestObject',
    ),
    'plugins' => array(
      // CELLULAR_CSS_EXT = .js || .min.js based on theme settings.
      'file' => 'myOtherScript' . CELLULAR_JS_EXT,
      'group' => JS_THEME,
      'weight' => 99,
    ),
  );
  
  // Attach styles to content.
  cellular_attach_css($vars['content'], $styles);
  // Attach scripts to content.
  cellular_attach_js($vars['content'], $scripts);

  //dpm($vars);
}
 */

/*
 * @see file: preprocess/alter_css.inc
 * Add/Update/Delete stylesheets.
 */

/**
 * Subcellular hook_css_alter().
 */
function subcellular_css_alter(&$css) {
  // Uncomment this block to add stylesheets to theme.
  /*
    $add_css = array(
    'myStyle' => array(// default params
    'file' => 'my.awesome.css',
    'preprocess' => TRUE,
    'media' => 'all',
    'every_page' => TRUE,
    'group' => CSS_THEME,
    'weight' => 10
    ),
    'otherStyle' => array(// minimum setup
    'file' => 'moar.css',
    ),
    );

    cellular_add_css($css, $add_css);
   */

  /* Remove stylesheets set by modules.
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

/*
 * @see file: preprocess/alter_js.inc
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
   // Add javascript to theme.
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
   */

  /* Add a new yepnope query with modernizr.
   * @see http://modernizr.com/docs/#load
   */
  /*
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
   */
}


/**
 * Implements template_preprocess_page().
function subcellular_preprocess_page(&$vars) {
    if (isset($vars['node']) && $vars['node']-type == 'page') {
   // Do something with content type.
    }  
    if (isset($vars['node']) && $vars['node']-nid === '40') {
   // Do something with specific node.
    }
}
 */ 

/**
 * Implements template_preprocess_html().
function subcellular_preprocess_html(&$vars) {
  
}
 */ 

/**
 * Implements template_preprocess_node().
function subcellular_preprocess_node(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_region().
function subcellular_preprocess_region(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_block().
function subcellular_preprocess_block(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_comment().
function subcellular_preprocess_comment(&$vars) {
  
}
 */ 