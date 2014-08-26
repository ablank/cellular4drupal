<?php
/*
 *  @file
 * Utility functions to control javascript
 */

/*
 *  Add scripts from array
 */

function cellular_add_js($array, $cellular) {
  foreach ($array as $script) {
    if (!empty($script)) {
      // Set default attrs
      $script['type'] = isset($script['cdn']) ? 'external' : 'file';
      $script['version'] = isset($script['version']) ? $script['version'] : NULL;
      $script['group'] = isset($script['group']) ? $script['group'] : JS_THEME;
      $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
      $script['weight'] = isset($script['weight']) ? $script['weight'] : 0;


      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
        $data .= '/js/' . $script['file'];
      }

      drupal_add_js($data, $script);
    }
  }
}

/*
 *  Javascript fallback to local source if CDN fails
 */

function cellular_js_fallback($script, $cellular) {
  $attr = array(
    'group'      => $script['group'],
    'weight'     => $script['weight'] + 1,
    'type'       => 'inline',
    'every_page' => TRUE,
  );
  if (isset($script['object'])) {
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
    $fallback .= '/js/' . $script['file'];
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, $attr);
  }
}

/*
 *  Override javascript
 */

function cellular_js_override(&$javascript, $script, $cellular) {
  // only override if js is being called
  if (isset($javascript[$script['default']])) {
    // foreach ($override as $script) {

    $ojs = $script['default'];

    if (isset($script['cdn'])) {
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      $data = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
      $data .= isset($script['file']) ? '/js/' . $script['file'] : NULL;
    }

    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['version'] = isset($script['version']) ? $script['version'] : NULL;
    $javascript[$ojs]['group'] = isset($script['group']) ? $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = isset($script['weight']) ? $script['weight'] : 0;
    $javascript[$ojs]['type'] = isset($script['cdn']) ? 'external' : 'file';
  }
}
