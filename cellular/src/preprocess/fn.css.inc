<?php
/**
 * @file
 * Cellular stylesheet functions.
 */

/**
 * Add array of stylesheets to $css, using a CDN if provided.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $array
 *   Associative array of stylesheets data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_css(array &$css, array $array, $cellular = FALSE) {

  $path = theme_get_setting('dev') == 0 ? 'build' : 'buildtest';
  $ext = $cellular === TRUE ? 'min.css' : theme_get_setting('dev') == 0 ? 'min.css' : 'css';

  foreach ($array as $style) {
    if (!empty($style)) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      elseif (isset($style['file'])) {
        $data = $cellular === TRUE ? constant('CELLULAR_LIB') : path_to_theme() . "/$path";
        $data .= '/css/' . $style['file'] . ".$ext";
      }
      if (!empty($data)) {
        $style['data'] = $data;
        $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
        $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
        $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
        $style['weight'] = isset($style['weight']) ? $style['weight'] : 1;
        $style['type'] = isset($style['cdn']) ? 'external' : 'file';
        $style['media'] = isset($style['media']) ? $style['media'] : 'all';
        $style['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);

        $css[$data] = $style;
      }
    }
  }
}

/**
 * Removes array of stylesheets from $css.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $exclude
 *   Array of stylesheets to remove.
 */
function cellular_remove_css(array &$css, array $exclude) {
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
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $style
 *   Array of stylesheet data used to override default.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_override_css(array &$css, array $style, $cellular = FALSE) {
  $ocss = $style['default'];
  // Only override if style is being called.
  if (isset($css[$ocss])) {
    if (isset($style['cdn'])) {
      // If cdn is provided, set data to external source.
      $data = $style['cdn'];
      // Set key to data to prevent multiple calls to same source.
      $ocss = $data;
    }
    else {
      $path = $cellular === TRUE ? constant('CELLULAR_LIB') : path_to_theme();
      // Or set data to local file.
      $data = $path . '/css/' . $style['file'];
    }
    $css[$ocss]['data'] = $data;
    $css[$ocss]['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : FALSE;
    $css[$ocss]['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
    $css[$ocss]['group'] = isset($style['group']) ? $style['group'] : CSS_DEFAULT;
    $css[$ocss]['weight'] = isset($style['weight']) ? $style['weight'] : 0;
    $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
    $css[$ocss]['media'] = isset($style['media']) ? $style['media'] : 'all';
    $css[$ocss]['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);
  }
}
