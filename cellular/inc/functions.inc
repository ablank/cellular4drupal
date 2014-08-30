<?php
/**
 * @file
 * General utility functions
 * @author    Adam Blankenship
 */

/*
 *  Get path to current || child theme
 */

function cellular_theme_path(&$theme_key = NULL) {
  $t_theme = isset($theme_key) ? $theme_key : $GLOBALS['theme'];
  $theme_path = drupal_get_path('theme', $t_theme);

  return $theme_path;
}

/*
 *  Merge attributes arrays
 */

function cellular_merge(&$arr) {
  $output = '';
  foreach ($arr as $a) {
    $output .= (is_array($a)) ? implode_r(' ', $a) : " " . $a;
  }

  return $output;
}

/*
 *  Add <link> & <meta> tags from array
 */

function cellular_build_head_tags(&$array) {
  $base_weight = 0;

  foreach ($array as $meta => $val) {
    // Build tag
    $tag = array(
      '#type'       => 'html_tag',
      '#tag'        => $val['tag'],
      '#attributes' => array(),
      '#weight'     => isset($val['weight']) ? $val['weight'] : $base_weight
    );

    // Misc. attr/val
    isset($val['attr']) && isset($val['attr_val']) ? $tag['#attributes'][$val['attr']] = $val['attr_val'] : NULL;
    // General attributes
    isset($val['name']) ? $tag['#attributes']['name'] = $val['name'] : NULL;
    isset($val['rel']) ? $tag['#attributes']['rel'] = $val['rel'] : NULL;
    isset($val['content']) ? $tag['#attributes']['content'] = $val['content'] : NULL;
    isset($val['href']) ? $tag['#attributes']['href'] = $val['href'] : NULL;
    // Attributes for favicons
    isset($val['size']) ? $tag['#attributes']['sizes'] = $val['size'] : NULL;
    isset($val['type']) ? $tag['#attributes']['type'] = $val['type'] : NULL;

    drupal_add_html_head($tag, 'meta_' . $meta);
  }
}

/*
 *  Add javascripts from array
 */

function cellular_add_js($array, $cellular = FALSE) {
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

function cellular_js_fallback($script, $cellular = FALSE) {
  $attr = array(
    'group'      => $script['group'],
    'weight'     => $script['weight'] + 0.1,
    'type'       => 'inline',
    'every_page' => isset($script['every_page']) ?
        $script['every_page'] : TRUE,
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

function cellular_js_override(&$javascript, $script, $cellular = FALSE) {
  // only override if js is being called
  if (isset($javascript[$script['default']])) {
    $ojs = $script['default'];

    if (isset($script['cdn'])) {
      // if cdn is provided, set data to external source & call local fallback
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      // or set data to local file
      $data = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
      $data .= isset($script['file']) ? '/js/' . $script['file'] : NULL;
    }

    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['version'] = isset($script['version']) ? $script['version'] : NULL;
    $javascript[$ojs]['group'] = isset($script['group']) ? $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = isset($script['weight']) ? $script['weight'] : 0;
    $javascript[$ojs]['type'] = isset($script['cdn']) ? 'external' : 'file';
    $javascript[$ojs]['preprocess'] = isset($script['preprocess']) ? $script['preprocess'] : FALSE;
  }
}

/*
 *  Add stylesheets
 */

function cellular_add_css(&$css, $array, $cellular = FALSE) {
  foreach ($array as $style) {
    if (isset($style)) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      else {
        $data = $cellular === TRUE ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
        $data .= '/css/' . $style['file'];
      }

      $style['data'] = $data;
      $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
      $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
      $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
      $style['weight'] = isset($style['weight']) ? $style['weight'] : 10;
      $style['type'] = isset($style['cdn']) ? 'external' : 'file';
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

/*
 *  Override javascript
 */

function cellular_css_override(&$css, $style, $cellular = FALSE) {
  $ocss = $style['default'];
  // only override if style is being called
  if (isset($css[$ocss])) {
    if (isset($style['cdn'])) {
      // if cdn is provided, set data to external source & call local fallback
      $data = $style['cdn'];
    }
    else {
      // or set data to local file
      $data = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
      $data .= isset($style['file']) ? '/css/' . $style['file'] : NULL;
    }

    $css[$ocss]['data'] = $data;
    $css[$ocss]['group'] = isset($style['group']) ? $style['group'] : CSS_DEFAULT;
    $css[$ocss]['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
    $css[$ocss]['weight'] = isset($style['weight']) ? $style['weight'] : 0;
    $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
    $css[$ocss]['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : FALSE;
  }
}

/*
 * Remove text formatting options from user input
 */

function cellular_form_strip_access(&$form) {
  // Nuke text format options
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;

  // Remove individual text format options
  /*
    $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
   */

  return $form;
}

/*
 * Main Menu
 */

function cellular_main_menu(&$vars) {
  if (theme_get_setting('full_menu') == 1) {

    // Render the full main menu tree
    // Use css / js to show/hide sub-menus
    $main_menu_tree = menu_tree_all_data('main-menu');
  }
  else {
    $main_menu_tree = menu_main_menu();
  }

  return menu_tree_output($main_menu_tree);
}

/*
 * Sidebar Test
 */

function cellular_test_sidebar(&$vars) {
  $sidebar_left = !empty($vars['page']['sidebar_left']) ? 1 : NULL;
  $sidebar_right = !empty($vars['page']['sidebar_right']) ? 1 : NULL;

  // Check if sidebars are rendered & set classes accordingly
  if (isset($sidebar_left) && isset($sidebar_right)) {
    $sidebars = 'dual-sidebars';
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
    $sidebars = 'single-sidebar';
  }
  else {
    $sidebars = 'no-sidebars';
  }

  return $sidebars;
}

/*
 * Get links to cdn jQuery & jQuery.ui
 */
/*
function cellular_get_cdn(&$vars) {

}
*/
