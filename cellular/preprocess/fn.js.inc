<?php
/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Add array of javascripts to $javascript, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * the 'object' value is provided.
 */
function cellular_add_js($array, $cellular = FALSE) {
  foreach ($array as $script) {
    if (!empty($script)) {
      // Set default attributes.
      $script['type'] = isset($script['cdn']) ? 'external' : 'file';
      $script['version'] = isset($script['version']) ? $script['version'] : NULL;
      $script['group'] = isset($script['group']) ? $script['group'] : JS_THEME;
      $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
      $script['weight'] = isset($script['weight']) ? $script['weight'] : 1;

      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ?
        constant('CELLULAR_LIB') : path_to_theme();
        $data .= '/js/' . $script['file'];
      }

      drupal_add_js($data, $script);
    }
  }
}

/**
 * Javascript fallback to local source if CDN fails.
 */
function cellular_js_fallback($script, $cellular = FALSE) {
  $attributes = array(
    'group' => $script['group'],
    'weight' => $script['weight'] + 0.1,
    'type' => 'inline',
    'every_page' => isset($script['every_page']) ? $script['every_page'] : TRUE,
  );
  if (isset($script['object'])) {
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? constant('CELLULAR_LIB') : path_to_theme();
    $fallback .= '/js/' . $script['file'];
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, $attributes);
  }
}

/**
 * Override existing $javascript sources.
 */
function cellular_js_override(&$javascript, $script, $cellular = FALSE) {
  // Only override if js is being called.
  if (isset($javascript[$script['default']])) {
    $ojs = $script['default'];

    if (isset($script['cdn'])) {
      // If cdn is provided, set data to external source & call local fallback.
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      // Or set data to local file if no CDN.
      // Set path relative to $cellular_lib or $theme path depending on context.
      $data = $cellular ?
      constant('CELLULAR_LIB') : path_to_theme();
      $data .= isset($script['file']) ? '/js/' . $script['file'] : NULL;
    }

    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['version'] = isset($script['version']) ?
    $script['version'] : NULL;
    $javascript[$ojs]['group'] = isset($script['group']) ?
    $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = isset($script['every_page']) ?
    $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = isset($script['weight']) ?
    $script['weight'] : 0;
    $javascript[$ojs]['type'] = isset($script['cdn']) ?
    'external' : 'file';
    $javascript[$ojs]['preprocess'] = isset($script['preprocess']) ?
    $script['preprocess'] : FALSE;
  }
}
