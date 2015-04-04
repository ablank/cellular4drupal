<?php
/*
* @see file: src/preprocess/alter.css.inc
* Add/Update/Delete stylesheets.
*/
/**
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
}
/*
* @see file: src/preprocess/alter.js.inc
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