<?php
/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js() {
  $ext = theme_get_setting('min_script') === 1 ? '.min.js' : '.js';

  // Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
  $js_plugins = array();
  theme_get_setting('backstretch') !== 1 ? NULL : $js_plugins['backstretch'] = TRUE;
  theme_get_setting('cellularui') !== 1 ? NULL : $js_plugins['cellularui'] = TRUE;
  theme_get_setting('flowtype') !== 1 ? NULL : $js_plugins['flowtype'] = TRUE;
  theme_get_setting('freetile') !== 1 ? NULL : $js_plugins['freetile'] = TRUE;
  theme_get_setting('jparallax') !== 1 ? NULL : $js_plugins['jparallax'] = TRUE;
  theme_get_setting('masonry') !== 1 ? NULL : $js_plugins['masonry'] = TRUE;
  theme_get_setting('smoove') !== 1 ? NULL : $js_plugins['smoove'] = TRUE;

  // Add scripts.
  $scripts['script'] = array(
    'file' => 'script' . $ext,
    'group' => JS_THEME,
    'weight' => 100,
  );
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
 *
 * @param array $array
 *  Assosciative array of javascript data.
 *
 * @param bool $cellular
 *  Reference cellular library if TRUE.
 */
function cellular_add_js($array, $cellular = FALSE) {
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
        $data = $cellular ? constant('CELLULAR_LIB') : path_to_theme();
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
 *  Array of script attributes used to generate fallback.
 *
 * @param bool $cellular
 *  Reference cellular library if TRUE.
 */
function cellular_js_fallback($script, $cellular = FALSE) {
  // Only add the fallback if an object has been provided to test.
  if (!empty($script['object'])) {
    $attributes = array(
      'group' => $script['group'],
      'weight' => $script['weight'] + 0.1,
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
 *  Associative array of javascripts.
 *
 * @param array $script
 *  Array of attributes used to add javascript fallback.
 *
 * @param bool $cellular
 *  Reference cellular library if TRUE.
 */
function cellular_js_override(&$javascript, $script, $cellular = FALSE) {
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
