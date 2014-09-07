<?php
/**
 * @file
 * Cellular utility functions.
 */

/**
 * Merge arrays & concat ' ' separated values to string.
 */
function cellular_merge(&$arr) {
  $output = '';
  foreach ($arr as $a) {
    $output .= (is_array($a)) ?
      implode_r(' ', $a) : " " . $a;
  }

  return $output;
}

/**
 * Add <link> & <meta> tags from an array.
 */
function cellular_build_head_tags(&$array) {
  foreach ($array as $meta => $val) {
    if (isset($val)) {
      // Build tag:
      $tag = array(
        '#type'       => 'html_tag',
        '#tag'        => $val['tag'],
        '#attributes' => array(),
        '#weight'     => isset($val['weight']) ?
            $val['weight'] : 0,
      );
      // Misc. attr/val:
      isset($val['attr']) && isset($val['attr_val']) ?
        $tag['#attributes'][$val['attr']] = $val['attr_val'] : NULL;
      // General attributes:
      isset($val['name']) ?
        $tag['#attributes']['name'] = $val['name'] : NULL;
      isset($val['rel']) ?
        $tag['#attributes']['rel'] = $val['rel'] : NULL;
      isset($val['content']) ?
        $tag['#attributes']['content'] = $val['content'] : NULL;
      isset($val['href']) ?
        $tag['#attributes']['href'] = $val['href'] : NULL;
      // Attributes for favicons:
      isset($val['size']) ?
        $tag['#attributes']['sizes'] = $val['size'] : NULL;
      isset($val['type']) ?
        $tag['#attributes']['type'] = $val['type'] : NULL;

      drupal_add_html_head($tag, 'meta_' . $meta);
    }
  }
}

/**
 * Add array of javascripts to $javascript, using a CDN if provided.
 * A fallback link will be automatically generated if using CDN and
 * the 'object' value is provided.
 */
function cellular_add_js($array, $cellular = FALSE) {
  foreach ($array as $script) {
    if (!empty($script)) {
      // Set default attributes.
      $script['type'] = isset($script['cdn']) ?
        'external' : 'file';
      $script['version'] = isset($script['version']) ?
        $script['version'] : NULL;
      $script['group'] = isset($script['group']) ?
        $script['group'] : JS_THEME;
      $script['every_page'] = isset($script['every_page']) ?
        $script['every_page'] : TRUE;
      $script['weight'] = isset($script['weight']) ?
        $script['weight'] : 0;

      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ?
          $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
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
  $attr = array(
    'group'      => $script['group'],
    'weight'     => $script['weight'] + 0.1,
    'type'       => 'inline',
    'every_page' => isset($script['every_page']) ?
        $script['every_page'] : TRUE,
  );
  if (isset($script['object'])) {
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ?
      $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
    $fallback .= '/js/' . $script['file'];
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, $attr);
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
        $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
      $data .= isset($script['file']) ?
        '/js/' . $script['file'] : NULL;
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
          $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
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
          $style['weight'] : 10;
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
      $data = $GLOBALS['theme_path'] . 'css/' . $style['file'];
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
 * Set path to page-error.tpl if http error is returned.
 */
function cellular_error_page(&$vars) {
// Set custom error template:
  $http_status = drupal_get_http_header("status");

  if (isset($http_status)) {

    switch ($http_status) {
      case "403 Forbidden":
      case "404 Not Found":
      case "500 Internal Server Error":
        $vars['theme_hook_suggestions'][] = 'page__error';
        $vars['http_status'] = "Error: " . $http_status;
        $vars['error_message'] = drupal_get_messages();
        $vars['classes_array'][] = 'page-error';

        cellular_merge($vars['classes_array']);
        break;
    }
  }
}

/**
 * Add stylesheets used with javascript plugins, including jQuery.ui.
 */
function cellular_add_plugin_css(&$css) {
  // Plugins available through cellular, styles added based on theme settings.
// $plugin_css paths are relative to /libraries/cellular/css/
  $plugin_css = array(
    'prism'  => theme_get_setting('prism') == 1 ?
        array(
          'file' => 'prism.css',
        ) : NULL,
    'reveal' => theme_get_setting('reveal') == 1 ?
        array(
          'file' => 'reveal/reveal.min.css',
        ) : NULL,
  );

  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_css($css);
  }

  cellular_add_css($css, $plugin_css, TRUE);
}

/**
 * Removes text formatting options from user input.
 */
function cellular_form_strip_access(&$form) {
  // Remove individual text format options:
  // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
  // Or Nuke text format options:
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;

  return $form;
}

/**
 * Print variables if dsm is enabled.
 */
function cellular_dev($element) {
  if (theme_get_setting('dev') === 1) {
    if (module_exists('devel')) {
      dsm($element);
    }
    else {
      print '<div class="cell-70 center">';
      print_r($element);
      print '</div>';
    }
  }
}
