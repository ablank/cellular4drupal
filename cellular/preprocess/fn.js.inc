<?php
/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Attach scripts to a render array, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * an 'object' key value is provided.
 *
 * @param array $array
 *   Assosciative array of javascript data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_attach_js(&$vars, $array, $cellular = FALSE) {
  $type = 'file';
  foreach ($array as $script) {
    // Test if local or external source is provided.
    if (!empty($script['cdn'])) {
      $type = 'external';
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    elseif (!empty($script['file'])) {
      $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH;
      $data .= '/js/' . $script['file'];
    }
    else {
      $data = $script['data'];
    }
    // Set script attributes.
    if (!empty($script['type'])) {
      $type = $script['type'];
    }

      $script['data'] = $data;
      $script['type'] = $type;
      $script['scope'] = !empty($script['scope']) ? $script['scope'] : 'header';
      $script['group'] = !empty($script['group']) ? $script['group'] : JS_THEME;
      $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
      $script['preprocess'] = !empty($script['preprocess']) ? $script['preprocess'] : TRUE;
      $script['cache'] = !empty($script['cache']) ? $script['cache'] : TRUE;
      $script['defer'] = !empty($script['defer']) ? $script['defer'] : FALSE;
      $script['every_page'] = !empty($script['every_page']) ? $script['every_page'] : TRUE;
      empty($script['version']) ? NULL : $script['version'] = $script['version'];

      $vars['#attached']['js'][$data] = $script;
  }
}

/**
 * Add scripts from an array, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * an 'object' key value is provided.
 *
 * @param array $array
 *   Assosciative array of javascript data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_js($array, $cellular = FALSE) {
  foreach ($array as $script) {
    $type = 'file';
    // Test if local or external source is provided.
    if (!empty($script['cdn'])) {
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    elseif (!empty($script['file'])) {
      $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH;
      $data .= '/js/' . $script['file'];
    }
    else {
      $data = $script['data'];
    }
    // Set script attributes.
    if(!empty($script['type'])){
      $type = $script['type'];
    }
    elseif(!empty($script['cdn'])){
      $type = 'external';
    }

    $script['type'] = $type;
    $script['scope'] = !empty($script['scope']) ? $script['scope'] : 'header';
    $script['group'] = !empty($script['group']) ? $script['group'] : JS_THEME;
    $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
    $script['every_page'] = !empty($script['every_page']) ? $script['every_page'] : TRUE;
    $script['preprocess'] = !empty($script['preprocess']) ? $script['preprocess'] : TRUE;
    $script['cache'] = !empty($script['cache']) ? $script['cache'] : TRUE;
    $script['defer'] = !empty($script['defer']) ? $script['defer'] : FALSE;
    empty($script['version']) ? NULL : $script['version'] = $script['version'];

    drupal_add_js($data, $script);
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
function cellular_js_fallback($script, $cellular = FALSE) {
  // Only add the fallback if an object has been provided to test.
  if (!empty($script['object'])) {
    $attributes = array(
      'type' => 'inline',
      'group' => !empty($script['group']) ? $script['group'] : JS_THEME,
      'weight' => !empty($script['weight']) ? $script['weight'] + 0.1 : 1,
      'every_page' => !empty($script['every_page']) ? $script['every_page'] : TRUE,
    );
    // Construct the fallback script.
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH;
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
function cellular_js_override(&$javascript, $script, $cellular = FALSE) {
  // Only override if js is being called.
  if (isset($javascript[$script['default']])) {
    $ojs = $script['default'];
    if (!empty($script['cdn'])) {
      // If cdn is provided, set data to external source & call local fallback.
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      // Use local source if no CDN is used.
      if (!empty($script['file'])) {
        $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH;
        $data .= '/js/' . $script['file'];
      }
    }
    // Set the script attributes.
    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['type'] = !empty($script['cdn']) ? 'external' : 'file';
    $javascript[$ojs]['scope'] = !empty($script['scope']) ? $script['scope'] : $javascript[$ojs]['scope'];
    $javascript[$ojs]['group'] = !empty($script['group']) ? $script['group'] : $javascript[$ojs]['group'];
    $javascript[$ojs]['every_page'] = !empty($script['every_page']) ? $script['every_page'] : $javascript[$ojs]['every_page'];
    $javascript[$ojs]['weight'] = !empty($script['weight']) ? $script['weight'] : $javascript[$ojs]['weight'];
    $javascript[$ojs]['preprocess'] = !empty($script['preprocess']) ? $script['preprocess'] : $javascript[$ojs]['preprocess'];
    $javascript[$ojs]['cache'] = !empty($script['cache']) ? $script['cache'] : $javascript[$ojs]['cache'];
    $javascript[$ojs]['defer'] = !empty($script['defer']) ? $script['defer'] : $javascript[$ojs]['defer'];
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
  $dir = $GLOBALS['base_url'] . '/' . CURRENT_THEME_PATH;
  $query = '';

  foreach ($tests as $test) {
    $query .= "{\n";
    $query .= "test : " . $test['test'] . ",\n";
    empty($test['yep']) ? NULL : $query .= "yep : ['" . $dir . $test['yep'] . "'],\n";
    empty($test['nope']) ? NULL : $query .= "nope : ['" . $dir . $test['nope'] . "'],\n";
    empty($test['both']) ? NULL : $query .= "both : ['" . $dir . $test['both'] . "'],\n";
    empty($test['complete']) ? NULL : $query .= "complete : function(){\n" . $test['complete'] . "},\n";
    $query .= "},\n";
  }

  $modernizr = "Modernizr.load([\n$query]);\n";

  drupal_add_js($modernizr, array(
    'type' => 'inline',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js_settings() {
  // Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
  $js_plugins = array();
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = TRUE : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = TRUE : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = TRUE : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = TRUE : NULL;
  theme_get_setting('masonry') == 1 ? $js_plugins['masonry'] = TRUE : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = TRUE : NULL;

  return $js_plugins;
}
