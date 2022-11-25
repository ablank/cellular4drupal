<?php
/**
 * @file
 * Add and update javascript.
 */

/**
 * Implements hook_js_alter().
 */
function subcellular_js_alter(&$javascript) {
  /*
    // Override misc. js
    $override = array();
    if (module_exists('some_module')) {
    $override['some_module'] = array(
    'default' => drupal_get_path('module', 'some_module') . '/path/to/somescript.js',
    'file' => CURRENT_THEME_PATH . '/path/to/replacement.js',
    );
    }

    foreach ($override as &$js) {
    $js['group'] = JS_LIBRARY;
    cellular_js_override($javascript, $js);
    }
   */
}
