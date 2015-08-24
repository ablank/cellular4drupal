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
 * Initialize constants & global variables.
 */

define('CURRENT_THEME_PATH', cellular_theme_path());
define('CELLULAR_CSS_EXT', cellular_ext('css'));
define('CELLULAR_JS_EXT', cellular_ext('js'));
define('CELLULAR_INPUT_SIZE', 20);
// May convert to use Libraries module at some point...
define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');


/*
 * @see file: preprocess/fn.inc
 * Cellular utility functions.
 */

/**
 * Get path to the active theme.
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
  $mq = array(
    'mobile' => theme_get_setting('mq_mobile'),
    'normal' => theme_get_setting('mq_normal'),
    'large' => theme_get_setting('mq_large'),
  );

  return $mq;
}

/**
 * Get file extensions as .min based on theme settings.
 *
 * @param $type string
 *  Type of file to test settings for, either css or js.
 *
 * @return array
 *  Extension string for each file type.
 */
function cellular_ext($type){
  $settings = array(
    'css' => theme_get_setting('min_style') == 1 ? '.min.css' : '.css',
    'js' => theme_get_setting('min_script') == 1 ? '.min.js' : '.js',
  );

  return $settings[$type];
}

/**
 * Add <link> & <meta> tags from an array.
 *
 * @param array $array
 *   Array of tags to add to document <head>.
 */
function cellular_build_head_tags($array) {
  foreach ($array as $meta => $val) {
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
 * Print variables for development as message, useful if devel isn't active.
 *
 * @param array $element
 *   Element to test and return variables of.
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
 */


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
    // Set data source as CDN or local host.
    if (isset($style['cdn'])) {
      $data = $style['cdn'];
    }
    elseif (isset($style['file'])) {
      $data = $cellular == TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH;
      $data .= '/css/' . $style['file'];
    }
    if (!empty($data)) {
      // Set stylesheet properties.
      $style['data'] = $data;
      $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
      $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
      $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
      $style['weight'] = isset($style['weight']) ? $style['weight'] : 1;
      $style['type'] = isset($style['cdn']) ? 'external' : 'file';
      $style['media'] = isset($style['media']) ? $style['media'] : 'all';
      $style['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);
      // Add stylesheet to $css.
      $css[$data] = $style;
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
function cellular_remove_css(&$css, $exclude) {
  foreach ($exclude as $module => $stylesheet) {
    // Remove multiple stylesheets attached by module.
    if (is_array($stylesheet)) {
      foreach ($stylesheet as $style) {
        unset($css[drupal_get_path('module', $module) . '/' . $style]);
      }
    }
    // Remove individual module stylesheet.
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
function cellular_override_css(&$css, $style, $cellular = FALSE) {
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
      $path = $cellular === TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH;
      // Or set data to local file.
      $data = $path . '/css/' . $style['file'];
    }
    // Set stylesheet properties.
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
  $exclude = array();
  // Nuke all css not a member of group CSS_THEME:
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
  // Nuke SYSTEM_CSS.
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
        'system.messages.css',
        'system.theme.css',
        // Remove menu.css for anonymous users.
        user_is_logged_in() ? NULL : 'system.menus.css',
      ),
      'block' => 'block.css',
      'colorbox' => 'styles/default/colorbox_style.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'file' => 'file.css',
      'image' => 'image.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'media' => 'css/media.css',
      'node' => 'node.css',
      'panels' => 'css/panels.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
}

/**
 * Add critical styles (above the fold) inline.
 * @see http://fourword.fourkitchens.com/article/use-grunt-and-advagg-inline-critical-css-drupal-7-theme
 */
function cellular_critical_css($vars) {
  if (theme_get_setting('inline_critical_css') == 1) {
    $ext = CELLULAR_CSS_EXT;
    $critical_opts = array(
      'type' => 'inline',
      'scope' => 'header',
      'group' => CSS_SYSTEM,
      'weight' => -1000,
      'preprocess' => FALSE,
    );

    if ($vars['is_front'] == 1) {
      $critical_file = 'critical-front' . $ext;
    }
    else {
      $critical_file = 'critical' . $ext;
    }

    // Add the stylesheet inline.
    drupal_add_css(file_get_contents(CURRENT_THEME_PATH . '/css/' . $critical_file), $critical_opts);
  }
}


/*
 * @see file: preprocess/fn.form.inc
 * Cellular form utility functions.
 */

/**
 * Array of attributes to be rendered.
 *
 * @param array $element
 *   Variable on which to set attributes.
 *
 * @return array
 *   Attributes to render.
 */
function cellular_form_element_attributes($element) {
  // $element['#theme_wrappers'] = NULL;
  $attributes = array();
  //empty($element['#value']) ? NULL : $attributes['value'] = $element['#value'];
  empty($element['#name']) ? NULL : $attributes['name'] = $element['#name'];
  empty($element['#id']) ? NULL : $attributes['id'] = $element['#id'];
  empty($element['#title']) ? NULL : $attributes['title'] = $element['#title'];
  empty($element['#required']) ? NULL : $attributes['required'] = $element['#required'];
  empty($element['#size']) ? NULL : $attributes['size'] = $element['#size'];
  empty($element['#maxlength']) ? NULL : $attributes['maxlength'] = $element['#maxlength'];
  empty($element['#checked']) ? NULL : $attributes['checked'] = TRUE;
  empty($element['#attributes']['class']) ? NULL : $attributes['class'] = implode(' ', $element['#attributes']['class']);

  return $attributes;
}

/**
 * Generate markup for theme_radios() & theme_checkboxes().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinputs(&$element) {
  $attributes = cellular_form_element_attributes($element);

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ? $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Generate markup for theme_radio() & theme_checkbox().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinput($element, $type) {
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = $type;
  $attributes['value'] = $element['#return_value'];

  return "<input" . drupal_attributes($attributes) . " />";
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
 * Configure links to CDN sources.
 *
 * @return array
 *   CDN URLs used to update jQuery & jQuery.ui
 */
function cellular_cdn() {

  $jq = cellular_jquery_info();
  $ui = $jq['ui'];
  $ext = CELLULAR_JS_EXT;
  /* Available cdns:
   * //ajax.googleapis.com/ajax/libs/jquery/1.10.4/jquery.min.js
   * //ajax.aspnetcdn.com/ajax/jquery.ui/1.10.4/jquery-ui.min.js
   * //cdnjs.cloudflare.com/ajax/libs/jqueryui/1.10.4/jquery-ui.min.js
   */
  $networks = array(
    'jquery' => array(
      'base_url' => '//code.jquery.com/',
      'jquery' => 'jquery-' . $jq['version'] . $ext,
      'jqueryui' => 'ui/' . $ui['version'] . '/jquery-ui' . $ext,
      'theme' => 'ui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . CELLULAR_CSS_EXT,
    ),
    'google' => array(
      'base_url' => '//ajax.googleapis.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery' . $ext,
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui' . $ext,
      'theme' => 'jqueryui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . CELLULAR_CSS_EXT,
    ),
    'microsoft' => array(
      'base_url' => '//ajax.aspnetcdn.com/ajax/',
      'jquery' => 'jquery/jquery-' . $jq['version'] . $ext,
      'jqueryui' => 'jquery.ui/' . $ui['version'] . '/jquery-ui' . $ext,
      'theme' => 'jquery.ui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . CELLULAR_CSS_EXT,
    ),
    'cloudflare' => array(
      'base_url' => '//cdnjs.cloudflare.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery' . $ext,
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui' . $ext,
      // Themes aren't provided by cdnjs.
      'theme' => 'jqueryui/' . $ui['version'] . '/css/jquery-ui' . CELLULAR_CSS_EXT,
    ),
  );

  return $networks[$jq['cdn']];
}

/**
 * Update jQuery.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 */
function cellular_jquery_update(&$javascript) {
  $jq = cellular_jquery_info();
  // Override jQuery.
  $jquery = array(
    'default' => 'misc/jquery.js',
    'file' => 'jquery-' . $jq['version'] . '.min.js',
    'version' => $jq['version'],
    'every_page' => TRUE,
    'group' => JS_LIBRARY,
    'weight' => -100,
  );
  // Set CDN or local source.
  if ($jq['use_cdn'] == 1) {
    $cdn = cellular_cdn();
    $jquery['object'] = 'jQuery';
    $jquery['cdn'] = $cdn['base_url'] . $cdn['jquery'];
  }
  // Override jQuery.
  cellular_js_override($javascript, $jquery, TRUE);
  // Update the Drupal's default jQuery plugins.
  if (theme_get_setting('jquery_plugins_update') == 1) {
    cellular_update_plugins($javascript, $jquery);
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
          'object' => "jQuery.ui",
          'version' => $jq['ui']['version'],
          'group' => JS_LIBRARY,
          'every_page' => FALSE,
          'weight' => isset($javascript[$default]['weight']) ? $javascript[$default]['weight'] : -99,
          'file' => "jquery-ui/" . $jq['ui']['version'] . "/minified/jquery.$widget.min.js",
          'preprocess' => TRUE,
          'browsers' => array('IE' => TRUE, '!IE' => TRUE),
        ),
      );

      if (theme_get_setting('jquery_cdn') == 1) {
        $cdn = cellular_cdn();
        // If updating from cdn unset each widget so a single call is made for all widgets.
        unset($javascript[$default]);
        // Set cdn source.
        $script['jqueryui']['cdn'] = $cdn['base_url'] . $cdn['jqueryui'];
        // Set lower weight so cdn is delivered before fallbacks.
        $script['jqueryui']['weight'] = -10;
        // Add single link to cdn, with local fallback to each file.
        cellular_add_js($script, TRUE);
      }
      else {
        // Use local source, only include only scripts that are needed.
        // Recommend AdvAgg, or use core aggregation in
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
  $ext = CELLULAR_CSS_EXT;
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
      $jq = cellular_jquery_info()['ui'];
      $style = array(
        'ui' => array(
          'default' => $default,
          'version' => $jq['version'],
          'group' => CSS_SYSTEM,
          'every_page' => FALSE,
          'weight' => isset($css[$default]['weight']) ? $css[$default]['weight'] : -9,
          'file' => NULL,
          'preprocess' => TRUE,
        ),
      );
      // Remove default after updating styles.
      unset($css[$default]);

      if ($jq['theme'] === 'custom') {
        // Set path to local custom file if selected.
        $v = $jq['version'] === '1.10.4' ? '1.10' : '1.9';
        $style['ui']['file'] = "/jquery-ui/jquery-ui.$v.$ext";

        cellular_add_css($css, $style);
      }
      else {
        $ui_path = $ui['path'] . $jq['version'] . '/' . $jq['theme'] . '/';
        $style['ui']['file'] = $ui_path . 'jquery-ui' . $ext;
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
 * @see file: preprocess/fn.js.inc
 * Cellular javascript functions.
 */

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
    // Test if local or external source is provided.
    if (!empty($script['cdn'])) {
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH;
      $data .= '/js/' . $script['file'];
    }
    // Set script attributes.
    $script['type'] = !empty($script['cdn']) ? 'external' : 'file';
    $script['scope'] = !empty($script['scope']) ? $script['scope'] : 'header';
    $script['group'] = !empty($script['group']) ? $script['group'] : JS_THEME;
    $script['every_page'] = !empty($script['every_page']) ? $script['every_page'] : TRUE;
    $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
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
      'group' => !empty($script['group']) ? $script['group'] : JS_DEFAULT,
      'weight' => !empty($script['weight']) ? $script['weight'] + 0.1 : 0,
      'type' => 'inline',
      'every_page' => !empty($script['every_page']) ? $script['every_page'] : FALSE,
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
  if (!empty($javascript[$script['default']])) {
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


/*
 * @see file: preprocess/fn.menu.inc
 * Cellular menu functions.
 */

/**
 * Returns full Main Menu tree instead of top-level only links.
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
  /*
   Work in progress to generate id from template function
   ... currently wrapping menu in <div id="nav"/> page template.

  //$vars['main_menu']['#theme_wrappers'] = array('cellular_menu_tree__main_menu');

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

/**
 * Implements links__system_main_menu.
function cellular_links__system_main_menu($vars) {
  $output = "<ul id=\"nav\">\n";
  foreach ($vars['links'] as $key => $link) {
    $output .= "<li>" . l($link['title'], $link['href']) . "</li>";
  }
  $output .= "</ul>\n";

  return $output;
}
*/

/*
 * @see file: preprocess/fn.preprocess.inc
 * Cellular functions to set content attributes.
 */

/**
 * Add HTTP Response Headers.
 */
function cellular_http_headers() {
  // Try to prevent clickjacking.
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

  $vars['doctype'] = "<!DOCTYPE html>\n";
  $html_attributes = array(
    'lang' => $language->language,
    'xml:lang' => $language->language,
    'dir' => $language->dir,
  );
  // Check support for RDF, adding namespace if needed.
  if (module_exists('rdf')) {
    // Set namespace.
    $html_attributes['xmlns'] = 'http://www.w3.org/1999/xhtml';
  }

  $vars['html_attributes'] = drupal_attributes($html_attributes);
}

/**
 * Convert xmlns to profile.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_rdf(&$vars) {
  // Add extra namespaces if needed:
  // $vars['rdf_namespaces'] .= "\nxmlns:og=\"http://opengraphprotocol.org/schema/\"";
  // Check support for RDF & add attributes:
  if (module_exists('rdf')) {
    // @see http://phase2technology.com/?p=552
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
   * whichever value is last, so 'default' is given highest weight.
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
      $favicon['href'] = $GLOBALS['base_url'] . '/' . CURRENT_THEME_PATH . '/assets/favicons/' . $favicon['href'];
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

/* Under development, process vars for comment & node */

/**
 *
 */
function cellular_author_info(&$vars) {
  // Author info
  $aid = user_load($vars['uid']);
  if (!empty($aid)) {
    $author = theme('user_picture', array('account' => $aid));
    $author .= $aid->name;
  }

  // Push formatted author block to $vars array.
  return $author;
}

function cellular_post_date($node) {
  // Date node was created.
  $date = "\n<span class=\"day\">" . date("j", $node->created) . "</span>\n";
  $date .= "<span class=\"month\">" . date("M", $node->created) . "</span>\n";
  $date .= "<span class=\"year\">" . date("Y", $node->created) . "</span>\n";

  return $date;
}

/**
 * Set path to page-error.tpl if header error code is returned.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_error_page(&$vars) {
  $http_status = drupal_get_http_header("status");
  // Set error page template if error.
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


/*
 * @see file: preprocess/alter.inc
 * Alter misc. hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 */
function cellular_html_head_alter(&$head_elements) {
  // Remove unwanted meta tags.
  $exclude = array(
    'metatag_generator'
  );

  foreach ($exclude as $element) {
    if (isset($head_elements[$element])) {
      unset($head_elements[$element]);
    }
  }
}

/**
 * Implements hook_page_alter().

function cellular_page_alter(&$page) {}
*/


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

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  if (!empty($plugins)) {
    cellular_add_css($css, $plugins, TRUE);
  }
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_update_css($css);
  }
  // Check for minified or standard style extension.
  $ext = CELLULAR_CSS_EXT;
  // Add default stylesheets to theme, paths are relative to /YourTheme/css/
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
}


/*
 * @see file: preprocess/form_alter.inc
 * Alter specific forms.
 */

/**
 * Implements hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id) {
  $size = CELLULAR_INPUT_SIZE;

  //drupal_set_message('<code><pre>' . print_r($form) . '</pre></code>');
  switch ($form['#id']) {
    /* Search page. */
    case 'search-form':
      $form['#attributes']['class'][] = 'site-search';
      break;

    /* Search block. */
    case 'search-block-form':
      $form['#attributes']['class'][] = 'site-search';
      $form[$form_id]['#title'] = t('Search this site');
      $form[$form_id]['#default_value'] = t('Keywords');
      $form[$form_id]['#type'] = 'textfield';
      $form[$form_id]['#size'] = $size;
      // Submit button.
      $form['actions']['submit']['#type'] = 'submit';
      $form['actions']['submit']['#value'] = t('Search');
      break;

    /* User Login block. */
    case 'user-login-form':
      $orient = theme_get_setting('login_block_orientation');
      $form['#attributes']['class'][] = $orient;

      switch ($orient) {
        case 'horizontal':
          break;

        case 'vertical':
        default:
          $form['actions']['submit']['#attributes']['class'][] = 'clearfix';
          break;
      }
      
      // Username
      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => t('Username'),
        '#size' => $size,
      );
      // Password
      $form['pass'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#default_value' => t('Password'),
        '#size' => $size,
      );
      // Submit button
      $form['actions']['submit']['#attributes']['#value'] = t('Log in');

      /* Request New Password & Register New Account Links. */
      $login_links = NULL;
      $user_reg = theme_get_setting('login_block_register');
      $user_pass = theme_get_setting('login_block_password');

      if (isset($user_reg) || isset($user_pass)) {
        $login_links = '<div class="login-links">';
        if (!empty($user_reg)) {
          $login_links .= l(t('Register'), "user/register", array(
            'attributes' => array(
              'class' => array('register'),
          )));
        }
        if (!empty($user_pass)) {
          $login_links .= l(t('Forgotten Password?'), "user/password", array(
            'attributes' => array(
              'class' => array('password'),
          )));
        }
        $login_links .= '</div>';
      }
      $form['links']['#markup'] = $login_links;
      break;

    /* Comment Form. */
    case 'comment-form':
      $form['comment_body']['und'][0]['#default_value'] = t('I think...');
      // Hide unwanted form fields.
      $form['author']['#access'] = FALSE;
      $form['subject']['#access'] = FALSE;
      $form['actions']['preview']['#access'] = FALSE;
      // Customize Submit button.
      $form['actions']['submit']['#value'] = t('Submit');
      $form['actions']['submit']['#attributes']['class'][] = 'right';
      // Remove text format option descriptions.
      $form['comment_body']['#after_build'][] = 'cellular_form_format_opt';
      break;
  }
}


/*
 * @see file: preprocess/js_alter.inc
 * Add/Update/Delete javascript.
 */

/**
 * Implements hook_js_alter().
 */
function cellular_js_alter(&$javascript) {
  // Pass variables to client as drupal.settings.
  cellular_js_settings();
  // Add Modernizr & query based on theme settings.
  theme_get_setting('modernizr') == 1 ? cellular_modernizr_default() : NULL;
  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
  }
  // Add js for plugins after overriding default js.
  cellular_add_js(cellular_plugins_js(), TRUE);

  // dpm($javascript);
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js_settings() {
  $ext = CELLULAR_JS_EXT;

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

  $scripts = array();
  // Add script by extension. The minified source should compile ALL js in
  // /yourTheme/js/ into script.min.js.
  // Add Cellular UI
  if (theme_get_setting('cellularui') == 1) {
    $scripts['cellularui'] = array(
      'object' => 'cellular',
      'file' => 'cellular-ui/jquery.cellular-ui' . $ext,
      'weight' => 98,
    );
    // Add to Drupal.settings.
    drupal_add_js(array('cellular' => array('cellularui' => TRUE)), 'setting');
  }
  // Add plugins.js if plugins are set.
  if ($js_plugins || theme_get_setting('cellularui') == 1) {
    $scripts['plugins'] = array(
      'file' => 'plugins' . $ext,
      'group' => JS_DEFAULT,
      'weight' => 99,
    );
  }
  // Add script.js.
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
  $ext = CELLULAR_CSS_EXT;
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
 * Update Drupal's default jQuery plugins.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 *
 * @param array $jquery
 *   jQuery version info.
 */
function cellular_update_plugins(&$javascript, $jquery) {
  $dir = 'drupal/';
  $plugins = array(
    'drupal' => array(
      'default' => 'misc/drupal.js',
      'version' => '7.38',
      'file' => 'drupal',
      'weight' => 10,
    ),
    'ajax' => array(
      'default' => 'misc/ajax.js',
      'version' => '7.38',
      'file' => 'drupal.ajax',
    ),
    'progress' => array(
      'default' => 'misc/progress.js',
      'version' => '7.38',
      'file' => 'drupal.progress',
    ),
    'bbq' => array(
      'default' => 'misc/jquery.ba-bbq.js',
      'version' => '1.3',
      'file' => 'jquery.ba-bbq',
    ),
    'cookie' => array(
      'default' => 'misc/jquery.cookie.js',
      'version' => '1.4.1',
      'file' => 'jquery.cookie',
    ),
    'form' => array(
      'default' => 'misc/jquery.form.js',
      'version' => '3.48',
      'file' => 'jquery.form',
    ),
    'once' => array(
      'default' => 'misc/jquery.once.js',
      'version' => '1.2.6',
      'file' => 'jquery.once',
    ),
  );

  foreach ($plugins as $plugin) {
    $plugin['file'] = $dir . $plugin['file'] . CELLULAR_JS_EXT;
    cellular_js_override($javascript, $plugin, TRUE);
  }
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *   Associative array of plugin data.
 */
function cellular_plugins_js() {
  $jquery = cellular_jquery_info();
  $dir = 'plugins/';
  $ext = CELLULAR_JS_EXT;
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();
  theme_get_setting('modernizr') == 1 ? $js_plugins['modernizr'] = array(
    'group' => JS_LIBRARY,
    'object' => 'Modernizr',
    'file' => 'modernizr.js',
    'version' => '2.8.3',
    'weight' => -1000,
  ) : NULL;

    // Add migrate to prevent plugins from breaking with jQuery > v1.9.
  theme_get_setting('jquery_migrate') == 1 && floatval(substr($jquery['version'], 2)) >= 9 ?
  $js_plugins['migrate'] = array(
      'version' => '1.2.1',
      'file' => 'plugins/jquery.migrate.min.js',
      'group' => JS_LIBRARY,
      'weight' => -96,
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
  $plugin_css = array(
    'prism' => theme_get_setting('prism') == 1 ? array(
      'file' => 'prism.css',
      'weight' => -10,
    ) : NULL,
  );

  return $plugin_css;
}


/*
 * @see file: preprocess/preprocess.inc
 * Template preprocess functions.
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
  
    $site_name = variable_get('site_name', "Just another Drupal Site");  
    setcookie($site_name . 'visited', 'TRUE', time() + (86400 * 30), '/');
  
  if (isset($_COOKIE['visited'])) {
    drupal_set_message("OK, Cookie: ' " . $_COOKIE['visited'] . " ' set!");
  }
}

/**
 * Implements template_preprocess_node().
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];
  // Set attributes.
  $vars['title_attributes_array']['class'][] = 'node-title';
  $vars['content_attributes_array']['class'][] = 'node-content';
  /* Set additional template variables. */
  // Date node was created.
  $date = "\n<span class=\"day\">" . date("j", $node->created) . "</span>\n";
  $date .= "<span class=\"month\">" . date("M", $node->created) . "</span>\n";
  $date .= "<span class=\"year\">" . date("Y", $node->created) . "</span>\n";
  // Author info
  $aid = user_load($vars['uid']);
  $author = theme('user_picture', array('account' => $aid));
  $author .= $aid->name;

  // Push variables to the node array.
  $vars['post_date'] = $date;
  $vars['author'] = $author;
}

/**
 * Implements template_preprocess_block().
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  // Hide block titles in the header regions.
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
  $comment = $vars ['elements']['#comment'];
  //dpm($comment);
  // Set the template used by comments.
  $vars['theme_hook_suggestions'][] = 'comment';
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';

  if (!empty($vars['new'])) {
    $vars['classes_array'][] = 'new';
  }
  $submitted = '';
  if (!empty($vars['author'])) {
    $submitted .= '<span class="comment-author">';
    $submitted .= $vars['picture'];
    $submitted .= '<div>' . t('Posted by !username', array(
      '!username' => $vars['author'],
    )) . '</div>';
    $submitted .= '</span>';
  }

  $submitted .= '<span class="comment-date">' . $vars['created'] . '</span>';

  // No need to link comments...
  $vars['title'] = $comment->subject;

  $vars['submitted'] = $submitted;
}

/**
 * Implements template_preprocess_comment_wrapper.
 */
function cellular_preprocess_comment_wrapper(&$vars) {
  $vars['classes_array'][] = 'clearfix';
}

/*
 * @see file: preprocess/preprocess.page.inc
 * Template page preprocess functions.
 */

/**
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Set main_menu as full-tree or top-level as defined in settings.
  cellular_main_menu($vars);
  // Set classes for content & sidebar regions.
  cellular_test_sidebar($vars);
  // Link site name to frontpage.
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links.
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to page templates.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright info if provided.
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
  "&copy; " . date("Y") . " $copyright" : '';
  // Add template suggestion for custom content types(page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Automate error pages.
  cellular_error_page($vars);

  /* Work in progress... */
  // Panels everywhere page template suggestion.
  if (!empty(variable_get('panels_everywhere_site_template'))) {
    $vars['theme_hook_suggestions'][] = 'page__panels_everywhere';
  }
}

/**
 * Implements template_preprocess_maintenance_page().
 *
 * Duplicate page variables for the maintenance page.
 */
function cellular_preprocess_maintenance_page(&$vars) {
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Set main_menu as full-tree or top-level as defined in settings.
  cellular_main_menu($vars);
  // Set classes for content & sidebar regions.
  cellular_test_sidebar($vars);
  // Link site name to frontpage.
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links.
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to page templates.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright info if provided.
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
  "&copy; " . date("Y") . " $copyright" : '';
  // Add template suggestion for custom content types(page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Automate error pages.
  cellular_error_page($vars);

  /* Work in progress... */
  // Panels everywhere page template suggestion.
  if (!empty(variable_get('panels_everywhere_site_template'))) {
    $vars['theme_hook_suggestions'][] = 'page__panels_everywhere';
  }
}



/*
 * @see file: preprocess/theme.inc
 * Set element markup.
 */

/**
 * Implements theme_links().
 */
function cellular_links($vars) {
  global $language_url;
  $links = $vars ['links'];
  $attributes = $vars ['attributes'];
  $heading = $vars ['heading'];
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading ['level'];
      if (!empty($heading ['class'])) {
        $output .= drupal_attributes(array('class' => $heading ['class']));
      }
      $output .= '>' . check_plain($heading ['text']) . '</' . $heading ['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class [] = 'first';
      }
      if ($i == $num_links) {
        $class [] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET ['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class [] = 'active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l(ucfirst($link['title']), $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain(ucfirst($link['title']));
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

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
  // Generate markup.
  $output = "\n<form" . drupal_attributes($element['#attributes']) . ">\n";
  $output .= $element['#children'] . "\n</form>\n";

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

  if (isset($element['#disabled'])) {
    $element['#attributes']['class'][] = 'disabled';
  }

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

      case 'attribute':
      case 'none':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }
  if (!empty($element['#description'])) {
    $output .= "\n<div class=\"description\">\n" . $element['#description'] . "\n</div>\n";
  }

  return $output;
}

/**
 * Implements theme_button().
 */
function cellular_button(&$vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'submit';
  $element['#attributes']['class'][] = 'button';
  $element['#attributes']['class'][] = $element['#parents'][0];

  element_set_attributes($element, array('id', 'name', 'value'));

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'disabled';
  }
  /* // May add this back if I can get css styling dialed in...
    switch ($element['#parents'][0]) {
    case 'preview':
    case 'submit':
    $element['#attributes']['class'][] = 'right';
    break;

    case 'delete':
    default:
    $element['#attributes']['class'][] = 'left';
    break;
    }
   */

  return "\n<input" . drupal_attributes($element['#attributes']) . " />\n";
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
  $output .= '<div class="description">' . t($element['#description']) . "</div>\n" : NULL;
  // Add form elements.
  $output .= $element['#children'];
  $output .=!empty($element['#value']) ? $element['#value'] . "\n" : NULL;
  $output .= "</fieldset>\n";

  return $output;
}

/**
 * Implements theme_checkboxes().
 */
function cellular_checkboxes(&$vars) {

  return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_radios().
 */
function cellular_radios(&$vars) {

  return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_checkbox().
 */
function cellular_checkbox(&$vars) {

  return cellular_xinput($vars['element'], 'checkbox');
}

/**
 * Implements theme_radio().
 */
function cellular_radio(&$vars) {

  return cellular_xinput($vars['element'], 'radio');
}

/**
 * Implements theme_select().
 */
function cellular_select(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'select';

  $output = '<select' . drupal_attributes($attributes) . ">\n";
  $output .= form_select_options($element) . "\n";
  $output .= "</select>\n";

  return $output;
}

/**
 * Implements theme_textfield().
 */
function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'text';
  if (!empty($element['#default_value'])) {
    $attributes['placeholder'] = $element['#default_value'];
  }

  return '<input' . drupal_attributes($attributes) . '/>';
}

/**
 * Implements theme_textarea().
 */
function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'textarea';
  $attributes['placeholder'] = t($element['#default_value']);
  $attributes['cols'] = isset($element['#cols']) ? $element['#cols'] : 60;
  $attributes['rows'] = isset($element['#rows']) ? $element['#rows'] : 5;

  return '<textarea' . drupal_attributes($attributes) . '></textarea>';
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
    'text' => isset($tags[0]) ? $tags[0] : t('First'),
    'element' => $element,
    'parameters' => $parameters,
  ));
  $li_previous = theme('pager_previous', array(
    'text' => isset($tags[1]) ? $tags[1] : t('Previous'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_next = theme('pager_next', array(
    'text' => isset($tags[3]) ? $tags[3] : t('Next'),
    'element' => $element,
    'interval' => 1,
    'parameters' => $parameters,
  ));
  $li_last = theme('pager_last', array(
    'text' => isset($tags[4]) ? $tags[4] : t('Last'),
    'element' => $element,
    'parameters' => $parameters,
  ));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array('class' => array('pager-first'), 'data' => $li_first);
    }
    if ($li_previous) {
      $items[] = array('class' => array('pager-previous'),'data' => $li_previous);
    }

    // When there is more than one page, create the pager list.
    if ($i !== $pager_max) {
      if ($i > 1) {
        $items[] = array('class' => array('pager-ellipsis'), 'data' => '…');
      }
      // Now generate the actual pager piece.
      for (;$i <= $pager_last && $i <= $pager_max; $i++) {
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

    $output = '<h2 class="element-invisible">' . t('Pages') . '</h2>';
    $output .= theme('item_list', array(
      'items' => $items,
      'attributes' => array(
        'class' => array(
          'pager',
        ),
      ),
    ));

    return $output;
  }
}


/*
 * @see file: preprocess/panels.inc
 * Custom Panels functions.
 */

/**
 * Alter the default Panels markup to remove the panel separator.
 */
function cellular_panels_default_style_render_region($vars) {
  
  return implode('', $vars['panes']);
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
function cellular_process_html(&$vars) {
  // dpm($vars);
  // Push modified styles to page.
  // $vars['styles'] = drupal_get_css($vars['css'], FALSE);
}
 */

/**
 * Implements template_process_page().
function cellular_process_page(&$vars) {
  // dpm($vars);
}
 */


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
