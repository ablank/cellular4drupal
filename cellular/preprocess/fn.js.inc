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
function cellular_add_js($array,  $cellular = FALSE) {
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
        $data = $cellular ? constant('CELLULAR_LIB') : cellular_theme_path();
        $data .= '/js/' . $script['file'];
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
function cellular_js_fallback($script,  $cellular = FALSE) {
// Only add the fallback if an object has been provided to test.
  if (!empty($script['object'])) {
    $attributes = array(
      'group' => $script['group'],
      'weight' => $script['weight'] + 0.1,
      'type' => 'inline',
      'every_page' => !empty($script['every_page']) ? $script['every_page'] : TRUE,
    );

    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? constant('CELLULAR_LIB') : cellular_theme_path();
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
function cellular_js_override(&$javascript, $script,  $cellular = FALSE) {
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
        $data = $cellular ? constant('CELLULAR_LIB') : cellular_theme_path();
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

/**
 * Build modernizr query and add script inline on page.
 *
 * @param array $tests
 *   Array of arrays used to build modernizr tests.
 *   $tests['testName'] = array(
 *   'test',
 *   'yep',
 *   'nope',
 *   'both',
 *   'complete',
 *   );.
 */
function cellular_modernizr($tests) {
// $base_url needs to be added to set the correct path.
  $dir = $GLOBALS['base_url'] . '/' . cellular_theme_path();
  $query = '';

  foreach ($tests as $test) {
    if (empty($test['test'])) {
      return;
    }
    else {
      $query .= "{\n";
      $query .= "test : " . $test['test'] . ",\n";
      empty($test['yep']) ? NULL : $query .= "yep : ['" . $dir . $test['yep'] . "'],\n";
      empty($test['nope']) ? NULL : $query .= "nope : ['" . $dir . $test['nope'] . "'],\n";
      empty($test['both']) ? NULL : $query .= "both : ['" . $dir . $test['both'] . "'],\n";
      empty($test['complete']) ? NULL : $query .= "complete : function(){\n" . $test['complete'] . "},\n";

      // $query .= "nope : ['" . $test['nope'] . "'],\n";
      $query .= "},\n";
    }
  }

  $query = "Modernizr.load([\n$query]);\n";

  drupal_add_js($query, array(
    'type' => 'inline',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}
