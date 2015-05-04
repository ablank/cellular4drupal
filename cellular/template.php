<?php
/**
 * @file
 * Cellular Base Theme for Drupal 7.
 *
 * @author Adam Blankenship
 * 
 * @see http://live-cellular.gotpantheon.com
 * @see https://github.com/ablank/cellular
 */


/*
 * @see file: preprocess/_init.inc
 * Initialize constants & globals
 */

define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');


/*
 * @see file: preprocess/fn.inc
 * Cellular utility functions.
 */

/**
 * Get path to current theme.
 *
 *
 * @param type $theme_key
 *   The name of the theme to get path to, defaults to active theme.
 *
 * @return string
 *   Path to active theme.
 */
function cellular_theme_path(&$theme_key = NULL) {
  $theme = isset($theme_key) ? $theme_key : $GLOBALS['theme_key'];

  return drupal_get_path('theme', $theme);
}

/**
 * Get media query breakpoints from theme settings.
 *
 * @return array
 *   Media queries settings.
 */
function cellular_mq() {
  $mq = array();
  $mq['mobile'] = theme_get_setting('mq_mobile');
  $mq['normal'] = theme_get_setting('mq_normal');
  $mq['large'] = theme_get_setting('mq_large');

  return $mq;
}

/**
 * Add <link> & <meta> tags from an array.
 *
 * @param array $array
 *   Array of tags to add to document <head>.
 */
function cellular_build_head_tags($array) {
  foreach ($array as $meta => $val) {
    if (isset($val)) {
      // Build tag:
      $tag = array(
        '#type' => 'html_tag',
        '#tag' => $val['tag'],
        '#attributes' => array(),
        '#weight' => isset($val['weight']) ? $val['weight'] : 0,
      );
      // Misc. attr/val:
      empty($val['attr']) || empty($val['attr_val']) ? NULL :
      $tag['#attributes'][$val['attr']] = $val['attr_val'];
      empty($val['profile']) ? NULL :
      $tag['#attributes']['profile'] = $val['profile'];
      // General attributes:
      empty($val['name']) ? NULL :
      $tag['#attributes']['name'] = $val['name'];
      empty($val['rel']) ? NULL :
      $tag['#attributes']['rel'] = $val['rel'];
      empty($val['content']) ? NULL :
      $tag['#attributes']['content'] = $val['content'];
      empty($val['href']) ? NULL :
      $tag['#attributes']['href'] = $val['href'];
      // Attributes for favicons:
      empty($val['size']) ? NULL :
      $tag['#attributes']['sizes'] = $val['size'];
      empty($val['type']) ? NULL :
      $tag['#attributes']['type'] = $val['type'];

      drupal_add_html_head($tag, 'meta_' . $meta);
    }
  }
}

/**
 * Set path to page-error.tpl if http error is returned.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
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
        $vars['classes_array'][] = 'page-error';
        $vars['error_message'] = drupal_get_messages();
        break;
    }
  }
}

/**
 * Removes text formatting options from user input.
 *
 * @param array $form
 *   Form element to set.
 * @param array $form_state
 *   Form element's state.
 */
function cellular_form_format_opt(&$form, $form_state) {
  // Remove individual text format options:
  // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
  // Or Nuke text format options:
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;
  $form[LANGUAGE_NONE][0]['format']['#default_value'] = 'filtered';

  return $form;
}

/**
 * Print variables for development as message, usedful if devel isn't available.
 *
 * @param array $element
 *   Element to test and return variables of.
 */
function cellular_dev($element) {
  if (theme_get_setting('dev') == 1) {
    if (module_exists('devel')) {
      dpm($element);
    }
    else {
      drupal_set_message('<pre>' . print_r($element, TRUE) . '</pre>');
    }
  }
}


/*
 * @see file: preprocess/fn.css.inc
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
function cellular_add_css(&$css, $array, $cellular = FALSE) {
  foreach ($array as $style) {
      if (isset($style['cdn'])) {
        $data = $style['cdn'];
      }
      elseif (isset($style['file'])) {
        $data = $cellular === TRUE ? constant('CELLULAR_LIB') : cellular_theme_path();
        $data .= '/css/' . $style['file'];
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

      
    }
        $css[$data] = $style;
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
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $style
 *   Array of stylesheet data used to override default.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_override_css(&$css, $style,  $cellular = FALSE) {
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
      $path = $cellular === TRUE ? constant('CELLULAR_LIB') : cellular_theme_path();
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

/**
 * Remove core stylesheets based on theme settings.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_remove_default_css(&$css) {
  // Nuke all css not a member of group CSS_THEME:
  $exclude = array();
  if (theme_get_setting('remove_drupal_css') === 'theme_only') {
    foreach ($css as $key => $value) {
      $keep = array(
        'toolbar',
        'admin_menu',
        'admin_menu_toolbar'
      );

      if (!array_key_exists($key, $keep) && $value['group'] !== CSS_THEME) {
        unset($css[$key]);
      }
    }
  }
  // 86 SYSTEM_CSS.
  if (theme_get_setting('remove_drupal_css') === 'system') {
    foreach ($css as $key => $value) {
      if ($value['group'] === CSS_SYSTEM) {
        unset($css[$key]);
      }
    }
  }
  // Remove selected system & module css.
  if (theme_get_setting('remove_drupal_css') === 'select') {
    // Select module css to exclude.
    $exclude = array(
      'system' => array(
        'system.base.css',
        //'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block' => 'block.css',
      'colorbox' => 'styles/default/colorbox_style.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'menu' => 'menu.css',
      'node' => 'node.css',
      'panels' => 'css/panels.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
}


/*
 * @see file: preprocess/fn.menu.inc
 * Cellular menu functions.
 */

/**
 *
 */
function cellular_links__system_main_menu($vars) {
  $output .= "<ul id=\"nav\">\n";
  foreach ($vars['links'] as $key => $link) {
    $output .= "<li>".l($link['title'], $link['path'], $link)."</li>";
  }
  $output .= "</ul>\n";

  return $output;
}

/**
 * Returns full Main Menu instead of top-level links.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from theme registry.
 */
function cellular_main_menu(&$vars) {
  if (theme_get_setting('full_menu') == 1) {
    // Render the full main menu tree, use css / js to show/hide sub-menus.
    $menu_data = menu_tree_output(menu_tree_all_data('main-menu'));
  }
  else {
    $menu_data = menu_tree('main-menu');
  }

   $vars['main_menu'] = $menu_data;
   //$vars['main_menu']['#theme_wrappers'] = array('cellular_menu_tree__main_menu');
   /*
   $vars['main_menu'] = theme('links__system_main_menu', array(
      'links' => $menu_data,
      'attributes' => array(
        'id' => 'nav',
        'class' => array(
          'primary'
          )
        ),
      // 'heading' => t('Main menu'),
    ));
    */
  // dpm($menu_data);
   // dpm($vars);
}


/*
 * @see file: preprocess/fn.js.inc
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


/*
 * @see file: preprocess/fn.jquery.inc
 * Functions for updating jQuery & jQuery.ui.
 */

/**
 * Get info from theme settings.
 *
 * @return array
 *   Settings for jQuery & jQuery.ui
 */
function cellular_jquery_info() {
  $jquery = array(
    'update' => theme_get_setting('jquery_update'),
    'version' => theme_get_setting('jquery_version'),
    'use_cdn' => theme_get_setting('jquery_cdn'),
    'cdn' => theme_get_setting('jquery_cdn_source'),
    'ui' => array(
      'version' => theme_get_setting('jqueryui_version'),
      'theme' => theme_get_setting('jqueryui_theme'),
    ),
  );

  return $jquery;
}

/**
 * Generate links to CDN sources.
 *
 * @return array
 *   CDN URLs used to update jQuery & jQuery.ui
 */
function cellular_cdn() {
  /* Available cdns:
   * //ajax.googleapis.com/ajax/libs/jquery/1.10.4/jquery.min.js
   * //ajax.aspnetcdn.com/ajax/jquery.ui/1.10.4/jquery-ui.min.js
   * //cdnjs.cloudflare.com/ajax/libs/jqueryui/1.10.4/jquery-ui.min.js
   */
  $jq = cellular_jquery_info();
  $ui = $jq['ui'];
  $networks = array(
    'jquery' => array(
      'base_url' => '//code.jquery.com/',
      'jquery' => 'jquery-' . $jq['version'] . '.min.js',
      'jqueryui' => 'ui/' . $ui['version'] . '/jquery-ui.min.js',
      'theme' => 'ui/' . $ui['version'] . '/themes/'
      . $ui['theme'] . '/jquery-ui.css',
    ),
    'google' => array(
      'base_url' => '//ajax.googleapis.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery.min.js',
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui.min.js',
      'theme' => 'jqueryui/' . $ui['version'] . '/themes/'
      . $ui['theme'] . '/jquery-ui.css',
    ),
    'microsoft' => array(
      'base_url' => '//ajax.aspnetcdn.com/ajax/',
      'jquery' => 'jquery/jquery-' . $jq['version'] . '.min.js',
      'jqueryui' => 'jquery.ui/' . $ui['version'] . '/jquery-ui.min.js',
      'theme' => 'jquery.ui/' . $ui['version'] . '/themes/'
      . $ui['theme'] . '/jquery-ui.css',
    ),
    'cloudflare' => array(
      'base_url' => '//cdnjs.cloudflare.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery.min.js',
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui.min.js',
      'theme' => 'jqueryui/' . $ui['version'] . '/css/jquery-ui.min.css',
    ),
  );

  // Select cdn to use.
  $cdn = $networks[$jq['cdn']];

  return $cdn;
}

/**
 * Update jQuery & essential plugins.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 */
function cellular_jquery_update(&$javascript) {
  $jq = cellular_jquery_info();
  // Override jQuery.
  $jquery = array(
    'default' => 'misc/jquery.js',
    'object' => 'jQuery',
    'version' => $jq['version'],
    'file' => 'jquery-' . $jq['version'] . '.min.js',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -100,
  );

  if ($jq['use_cdn'] == 1) {
    // Select cdn to use:
    $cdn = cellular_cdn();
    $jquery['cdn'] = $cdn['base_url'] . $cdn['jquery'];
  }

  cellular_js_override($javascript, $jquery, TRUE);

  // Override jQuery.cookie.
  $jquerycookie = array(
    'default' => 'misc/jquery.cookie.js',
    'version' => '1.4.1',
    'file' => 'plugins/jquery.cookie.min.js',
  );

  cellular_js_override($javascript, $jquerycookie, TRUE);

  // Override jQuery.once.
  $jqueryonce = array(
    'default' => 'misc/jquery.once.js',
    'version' => '1.2.6',
    'file' => 'plugins/jquery.once.min.js',
  );

  cellular_js_override($javascript, $jqueryonce, TRUE);

  // Override jQuery.form.
  $jqueryform = array(
    'default' => 'misc/jquery.form.js',
    'version' => '3.48',
    'file' => 'plugins/jquery.form.min.js',
  );

  cellular_js_override($javascript, $jqueryform, TRUE);

  // Add jQuery.migrate to prevent deprecated functions from breaking.
  $migrate = theme_get_setting('jquery_migrate');
  if (!empty($migrate)) {
    // Add jQuery.migrate  if v >= 1.9
    if ($jquery['version'] !== '1.8.24') {
      $js_plugins['migrate'] = array(
        'version' => '1.2.1',
        'file' => 'plugins/jquery.migrate.min.js',
        'group' => JS_LIBRARY,
        'weight' => -96,
      );
      // Add js after override.
      cellular_add_js($js_plugins, TRUE);
    }
  }
}

/**
 * Override jQueryUI javascript.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 */
function cellular_jqueryui_update_js(&$javascript) {
  $jq = cellular_jquery_info();
  $ui_widgets = array(
    'ui.core',
    'ui.accordion',
    'ui.autocomplete',
    'ui.button',
    'ui.datepicker',
    'ui.dialog',
    'ui.draggable',
    'ui.droppable',
    'ui.mouse',
    'ui.position',
    'ui.progressbar',
    'ui.resizable',
    'ui.selectable',
    'ui.slider',
    'ui.sortable',
    'ui.tabs',
    'ui.widget',
    'effects.blind',
    'effects.bounce',
    'effects.clip',
    'effects.drop',
    'effects.explode',
    'effects.fade',
    'effects.fold',
    'effects.highlight',
    'effects.pulsate',
    'effects.scale',
    'effects.shake',
    'effects.slide',
    'effects.transfer',
  );

  foreach ($ui_widgets as $widget) {
    $default = 'misc/ui/jquery.' . $widget . '.min.js';
    if (isset($javascript[$default])) {
      $script = array(
        'jqueryui' => array(
          'default' => $default,
          'object' => 'jQuery.ui',
          'version' => $jq['ui']['version'],
          'group' => JS_LIBRARY,
          'every_page' => FALSE,
          'weight' => isset($javascript[$default]['weight']) ? $javascript[$default]['weight'] : -9,
          'file' => "jquery-ui/" . $jq['ui']['version'] . "/minified/jquery.$widget.min.js",
          'preprocess' => TRUE,
          'browsers' => array('IE' => TRUE, '!IE' => TRUE),
        ),
      );

      if (theme_get_setting('jquery_cdn') == 1) {
        $cdn = cellular_cdn();
        // If updating from cdn unset each widget so a single call can be made.
        unset($javascript[$default]);
        // Set cdn source.
        $script['jqueryui']['cdn'] = $cdn['base_url'] . $cdn['jqueryui'];
        // Set lower weight so cdn is delivered before fallbacks.
        $script['jqueryui']['weight'] = -10;
        // Add single link to cdn, with local fallback to each file.
        cellular_add_js($script, TRUE);
      }
      else {
        cellular_js_override($javascript, $script['jqueryui'], TRUE);
      }
    }
  }
}

/**
 * Update jQuery.ui stylesheets.
 *
 * @param array $css
 *   Associative array of stylesheets.
 */
function cellular_jqueryui_update_css(&$css) {
  $ui['path'] = 'jquery-ui/';
  $ui['widgets'] = array(
    'core',
    'theme',
    'accordion',
    'autocomplete',
    'button',
    'datepicker',
    'dialog',
    'progressbar',
    'resizable',
    'selectable',
    'slider',
    'tabs',
  );

  foreach ($ui['widgets'] as $widget) {
    $default = "misc/ui/jquery.ui.$widget.css";
    if (isset($css[$default])) {
      $jq = cellular_jquery_info();
      $jq = $jq['ui'];
      $style = array(
        'ui' => array(
          'default' => $default,
          'version' => $jq['version'],
          'group' => CSS_SYSTEM,
          'every_page' => FALSE,
          'weight' => isset($css[$default]['weight']) ?
          $css[$default]['weight'] : -9,
          'file' => NULL,
        ),
      );
      // Remove default after updating styles.
      unset($css[$default]);

      if ($jq['theme'] === 'custom') {
        // Set path to local custom file if selected.
        $v = $jq['version'] === '1.10.4' ? '1.10' : '1.9';
        $style['ui']['file'] = "/jquery-ui/jquery-ui.$v.css";

        cellular_add_css($css, $style);
      }
      else {
        $ui_path = $ui['path'] . $jq['version'] . '/' . $jq['theme'] . '/';
        $style['ui']['file'] = $ui_path . 'jquery-ui.css';
        if (theme_get_setting('jquery_cdn') == 1) {
          $cdn = cellular_cdn();
          // Set cdn source.
          $style['ui']['cdn'] = $cdn['base_url'] . $cdn['theme'];
        }

        cellular_add_css($css, $style, TRUE);
      }
    }
  }
}


/*
 * @see file: preprocess/fn.preprocess.inc
 * Cellular functions to set content attributes.
 */

/**
 * Add HTTP Response Headers.
 */
function cellular_http_headers() {
  // Help prevent xss clickjacking.
  drupal_add_http_header('X-Frame-Options', 'DENY');
  // Set IE compatibility mode.
  drupal_add_http_header('X-UA-Compatible', 'IE=Edge,chrome=1');
}

/**
 * Set html attributes.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_html_attributes(&$vars) {
  global $language;
  $html_attributes = array(
    'lang' => $language->language,
    'xml:lang' => $language->language,
    'dir' => $language->dir,
  );
  // Check support for RDF & add DOCTYPE:
  if (module_exists('rdf')) {
    // Set namespace.
    $html_attributes['xmlns'] = 'http://www.w3.org/1999/xhtml';
  }

  $vars['doctype'] = "<!DOCTYPE html>\n";
  $vars['html_attributes'] = drupal_attributes($html_attributes);
}

/**
 * Convert @xmlns to @profile.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_rdf(&$vars) {
  $vars['rdf_prefixes'] = '';
  // Add extra namespaces if needed:
  // $vars['rdf_namespaces'] .= "\nxmlns:og=\"http://opengraphprotocol.org/schema/\"";
  // Check support for RDF & add DOCTYPE:
  if (module_exists('rdf')) {
    // @ http://phase2technology.com/?p=552
    $head_attributes = array();
    $prefixes = array();
    $namespaces = explode("\n", trim($vars['rdf_namespaces']));

    foreach ($namespaces as $name) {
      list($key, $url) = explode('=', $name, 2);
      list($xml, $space) = explode(':', $key, 2);
      unset($xml);
      $url = trim(str_replace('"', '', $url));
      $prefixes[] = "\n" . $space . ": " . $url;
    }
    $head_attributes['prefix'] = implode(' ', $prefixes);

    $vars['rdf_prefixes'] = drupal_attributes($head_attributes);
  }
}

/**
 * Add variable classes to <body>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_body_attributes(&$vars) {
  $body_attributes = array();
  $path = drupal_get_path_alias();
  // Page URL is used to set id & classes of body.
  $aliases = explode('/', $path);
  // Set the current page as body id:
  $body_attributes['id'] = array_pop($aliases);

  // Add body classes:
  foreach ($aliases as $alias) {
    $body_attributes['class'][] = $alias;
  }

  // Sidebar class is generated if region is used on page.
  $body_attributes['class'][] = cellular_test_sidebar($vars);
  drupal_is_front_page() ? $body_attributes['class'][] = 'frontpage' : NULL;
  user_is_logged_in() ? $body_attributes['class'][] = 'user' : NULL;

  $vars['body_attributes'] = drupal_attributes($body_attributes);
}

/**
 * Build links to favicons & apple-touch-icons.
 */
function cellular_favicons() {
  // Get icon file names from theme settings.
  $settings = array(
    'favicon' => theme_get_setting('favicon'),
    'favicon-32' => theme_get_setting('favicon_32'),
    'apple-default' => theme_get_setting('apple_icon_57'),
    'apple-72' => theme_get_setting('apple_icon_72'),
    'apple-114' => theme_get_setting('apple_icon_114'),
    'apple-144' => theme_get_setting('apple_icon_144'),
  );

  $favicons = array();
  !empty($settings['favicon']) ? $favicons['favicon-16x16'] = array(
    'rel' => 'shortcut icon',
    'type' => 'image/x-icon',
    'size' => NULL,
    'href' => $settings['favicon'],
    'weight' => 95,
  ) : NULL;
  !empty($settings['favicon-32']) ? $favicons['favicon-32x32'] = array(
    'rel' => 'shortcut icon',
    'type' => 'image/png',
    'size' => '32x32',
    'href' => $settings['favicon-32'],
    'weight' => 96,
  ) : NULL;
  /* Older iOS devices don't understand the sizes attribute and use
   * whichever value is last, so 'default' is given more weight.
   */
  !empty($settings['apple-default']) ? $favicons['apple-default'] = array(
    'rel' => 'apple-touch-icon',
    'size' => NULL,
    'href' => $settings['apple-default'],
    'weight' => 100,
  ) : NULL;
  !empty($settings['apple-72']) ? $favicons['apple-72x72'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '72x72',
    'href' => $settings['apple-72'],
    'weight' => 99,
  ) : NULL;
  !empty($settings['apple-114']) ? $favicons['apple-114x114'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '114x114',
    'href' => $settings['apple-114'],
    'weight' => 98,
  ) : NULL;
  !empty($settings['apple-144']) ? $favicons['apple-144x144'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '144x144',
    'href' => $settings['apple-144'],
    'weight' => 97,
  ) : NULL;

  foreach ($favicons as &$favicon) {
    if (isset($favicon)) {
      // Set tag type to <link>
      $favicon['tag'] = 'link';
      // Set href relative to /assets/favicons/
      $favicon['href'] = cellular_theme_path() . '/assets/favicons/' . $favicon['href'];
    }
  }

  cellular_build_head_tags($favicons);
}

/**
 * Add meta tags to <head>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_metatags(&$vars) {
  // Add default metatags:
  $meta_tags = array(
    'viewport' => array(
      'tag' => 'meta',
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
      'weight' => 0,
    ),
    'robots' => array(
      'tag' => 'meta',
      'name' => 'robots',
      'content' => 'index, follow',
      'weight' => 2,
    ),
    'humans' => array(
      'tag' => 'link',
      'type' => 'text/plain',
      'rel' => 'author',
      'href' => $GLOBALS['base_url'] . '/humans.txt',
      'weight' => 3,
    ),
  );

  // Add conditional metatags:
  isset($vars['grddl_profile']) ? $meta_tags['grddl'] = array(
    'tag' => 'link',
    'rel' => 'profile',
    'href' => $vars['grddl_profile'],
    'weight' => 4,
  ) : NULL;

  cellular_build_head_tags($meta_tags);
}

/**
 * Test if sidebar regions are used and return the appropriate class.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_test_sidebar(&$vars) {
  empty($vars['page']['sidebar_left']) ? NULL : $sidebar_left = 1;
  empty($vars['page']['sidebar_right']) ? NULL : $sidebar_right = 1;

  if (!isset($sidebar_left) && !isset($sidebar_right)) {
    $vars['page']['content_class'] = theme_get_setting('content_class_no_sidebar');
  }
  elseif (isset($sidebar_left) && isset($sidebar_right)) {
    $vars['page']['content_class'] = theme_get_setting('content_class_dual_sidebars');
    $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_dual_sidebars');
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
    $vars['page']['content_class'] = theme_get_setting('content_class_single_sidebar');
    $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_single_sidebar');
  }
}

/**
 * Set content author attributes.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_set_author(&$vars) {
  $node = $vars['elements']['#node'];
  $uid = user_load($node->uid);
  $safe_value = "['LANGUAGE_NONE'][0]['safe_value']";
  $author = array(
    'name' => l($node->name, 'user/' . $node->uid),
    'description' => isset($vars['author']->field_description[$safe_value]) ?
    '<div class="author-description">' . $uid->field_description[$safe_value] . '</div>' : NULL,
    'image' => !empty($uid->picture->uri) ? theme('image_style', array(
      'path' => $node->picture->uri,
      'width' => NULL,
      'height' => NULL,
      'alt' => t('User') . ' ' . $node->name,
      'title' => t('User') . ' ' . $node->name,
      'attributes' => array('class' => 'author-image'),
    )) : NULL,
  );

  $vars['author'] = $author['image'] . $author['name'] . $author['description'];
}


/*
 * @see file: preprocess/alter.inc
 * Alter misc. hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 */
function cellular_html_head_alter(&$head_elements) {
  // Remove unwanted meta tags.
  $exclude = array('metatag_generator');

  foreach ($exclude as $element) {
    if (isset($head_elements[$element])) {
      unset($head_elements[$element]);
    }
  }
  // cellular_dev($head_elements);
}

/**
 * Implements hook_page_alter().
 */
function cellular_page_alter(&$page) {
  // cellular_dev($page);
}


/*
 * @see file: preprocess/css_alter.inc
 * Add/Update/Delete stylesheets.
 */

/**
 * Implements hook_css_alter().
 */
function cellular_css_alter(&$css) {
  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  $ext = theme_get_setting('min_style') == 1 ? '.min.css' : '.css';
  // Add stylesheets to theme.
  // Paths are relative to /yourTheme/css/
  $add_css = array(
    'drupal' => array(
      'file' => 'drupal' . $ext,
      'weight' => 10,
    ),
    'style' => array(
      'file' => 'style' . $ext,
      'weight' => 11,
    ),
    'print' => array(
      'file' => 'print' . $ext,
      'media' => 'print',
      'weight' => 100,
      'preprocess' => FALSE,
    ),
    'ie' => array(
      // Single stylesheet used to hack old internet explorer quirks.
      // Minimal support for deprecated breowsers is fine imo...
      'file' => 'ie' . $ext,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'weight' => 999,
    ),
  );
  cellular_add_css($css, $add_css);

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_update_css($css);
  }
  !empty($plugins) ? cellular_add_css($css, $plugins, TRUE) : NULL;
}


/*
 * @see file: preprocess/form_alter.inc
 * Alter specific forms.
 */

/**
 * Implements hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id) {

  switch ($form_id) {
    // Site Search block:
    case 'search_block_form':
    case 'search_form':

      $form['#attributes'] = array(
        'class' => array('site-search'),
      );

      $form[$form_id]['#title'] = t('Search this site');
      $form[$form_id]['#type'] = 'textfield';
      $form[$form_id]['#size'] = 25;
      $form[$form_id]['#default_value'] = t('Search keywords');
      // Submit button.
      $form['actions']['submit']['#type'] = 'submit';
      $form['actions']['submit']['#value'] = t('Search');
      // $form['actions']['submit']['#attributes']['class'] = array('search-submit');

      break;

    // User Login block:FF
    case 'user_login_block':
      $field_size = 20;
      $orient = theme_get_setting('login_block_orientation');

      $form['#attributes']['class'][] = $orient;

      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => t('Username'),
        '#size' => $field_size,
      );
      $form['pass'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#default_value' => t('Password'),
        '#size' => $field_size,
      );
      $form['actions']['submit'][] = array(
        // Change the text on the submit button:
        '#value' => t('Log in'),
        '#attributes' => array(
          'class' => array(
            $orient === 'vertical' ? 'clearfix' : NULL,
          ),
        ),
      );

      // Remove Request New Password and other links from Block form:
      $user_reg = theme_get_setting('login_block_register');
      $user_pass = theme_get_setting('login_block_password');

      if (isset($user_reg) || isset($user_pass)) {
        $output = '<div id="login-links">';
        if (!empty($user_reg)) {
          $output .= l(t('Register'), "user/register", array(
            'attributes' => array(
              'class' => array('register'),
          )));
        }
        if (!empty($user_pass)) {
          $output .= l(t('Forgotten Password?'), "user/password", array(
            'attributes' => array(
              'class' => array('password'),
          )));
        }
        $output .= '</div>';
      }
      else {
        $output = NULL;
      }

      $form['links']['#markup'] = $output;
      // Register New User Account:
      /*
        $form['links']['#markup'][] = t('Register')
        . ' <a href="/user/register">'
        . t('Register') . '</a>';
       */

      // Forgot Password:
      /*
        $form['links']['#markup'][] = t('Forgotten Password?')
        . ' <a href="/user/password">'
        . t('Forgotten Password?') . '</a>';
       */

      // Register New User Account &&  Forgot Password:
      /*
        $form['links']['#markup'] = '<hr/>'
        . ' <a class="user-register" href="/user/register">'
        . t('Register') . '</a>' . '<hr/>'
        . ' <a class="user-password" href="/user/password">'
        . t('Forgotten Password?') . '</a>';
       */

      break;
  }
}

/**
 * Implements hook__form_comment_form_alter().
 */
function cellular_form_comment_form_alter(&$form, $form_state, $form_id) {
  // Set field sizes.
  $field_size = 32;
  // Remove text format option.
  $form['comment_body'][LANGUAGE_NONE][0]['#default_value'] = t('Add your comment');
  $form['comment_body']['#after_build'][] = 'cellular_form_format_opt';

  $form['author']['name']['#size'] = $field_size;
  $form['subject']['#size'] = $field_size;
  // Customize Submit & Preview buttons.
  $form['actions']['preview']['#value'] = t('Preview');
  $form['actions']['preview']['#weight'] = 19;
  $form['actions']['preview']['#attributes']['class'][] = 'left';

  $form['actions']['submit']['#value'] = t('Save');
  $form['actions']['submit']['#weight'] = 20;
  $form['actions']['submit']['#attributes']['class'][] = 'right';
}


/*
 * @see file: preprocess/js_alter.inc
 * Add/Update/Delete javascript.
 */

/**
 * Implements hook_js_alter().
 */
function cellular_js_alter(&$javascript) {
  // Pass variables from drupal to js.
  cellular_js();

  // Get array of js plugins to add.
  $js_plugins = cellular_plugins_js();

  // Add Modernizr & query based on theme settings.
  theme_get_setting('modernizr') == 1 ? cellular_modernizr_default() : NULL;

  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
  }

  // Add js after override.
  cellular_add_js($js_plugins, TRUE);

  // Dev.
  // cellular_dev($javascript);
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js() {
  $ext = theme_get_setting('min_script') == 1 ? '.min.js' : '.js';

// Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
  $js_plugins = array();
  
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = TRUE : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = TRUE : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = TRUE : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = TRUE : NULL;
  theme_get_setting('masonry') == 1 ? $js_plugins['masonry'] = TRUE : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = TRUE : NULL;

// Add to Cellular plugin settings to Drupal.settings.
  drupal_add_js(array('cellular' => $js_plugins), 'setting');

// Add script by extension. The minified source should compile ALL js in
// /yourTheme/js/ into script.min.js.

  // Add Cellular UI
  if (theme_get_setting('cellularui') == 1 && $ext === '.js') {
    $scripts['cellularui'] = array(
      'object' => 'cellular',
      'file' => 'cellularUI/jquery.cellularUI' . $ext,
      'weight' => 98,
    );
  }
  if (($js_plugins) && ($ext === '.js')) {
    $scripts['plugins'] = array(
      'file' => 'plugins' . $ext,
      'group' => JS_DEFAULT,
      'weight' => 99,
    );
  }
  $scripts['script'] = array(
    'file' => 'script' . $ext,
    'group' => JS_THEME,
    'weight' => 100,
  );

  cellular_add_js($scripts);
}


/*
 * @see file: preprocess/js_plugins.inc
 * Functions to add javascript plugins.
 */

/**
 * Build default modernizr queries using theme settings.
 */
function cellular_modernizr_default() {
  $css_dir = '/css/';
  $ext = theme_get_setting('min_style') == 1 ? '.min.css' : '.css';
  // Build yepnope query based on theme settings.
  $mq = cellular_mq();

  $tests = array();
  // Test SVG
  $tests['svg'] = array(
    'test' => 'Modernizr.svg',
    'yep' => $css_dir . "icons-svg" . $ext,
    'nope' => $css_dir . "icons-png" . $ext,
  );

  if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
    $tests['mobile'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['mobile'] . '\')',
      'yep' => $css_dir . "conditional-mobile" . $ext,
    );
  }
  if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
    $tests['normal'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['normal'] . '\')',
      'yep' => $css_dir . "conditional-style" . $ext,
    );
  }
  if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
    $tests['large'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['large'] . '\')',
      'yep' => $css_dir . "conditional-large" . $ext,
    );
  }

  cellular_modernizr($tests);
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *   Associative array of plugin data.
 */
function cellular_plugins_js() {
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();
  theme_get_setting('modernizr') == 1 ? $js_plugins['modernizr'] = array(
    'group' => JS_LIBRARY,
    'object' => 'Modernizr',
    'file' => 'modernizr.js',
    'version' => '2.8.3',
    'weight' => -1000,
  ) : NULL;
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = array(
    'object' => 'backstretch',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-backstretch/2.0.4/jquery.backstretch.min.js',
    'file' => 'plugins/jquery.backstretch.min.js',
    'version' => '2.0.4',
    'weight' => -20,
  ) : NULL;
  theme_get_setting('d3js') == 1 ? $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
    'file' => 'plugins/d3.min.js',
    'version' => '3.4.11',
    'weight' => -18,
  ) : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = array(
    'file' => 'plugins/jquery.freetile.min.js',
    'version' => '0.3.1',
    'weight' => -17,
  ) : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = array(
    'file' => 'plugins/jquery.flowtype.js',
    'version' => '',
    'weight' => -16,
  ) : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = array(
    'file' => 'plugins/jquery.parallax.min.js',
    'version' => '2.0',
    'weight' => -15,
  ) : NULL;
  theme_get_setting('prism') == 1 ? $js_plugins['prism'] = array(
    'object' => 'Prism',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
    'file' => 'plugins/prism.min.js',
    'version' => '0.0.1',
    'weight' => -14,
  ) : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
    'file' => 'plugins/jquery.smoove.min.js',
    'version' => '0.2.6',
    'weight' => -12,
  ) : NULL;
  theme_get_setting('snap-svg') == 1 ? $js_plugins['snap-svg'] = array(
    'file' => 'plugins/snap.svg.min.js',
    'version' => '0.3.0',
    'weight' => -11,
  ) : NULL;
  theme_get_setting('threejs') == 1 ? $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
    'file' => 'plugins/three.min.js',
    'version' => 'r68',
    'weight' => -10,
  ) : NULL;

  if (theme_get_setting('gsap') == 1) {
    $gsap['cssplugin'] = array(
      'object' => 'CSSPlugin',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
      'file' => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
      'version' => '1.13.1',
      'weight' => -9,
    );
    $gsap['easepack'] = array(
      'object' => 'EasePack',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
      'file' => 'plugins/gsap/minified/easing/EasePack.min.js',
      'version' => '1.13.1',
      'weight' => -8,
    );
    $gsap['tweenlite'] = array(
      'object' => 'TweenLite',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
      'file' => 'plugins/gsap/minified/TweenLite.min.js',
      'version' => '1.13.1',
      'weight' => -7,
    );
    $gsap['jquerygsap'] = array(
      'object' => 'gsap',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
      'file' => 'plugins/gsap/minified/jquery.gsap.min.js',
      'version' => '1.13.1',
      'weight' => -6,
    );

    $js_plugins = array_merge($js_plugins, $gsap);
  }

  return $js_plugins;
}

/**
 * Stylesheets used by javascript plugins.
 *
 * @return array
 *   Array of stylesheets used by javascript plugins.
 */
function cellular_plugin_css() {
  // Plugins available through cellular, styles added based on theme settings.
  // $plugin_css paths are relative to /libraries/cellular/css/
  $plugin_css = array();
  theme_get_setting('prism') == 1 ? $plugin_css['prism'] = array(
    'file' => 'prism.css',
    'weight' => -10,
  ) : NULL;

  return $plugin_css;
}


/*
 * @see file: preprocess/preprocess.inc
 * Template preprocess variables.
 */

/**
 * Implements template_preprocess_html().
 */
function cellular_preprocess_html(&$vars) {
  cellular_http_headers();
  cellular_html_attributes($vars);
  cellular_rdf($vars);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars);
}

/**
 * Implements template_preprocess_node().
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];

  $vars['title_attributes_array']['class'] = array('node-title');
  $vars['content_attributes_array']['class'] = array('node-content');

  // Customize articles & blog posts:
  if ($node->type === 'article' || 'blog') {
    // Get $author info:
    cellular_set_author($vars);
  }
}

/**
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Add template suggestions for custom Content types(page--content-type.tpl.php)
  isset($vars['node']->type) ? $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type : NULL;

  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page-- === .tpl if http  ===  status is returned.
  // = _page($vars);

  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e.  ===  page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';


  // if this is a panel page, add template suggestions
  if(theme_get_setting('panelseverywhere') == 1 && $panel_page = page_manager_get_current_page()) {
      // add a generic suggestion for all panel pages
      $suggestions[] = 'page__panels';
      // add the panel page machine name to the template suggestions
      $suggestions[] = 'page__panels_' . $panel_page['name'];
      // merge the suggestions in to the existing suggestions (as more specific than the existing suggestions)
      $vars['theme_hook_suggestions'] = array_merge($vars['theme_hook_suggestions'], $suggestions);
    }
  }
  // http://www.grasmash.com/article/add-drupal-template-suggestion-panels-page-paneltplphp#sthash.kJMOIc86.dpuf


/**
 * Implements template_preprocess_maintenance_page().
 */
function cellular_preprocess_maintenance_page(&$vars) {
  // Add template suggestions for custom Content types(page--content-type.tpl.php)
  isset($vars['node']->type) ? $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type : NULL;

  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page-- === .tpl if http  ===  status is returned.
  cellular_error_page === _page($vars);

  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links:
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to templates, i.e.  ===  page.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';
}

/**
 * Implements template_preprocess_block().
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  // Hide block titles in the headers region:
  switch ($block->region) {
    case 'header':
    case 'header-top':
    case 'header-bottom':

      $vars['title_attributes']['class'][] = 'element-invisible';

      break;
  }
}

/**
 * Implements template_preprocess_comment().
 */
function cellular_preprocess_comment(&$vars) {
  // $vars['comment_wrapper'] = NULL;
  $vars['theme_hook_suggestions'][] = 'comment';
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';

  $vars['submitted'] = t('Submitted by !username on !datetime', array(
    '!username' => $vars['author'],
    '!datetime' => $vars['created'],
  ));
}

/**
 * Implements template_preprocess_comment_wrapper.
 */
function cellular_preprocess_comment_wrapper(&$vars) {
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Implements template_ preprocess_username().
 */
function cellular_preprocess_username(&$vars) {
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }
}


/*
 * @see file: preprocess/theme.inc
 * Set element markup.
 */

/**
 * Implements hook_theme_registry_alter().
 */
  /*
function cellular_registry_alter(&$theme_registry) {
  // Override the default page.tpl.php.
  if (theme_get_setting('panelseverywhere') == 1 && isset($theme_registry['page'])) {
    $path = drupal_get_path('theme', 'cellular');
    $theme_registry['field_collection_item']['theme path'] = $path;
    $theme_registry['field_collection_item']['template'] = "$path/templates/page--panels";
  }
}
  */

/**
 * Implements hook_theme().

function cellular_theme($existing, $type, $theme, $path) {
  $theme['main_menu'] = array(
        'arguments' => array(
            // if NULL, function checks variable 'menu_primary_links_source'
            'menu_name' => NULL,

        )
    );
  $theme['panels_page'] = array(
    'base hook' => 'page',
    'render element' => 'page',
    'template' => 'templates/page--panels',
  );

  return $theme;
}
 */

/**
 * Implements theme_field().
 */
function cellular_field(&$vars) {
  $output = '';
  $wrap = theme_get_setting('field_wrappers');
  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= "<h5 class=\"field-label\"" . $vars['title_attributes'] . ">";
    $output .= $vars['label'] . '</h5>';
  }
  // Render the field.
  foreach ($vars['items'] as $delta => $item) {
    $output .= drupal_render($item);
    // Add attributes for each item.
    if (!empty($wrap) && !empty($output)) {
      $output = "\n<div" . $vars['item_attributes'][$delta] . ">\n $output \n</div>";
    }
  }
  // Wrap field if set.
  if ($wrap == 1) {
    $output = "<div class=\"" . $vars['classes'] . '"' . $vars['attributes'] . ">"
    . "\n $output \n</div>\n";
  }

  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function cellular_breadcrumb(&$vars) {
  $output = NULL;
  if (theme_get_setting('breadcrumb_display') == 1) {
    if (!empty($vars['breadcrumb'])) {
      $vars['breadcrumb'][] = '<span class="active">' . drupal_get_title() . '</span>';
      $breadcrumb = $vars['breadcrumb'];

      // Provide a navigational heading to give context for breadcrumb links to
      // screen-reader users. Make the heading invisible with .element-invisible.
      $output .= '<h2 class="element-invisible">' . t('You are here') . '</h2>';

      $output .= theme('item_list', array(
        'items' => $breadcrumb,
        'type' => 'ul',
        'attributes' => array('id' => 'breadcrumb'),
      ));
    }
  }
  return $output;
}

/**
 * Implements theme_file_icon().
 */
function cellular_file_icon(&$vars) {
  //Use css classes to style output instead of <img>.
  $file = $vars['file'];
  $mime = check_plain($file->filemime);
  $generic_mime = (string) file_icon_map($file);

  // $dashed_mime = strtr($file->filemime, array('/' => '-'));
  // $icon_path = $icon_directory . '/' . $dashed_mime . '.png';
  // Use generic icons for each category that provides such icons.
  foreach (array('audio', 'image', 'text', 'video') as $category) {
    if (strpos($file->filemime, $category . '/') == 0) {
      $cname = $category;
    }
  }
  if ($generic_mime) {
    $xmime = explode('/', $mime);
    $cname = $xmime[1];
  }
  isset($cname) ? $cname = $cname : '';

  return '<span class="icon ' . $cname . '"></span>' . "\n";
}

/**
 * Implements theme_feed_icon().
 */
function cellular_feed_icon(&$vars) {
  $text = t('Subscribe to !feed-title', array(
    '!feed-title' => $vars['title'],
  ));

  $icon = l($text, $vars['url'], array(
    'html' => TRUE,
    'attributes' => array(
      'class' => array(
        'icon',
        'rss',
      ),
      'title' => $text,
    ),
  ));

  return $icon;
}


/*
 * @see file: preprocess/theme_form.inc
 * Theme markup of form elements.
 */

/**
 * Return array of attributes.
 *
 * @param array $element
 *   Variable on which to set attributes.
 *
 * @return array
 *   Attributes to render.
 */
function cellular_form_element_attributes(&$element) {
  // $element['#theme_wrappers'] = NULL;
  $attributes = array();
  empty($element['#name']) ? NULL : $attributes['name'] = $element['#name'];
  empty($element['#id']) ? NULL : $attributes['id'] = $element['#id'];
  empty($element['#attributes']['class']) ? NULL : $attributes['class'] = implode(' ', $element['#attributes']['class']);
  empty($element['#title']) ? NULL : $attributes['title'] = $element['#title'];
  empty($element['#required']) ? NULL : $attributes['required'] = $element['#required'];
  empty($element['#checked']) ? NULL : $attributes['checked'] = 'checked';
  empty($element['#size']) ? NULL : $attributes['size'] = $element['#size'];
  empty($element['#maxlength']) ? NULL : $attributes['maxlength'] = $element['#maxlength'];

  return $attributes;
}

/**
 * Implements theme_form().
 */
function cellular_form($vars) {
  $element = $vars['element'];
  // $element['#attributes']['class'][] = 'cell';
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  $output = '<form' . drupal_attributes($element['#attributes']) . '>';
  $output .= $element['#children'] . '</form>';

  return $output;
}

/**
 * Implements theme_container().
 */
function cellular_container(&$vars) {
  $element = $vars['element'];
  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = array('center');
    // Assign an html ID if not present.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
  }

  return $element['#children'];
}

/**
 * Implements theme_form_element().
 */
function cellular_form_element(&$vars) {
  $element = $vars['element'];
  $output = '';
  /* May decide to include later:
    // $element['#theme_wrappers'] = NULL;
    // $attributes['class'] = array();
    // isset($element['#name']) ?
    // $attributes['class'][] = 'form-' . strtr($element['#name'], array(
    // ' ' => '-', '_' => '-', '[' => '-', ']' => ''))
    // : NULL;
    // $element['#theme_wrappers'] = NULL;
   */
  isset($element['#disabled']) ?
  $element['#attributes']['class'][] = 'disabled' : NULL;

  $prefix = isset($element['#field_prefix']) ?
  '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : NULL;
  $suffix = isset($element['#field_suffix']) ?
  '<span class="field-suffix">' . $element['#field_suffix'] . '</span>' : NULL;

  if (isset($element['#title_display'])) {
    switch ($element['#title_display']) {
      case 'before':
      case 'invisible':
        $output .= ' ' . theme('form_element_label', $vars);
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;

      case 'after':
        $output .= ' ' . $prefix . $element['#children'] . $suffix;
        $output .= ' ' . theme('form_element_label', $vars) . "\n";
        break;

      case 'none':
      case 'attribute':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }

  isset($element['#description']) ?
  $output .= '<div class="description">' . $element['#description'] . "</div>\n" : NULL;

  return $output;
}

/**
 * Implements theme_button().
 */
function cellular_button(&$vars) {
  $element = $vars['element'];
  $output = '';
  $element['#attributes']['type'] = 'submit';
  $element['#attributes']['class'][] = 'button';

  element_set_attributes($element, array('id', 'name', 'value'));

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output;
}

/**
 * Implements theme_fieldset().
 */
function cellular_fieldset(&$vars) {
  $element = $vars['element'];
  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  !empty($element['#title']) ?
  $output .= '<legend>' . $element['#title'] . "</legend>\n" : NULL;
  !empty($element['#description']) ?
  $output .= '<div class="description">' . $element['#description']
  . "</div>\n" : NULL;

  // Add form elements.
  $output .= $element['#children'];

  !empty($element['#value']) ?
  $element['#value'] . "\n" : NULL;

  $output .= "</fieldset>\n";

  return $output;
}

/**
 * Implements theme_select().
 */
function cellular_select(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'select';

  $output .= '<select' . drupal_attributes($attributes) . ">\n";
  $output .= form_select_options($element) . "\n";
  $output .= "</select>\n";

  return $output;
}

/**
 * Implements theme_checkboxes().
 */
function cellular_checkboxes(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);

  $output .= "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ?
  $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Implements theme_checkbox().
 */
function cellular_checkbox(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'checkbox';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));
  $output .= "<input" . drupal_attributes($attributes) . " />";

  return $output;
}

/**
 * Implements theme_radios().
 */
function cellular_radios(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);

  $output .= "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ? $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Implements theme_radio().
 */
function cellular_radio(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'radio';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));
  $output .= "<input" . drupal_attributes($attributes) . " />";

  return $output;
}

/**
 * Implements theme_textfield().
 */
function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'text';

  $value = empty($element['#value']) ? '' : ' value="' . $element['#value'] . '"';

  $output .= '<input' . drupal_attributes($attributes) . $value . ' />';

  return $output;
}

/**
 * Implements theme_textarea().
 */
function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'textarea';

  $attributes['cols'] = isset($element['#cols']) ? $element['#cols'] : 60;
  $attributes['rows'] = isset($element['#rows']) ? $element['#rows'] : 5;

  $output .= '<textarea' . drupal_attributes($attributes) . '>';
  $output .= check_plain($element['#value']);
  $output .= '</textarea>';

  return $output;
}


/*
 * @see file: preprocess/theme_pager.inc
 * Drupal pager, basically ripped off from Tao :)...
 */

/**
 * Implements theme_pager().
 */
function cellular_pager($vars) {
  global $pager_page_array, $pager_total;
  $tags = $vars['tags'];
  $element = $vars['element'];
  $parameters = $vars['parameters'];
  $quantity = $vars['quantity'];

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // Current is the page we are currently paged to:
  $pager_current = $pager_page_array[$element] + 1;
  // First is the first page listed by this pager piece (re quantity):
  $pager_first = $pager_current - $pager_middle + 1;
  // Last is the last page listed by this pager piece (re quantity):
  $pager_last = $pager_current + $quantity - $pager_middle;
  // Max is the maximum page number:
  $pager_max = $pager_total[$element];
  // End of marker calculations.
  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.
  $li_first = theme('pager_first', array(
    'text' => (isset($tags[0]) ? $tags[0] : t('« first')),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => (isset($tags[3]) ? $tags[3] : t('next ›')),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => (isset($tags[4]) ? $tags[4] : t('last »')),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array('class' => array('pager-first'), 'data' => $li_first);
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i !== $pager_max) {
      if ($i > 1) {
        $items[] = array('class' => array('pager-ellipsis'), 'data' => '…');
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($pager_current - $i),
              'parameters' => $parameters,
            )),
          );
        }
        if ($i === $pager_current) {
          $items[] = array('class' => array('pager-current'), 'data' => $i);
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array(
              'text' => $i,
              'element' => $element,
              'interval' => ($i - $pager_current),
              'parameters' => $parameters,
            )),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array('class' => array('pager-ellipsis'), 'data' => '…');
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array('class' => array('pager-next'), 'data' => $li_next);
    }
    if ($li_last) {
      $items[] = array('class' => array('pager-last'), 'data' => $li_last);
    }

    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array(
        'class' => array(
          'pager',
        ),
      ),
    ));
  }
}


/*
 * @see file: preprocess/panels.inc
 * Alter specific forms.
 */

/**
 * Alter the default Panels markup.
 */
function cellular_panels_default_style_render_region($vars) {
  // dpm($vars);
  $output = '';
  // $output .= implode('<div class="panel-separator"></div>', $vars['panes']);
  // Remove the panel separator.
  return implode($output, $vars['panes']);
}


/**
 * Alter the panelseverywhere header markup.
 */
function cellular_preprocess_pane_header(&$vars) {
  /*
  //function template_preprocess_pane_header(&$vars) {
  $vars['site_name'] = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');

  $vars['site_slogan'] = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
  $vars['main_menu'] = cellular_main_menu($vars);
  // dpm($vars);
   */
}


/*
 * @see file: preprocess/social.inc
 * Generate social media links.
 */

/**
 * Generate links for social media.
 *
 * @param array $links
 *   Array of links to add.
 * @param array $parent
 *   Media block array used to wrap links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_build_links($links, $parent) {
  $output = '';
  foreach ($links as $link) {
    if (!empty($link['tag'])) {
      // Use preformatted html if set.
      $output .= "\n " . $link['tag'] . "\n";
    }
    else {
      // Or create link using key's attributes:
      if (!empty($link['url'])) {
        $text = $parent['link_text'] . $link['name'];
        $output .= l(t($text), $link['url'], array(
          'attributes' => array(
            'class' => array(
              $parent['link_class'],
              $link['class'],
        ))));
      }
    }

    if (!empty($link['script'])) {
      // Add script if provided.
      drupal_add_js($link['script'], array(
        'type' => 'inline',
        'group' => JS_THEME,
        'weight' => isset($link['weight']) ? $link['weight'] : 100,
      ));
    }
  }
  return $output;
}

/**
 * Collect Social Media share settings.
 *
 * @param string $type
 *   String used to select the array to return ("follow" || "share").
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_settings($type) {
  switch ($type) {
    case 'follow':
      $output = array(
        'title' => theme_get_setting('sm_follow_title'),
        'fb' => theme_get_setting('follow_facebook'),
        'google' => theme_get_setting('follow_google_plus'),
        'twitter' => theme_get_setting('follow_twitter'),
        'linkedin' => theme_get_setting('follow_linkedin'),
        'github' => theme_get_setting('follow_github'),
      );
      break;

    case 'share':
      $output = array(
        'title' => theme_get_setting('sm_share_title'),
        'fb' => theme_get_setting('share_facebook'),
        'google' => theme_get_setting('share_google_plus'),
        'twitter' => theme_get_setting('share_twitter'),
        'linkedin' => theme_get_setting('share_linkedin'),
        'pinterest' => theme_get_setting('share_pinterest'),
        'reddit' => theme_get_setting('share_reddit'),
      );
      break;
  }

  return $output;
}

/**
 * Collect Social Media URLs.
 *
 * @param string $type
 *   String ("follow" || "share") used to select the array to return.
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_urls($type) {
  switch ($type) {
    case 'follow':
      $output = array(
        'fb' => theme_get_setting('follow_facebook_url'),
        'google' => theme_get_setting('follow_google_plus_url'),
        'twitter' => theme_get_setting('follow_twitter_url'),
        'linkedin' => theme_get_setting('follow_linkedin_url'),
        'github' => theme_get_setting('follow_github_url'),
      );
      break;

    case 'share':
      $output = array(
        'fb' => theme_get_setting('share_facebook_url'),
        'google' => theme_get_setting('share_google_plus_url'),
        'twitter' => theme_get_setting('share_twitter_url'),
        'linkedin' => theme_get_setting('share_linkedin_url'),
        'pinterest' => theme_get_setting('share_pinterest_url'),
        'reddit' => theme_get_setting('share_reddit_url'),
      );
  }

  return $output;
}

/**
 * Generate Social media follow links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_follow() {
  if (theme_get_setting('social_media_follow') == 1) {
    $set = cellular_sm_settings('follow');
    $url = cellular_sm_urls('follow');

    $output = '';
    $block_title = $set['title'];
    $media_block = array(
      'title' => !empty($block_title) ? "<h3>$block_title</h3>\n" : '',
      'id' => 'social-media-follow',
      'link_class' => 'social icon',
      'link_text' => 'Share this page on ',
    );

    $links = array();
    $set['fb'] == 1 ? $links['facebook'] = array(
      'url' => $url['fb'],
      'class' => 'facebook',
      'name' => 'Facebook',
    ) : NULL;
    $set['google'] == 1 ? $links['google+'] = array(
      'url' => $url['google'],
      'class' => 'google',
      'name' => 'Google+',
    ) : NULL;
    $set['twitter'] == 1 ? $links['twitter'] = array(
      'url' => $url['twitter'],
      'class' => 'twitter-bird',
      'name' => 'Twitter',
    ) : NULL;
    $set['linkedin'] == 1 ? $links['linkedin'] = array(
      'url' => $url['linkedin'],
      'class' => 'linkedin',
      'name' => 'LinkedIn',
    ) : NULL;
    $set['github'] == 1 ? $links['github'] = array(
      'url' => $url['github'],
      'class' => 'github-octo',
      'name' => 'Github',
    ) : NULL;

    $content = cellular_build_links($links, $media_block);
    if (!empty($content)) {
      $output .= "\n<div id=\"" . $media_block['id'] . "\">\n";
      $output .= $media_block['title'] . $content . "\n</div>\n";
    }

    return $output;
  }
}

/**
 * Generate Social media share links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_share() {
  if (theme_get_setting('social_media_share') == 1) {
    global $base_url;
    $set = cellular_sm_settings('share');
    $output = '';
    $page = array(
      'url' => $base_url . '/' . current_path(),
      'title' => drupal_get_title(),
    );
    $block_title = theme_get_setting('sm_share_title');
    $media_block = array(
      'title' => !empty($block_title) ? "<h3>$block_title</h3>\n" : '',
      'id' => 'social-media-share',
      'link_class' => 'social icon',
      'link_text' => 'Share this page on ',
    );

    $links = array();
    $set['google'] == 1 ? $links['google+'] = array(
      'name' => 'Google+',
      'script' => NULL,
      'url' => 'http://plus.google.com/share?url=' . $page['url'],
      'class' => 'google',
    ) : NULL;
    $set['twitter'] == 1 ? $links['twitter'] = array(
      'name' => 'Twitter',
      'script' => NULL,
      'url' => 'https://twitter.com/share',
      'class' => 'twitter-bird',
    ) : NULL;
    $set['linkedin'] == 1 ? $links['linkedin'] = array(
      'name' => 'LinkedIn',
      'url' => 'http://www.linkedin.com/shareArticle?mini=true&url=' .
      $page['url'] . '&title=' . $page['title'] . '&source=' . $base_url,
      'class' => 'linkedin',
    ) : NULL;
    $set['pinterest'] == 1 ? $links['pinterest'] = array(
      'name' => 'Pinterest',
      'url' => 'http://pinterest.com/pin/create/bookmarklet/?media=&url=' .
      $page['url'] . '&is_video=false&description=' . $page['title'],
      'class' => 'pinterest',
    ) : NULL;
    $set['reddit'] == 1 ? $links['reddit'] = array(
      'name' => 'Reddit',
      'url' => 'http://www.reddit.com/submit?url=' . $page['url'],
      'class' => 'reddit',
    ) : NULL;

    if ($set['fb'] == 1) {
      // Set variables to appease PAReview.
      $fbscript = '(function(d, s, id) {
          var js, fjs = d.getElementsByTagName(s)[0];
          if (d.getElementById(id)) return;
          js = d.createElement(s); js.id = id;
          js.src = "//connect.facebook.net/en_US/all.js#xfbml=1";
          fjs.parentNode.insertBefore(js, fjs);
          }(document, \'script\', \'facebook-jssdk\'));';
      $fbtag = '<div class="fb-like" data-href="' . $page['url'] . '"
          data-layout="button" data-action="like" data-show-faces="false"
          data-share="true"></div><div id="fb-root"></div>';

      $links['facebook'] = array(
        // Facebook javascript.
        'script' => $fbscript,
        // Set fb markup.
        'tag' => $fbtag,
        // Push script to end of body.
        'weight' => 1000,
      );
    }

    $content = cellular_build_links($links, $media_block);

    if (!empty($content)) {
      $output .= "\n<div id=\"" . $media_block['id'] . "\">\n";
      $output .= $media_block['title'] . $content . "\n</div>\n";
    }

    return $output;
  }
}


/*
 * @see file: preprocess/process.inc
 * Cellular process functions.
 */

/**
 * Implements template_process_html().
 */
function cellular_process_html(&$vars) {
  // Push modified styles to page.
 // $vars['styles'] = drupal_get_css($vars['css'], FALSE);
}

/**
 * Implements template_process_page().
 */
function cellular_process_page(&$vars) {
  // Dev.
  cellular_dev($vars);
}


/*
 * @see file: preprocess/views.inc
 * Preprocess functions for Views.
 */

/**
 * Set hooks for view preprocess functions.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_views_view(&$vars) {
  if (isset($vars['view']->name)) {
    $function = 'cellular_preprocess_views_view__' . $vars['view']->name;
    if (function_exists($function)) {
      $function($vars);
    }
  }
}
