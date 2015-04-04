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
 *
 * @param array $array
 *   Assosciative array of javascript data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_js(array $array, $cellular = FALSE) {

  $path = theme_get_setting('dev') == 0 ? 'build' : 'buildtest';
  $ext = $cellular === TRUE ? 'min.js' : theme_get_setting('dev') == 0 ? 'min.js' : 'js';

  foreach ($array as $script) {
    if (!empty($script)) {
// Set default attributes.
      $script['type'] = !empty($script['cdn']) ? 'external' : 'file';
      $script['group'] = !empty($script['group']) ? $script['group'] : JS_THEME;
      $script['every_page'] = !empty($script['every_page']) ? $script['every_page'] : TRUE;
      $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
// Conditional attributes.
      empty($script['version']) ? NULL : $script['version'] = $script['version'];

      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ? constant('CELLULAR_LIB') : path_to_theme() . "/$path";
        $data .= "/js/" . $script['file'] . ".$ext";
      }

      drupal_add_js($data, $script);
    }
  }
}

/**
 * Javascript fallback to local source if CDN fails.
 *
 * @param array $script
 *   Array of script attributes used to generate fallback.
 * @param  $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_js_fallback(array $script, $cellular = FALSE) {
// Only add the fallback if an object has been provided to test.
  if (!empty($script['object'])) {
    $attributes = array(
      'group' => $script['group'],
      'weight' => $script['weight'],
      'type' => 'inline',
      'every_page' => !empty($script['every_page']) ? $script['every_page'] : TRUE,
    );

    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? constant('CELLULAR_LIB') : path_to_theme();
    $fallback .= '/js/' . $script['file'];
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, $attributes);
  }
}

/**
 * Override existing $javascript sources.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 * @param array $script
 *   Array of attributes used to add javascript fallback.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_js_override(array &$javascript, array $script, $cellular = FALSE) {
// Only override if js is being called.
  if (!empty($javascript[$script['default']])) {
    $ojs = $script['default'];

    if (!empty($script['cdn'])) {
// If cdn is provided, set data to external source & call local fallback.
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
// Or set data to local file if no CDN.
      if (!empty($script['file'])) {
        $data = $cellular ? constant('CELLULAR_LIB') : path_to_theme();
        $data .= '/js/' . $script['file'];
      }
    }

// Default attributes.
    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['group'] = !empty($script['group']) ? $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = !empty($script['every_page']) ? $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
    $javascript[$ojs]['type'] = !empty($script['cdn']) ? 'external' : 'file';
    $javascript[$ojs]['preprocess'] = !empty($script['preprocess']) ? $script['preprocess'] : TRUE;
// Conditional attributes.
    empty($script['version']) ? NULL : $javascript[$ojs]['version'] = $script['version'];
  }
}
