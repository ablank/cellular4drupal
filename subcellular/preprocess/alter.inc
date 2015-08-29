<?php
/**
 * @file
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
