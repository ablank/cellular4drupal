<?php
/**
 * @file
 * Cellular stylesheet functions.
 */

/**
 * Add array of stylesheets to $css, using a CDN if provided.
 */
function cellular_add_css(&$css, $array, $cellular = FALSE) {
  foreach ($array as $style) {
    if (!empty($style)) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      elseif (isset($style['file'])) {
        $data = $cellular === TRUE ?
          constant('CELLULAR_LIB') : path_to_theme();
        $data .= '/css/' . $style['file'];
      }
      if (isset($data)) {
        $style['data'] = $data;
        $style['preprocess'] = isset($style['preprocess']) ?
          $style['preprocess'] : TRUE;
        $style['every_page'] = isset($style['every_page']) ?
          $style['every_page'] : TRUE;
        $style['group'] = isset($style['group']) ?
          $style['group'] : CSS_THEME;
        $style['weight'] = isset($style['weight']) ?
          $style['weight'] : 1;
        $style['type'] = isset($style['cdn']) ?
          'external' : 'file';
        $style['media'] = isset($style['media']) ?
          $style['media'] : 'all';
        $style['browsers'] = isset($style['browsers']) ?
          $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);

        $css[$data] = $style;
      }
    }
  }
}

/**
 * Removes array of stylesheets from $css.
 */
function cellular_remove_css(&$css, $exclude) {

  foreach ($exclude as $module => $stylesheet) {
    // Remove multiple stylesheets attached by module.
    if (is_array($stylesheet)) {
      foreach ($stylesheet as $style) {
        unset($css[drupal_get_path('module', $module) . '/' . $style]);
      }
    }
    // Remove individual stylesheet.
    else {
      unset($css[drupal_get_path('module', $module) . '/' . $stylesheet]);
    }
  }
}

/**
 * Overrides default css values.
 */
function cellular_css_override(&$css, $style, $cellular = FALSE) {
  $ocss = $style['default'];
  // Only override if style is being called.
  if (isset($css[$ocss])) {
    if (isset($style['cdn'])) {
      // If cdn is provided, set data to external source & call local fallback.
      $data = $style['cdn'];
    }
    else {
      // Or set data to local file.
      $data = path_to_theme() . 'css/' . $style['file'];
    }

    $css[$ocss]['data'] = $data;
    $css[$ocss]['group'] = isset($style['group']) ?
      $style['group'] : CSS_DEFAULT;
    $css[$ocss]['every_page'] = isset($style['every_page']) ?
      $style['every_page'] : TRUE;
    $css[$ocss]['weight'] = isset($style['weight']) ?
      $style['weight'] : 0;
    $css[$ocss]['type'] = isset($style['cdn']) ?
      'external' : 'file';
    $css[$ocss]['preprocess'] = isset($style['preprocess']) ?
      $style['preprocess'] : FALSE;
  }
}

/**
 * Add stylesheets used with javascript plugins, including jQuery.ui.
 */
function cellular_plugin_css() {
  // Plugins available through cellular, styles added based on theme settings.
  // $plugin_css paths are relative to /libraries/cellular/css/
  $plugin_css = array(
    'prism' => theme_get_setting('prism') == 1 ?
    array(
      'file' => 'prism.css',
      'weight' => 1,
      'preprocess' => FALSE,
    ) : NULL,
    'reveal' => theme_get_setting('reveal') == 1 ?
    array(
      'file' => 'reveal/reveal.min.css',
      'weight' => 1,
      'preprocess' => FALSE,
    ) : NULL,
  );

  return $plugin_css;
}
