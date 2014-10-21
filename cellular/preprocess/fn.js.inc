<?php
/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Pass variables to javascript object, used to call js if plugins are selected.
 */
function cellular_js() {
  $ext = theme_get_setting('min_script') === 1 ? '.min.js' : '.js';
  $scripts['script'] = array(
    'file' => 'script' . $ext,
    'group' => JS_THEME,
    'weight' => 100,
  );

  $js_plugins = array();
  theme_get_setting('backstretch') === 1 ? $js_plugins['backstretch'] = TRUE : NULL;
  theme_get_setting('cellularui') === 1 ? $js_plugins['cellularui'] = TRUE : NULL;
  theme_get_setting('flowtype') === 1 ? $js_plugins['flowtype'] = TRUE : NULL;
  theme_get_setting('freetile') === 1 ? $js_plugins['freetile'] = TRUE : NULL;
  theme_get_setting('jparallax') === 1 ? $js_plugins['jparallax'] = TRUE : NULL;
  theme_get_setting('masonry') === 1 ? $js_plugins['masonry'] = TRUE : NULL;
  theme_get_setting('smoove') === 1 ? $js_plugins['smoove'] = TRUE : NULL;

  if ($js_plugins) {
    // Add to Drupal.settings javascript.
    drupal_add_js(array('cellular' => $js_plugins), 'setting');
    // Scripts to add, relative to /yourTheme/js/
    $scripts['plugins'] = array(
      'file' => 'plugin' . $ext,
      'group' => JS_THEME,
      'weight' => 99,
    );
  }

  cellular_add_js($scripts);
}

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
      $script['group'] = isset($script['group']) ? $script['group'] : JS_THEME;
      $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
      $script['weight'] = isset($script['weight']) ? $script['weight'] : 0;
      // Conditional attributes.
      isset($script['version']) ? $script['version'] = $script['version'] : NULL;

      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ? constant('CELLULAR_LIB') : path_to_theme();
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

  // Only add the fallback if an object has been provided to test.
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
      $data = $cellular ? constant('CELLULAR_LIB') : path_to_theme();
      $data .= isset($script['file']) ? '/js/' . $script['file'] : NULL;
    }

    // Default attributes.
    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['group'] = isset($script['group']) ? $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = isset($script['weight']) ? $script['weight'] : 0;
    $javascript[$ojs]['type'] = isset($script['cdn']) ? 'external' : 'file';
    $javascript[$ojs]['preprocess'] = isset($script['preprocess']) ? $script['preprocess'] : TRUE;

    // Conditional attributes.
    isset($script['version']) ? $javascript[$ojs]['version'] = $script['version'] : NULL;
  }
}
