<?php

/*
 *  Add stylesheets
 */

function cellular_add_css(&$css, $array, $cellular) {
  foreach ($array as $style) {
    if (isset($style)) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      else {
        $data = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
        $data .= '/css/' . $style['file'];
      }

      $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
      $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
      $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
      $style['weight'] = isset($style['weight']) ? $style['weight'] : 10;
      $style['type'] = isset($style['cdn']) ? 'external' : 'file';
      $style['data'] = $data;
      $style['media'] = isset($style['media']) ? $style['media'] : 'all';
      $style['browsers'] = array('IE' => TRUE, '!IE' => TRUE,);

      $css[$style['file']] = $style;
    }
  }

  return $css;
}

/*
 *  Remove stylesheets
 */

function cellular_remove_css(&$css, $exclude) {

  foreach ($exclude as $module => $stylesheet) {
    // Remove multiple stylesheets attached by module
    if (is_array($stylesheet)) {
      foreach ($stylesheet as $style) {
        unset($css[drupal_get_path('module', $module) . '/' . $style]);
      }
      // Remove individual stylesheet
    }
    else {
      unset($css[drupal_get_path('module', $module) . '/' . $stylesheet]);
    }
  }
}
