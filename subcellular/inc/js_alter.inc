<?php
/**
 * @file
 * Add/Update/Delete javascript
 */

function subcellular_js_alter() {
  /*
   * Add javascript
   */

  /*
    $add_js = array(
    'localScript' => array( // Local script with minimum setup.
    'file'   => 'script.js', // Path to file, relative to /yourTheme/js/
    ),
    'cdnScript' => array( // CDN script w/ local fallback
    'object' => 'CDNscript', // javascript object to test for generating fallback from cdn
    'cdn'    => '//ajax.googleapis.com/ajax/libs/cdnScript.js',
    'file'   => 'fallback-script.js', // Path to file, relative to /yourTheme/js/
    ),
    'myScript'  => array( // default params
    'version'    => '1.2.3',
    'group'      => JS_THEME,
    'every_page' => TRUE,
    'object'     => 'MYScript', // javascript object to test for generating fallback from cdn
    'file'       => 'script.js', // Path to file, relative to /yourTheme/js/
    'weight'     => 5,
    ),
    );

    cellular_add_js($add_js);

   */

  /*

    /* Pass variable from drupal to js: */
//  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
  /* myVar will be available in Javascript as:
    <script>
    if (Drupal.settings.myVar.key == value){
    alert('Got it!');
    }
    </script>
   */
}
