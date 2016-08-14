<?php
/**
    * @file
    * Subcellular Starter Theme for Drupal 7.
    *
    * @author Adam Blankenship
    * 
    * @see http://live-cellular.gotpantheon.com
    * @see https://github.com/ablank/cellular
    */


/*
 * @see file: src/preprocess/_init.inc
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
 * @see file: src/preprocess/alter.inc
 * Alter hooks for templates.
 */

/**
 * Implements hook_page_alter().
function subcellular_page_alter(&$vars) {
 
}
 */


/*
 * @see file: src/preprocess/alter_css.inc
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


/*
 * @see file: src/preprocess/alter_js.inc
 * Add and update javascript.
 */

/**
 * Yoga hook_js_alter().
 */
function subcellular_js_alter(&$javascript) {
  // 
}


/**
 * Implements template_preprocess_html().
 */
function subcellular_preprocess_html(&$vars) {
  /*
    // Set stylesheets
    $styles = array(
    'mystyle' => array(
    'file' => 'myStyle.css',
    'weight' => 10,
    ),
    'moarstyle' => array(
    'file' => 'moar.css',
    'weight' => 9,
    ),
    );
    // Set scripts.
    $scripts = array(
    'script' => array(
    'cdn' => '//mycdnlink.com/myJavascript.js',
    'file' => 'myJavascript.js',
    'object' => 'myTestObject',
    ),
    'plugins' => array(
    'file' => 'myOtherScript.js',
    'group' => JS_THEME,
    'weight' => 99,
    ),
    );

    // Add styles to page.
    cellular_add_css($styles);
    // Add scripts to page.
    cellular_attach_js($scripts);

    // Pass a variable to js as Drupal.settings.myVar:
    // drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');

    //dpm($vars);

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