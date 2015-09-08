<?php
/**
 * @file
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
    'default' => 'misc/jquery.js',
    'update' => theme_get_setting('jquery_update'),
    'version' => theme_get_setting('jquery_version'),
    'use_cdn' => theme_get_setting('jquery_cdn'),
    'cdn' => theme_get_setting('jquery_cdn_source'),
    'ui' => array(
      'version' => theme_get_setting('jqueryui_version'),
      'theme' => theme_get_setting('jqueryui_theme'),
    ),
  );
  $jquery['file'] = 'jquery-' . $jquery['version'] . CELLULAR_JS_EXT;

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
      'theme' => 'ui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . $ext,
    ),
    'google' => array(
      'base_url' => '//ajax.googleapis.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery' . $ext,
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui' . $ext,
      'theme' => 'jqueryui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . $ext,
    ),
    'microsoft' => array(
      'base_url' => '//ajax.aspnetcdn.com/ajax/',
      'jquery' => 'jquery/jquery-' . $jq['version'] . $ext,
      'jqueryui' => 'jquery.ui/' . $ui['version'] . '/jquery-ui' . $ext,
      'theme' => 'jquery.ui/' . $ui['version'] . '/themes/' . $ui['theme'] . '/jquery-ui' . $ext,
    ),
    'cloudflare' => array(
      'base_url' => '//cdnjs.cloudflare.com/ajax/libs/',
      'jquery' => 'jquery/' . $jq['version'] . '/jquery' . $ext,
      'jqueryui' => 'jqueryui/' . $ui['version'] . '/jquery-ui' . $ext,
      // Themes aren't provided by cdnjs.
      'theme' => 'jqueryui/' . $ui['version'] . '/css/jquery-ui' . $ext,
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
    'default' => $jq['default'],
    'file' => $jq['file'],
    //'file' => 'jquery-' . $jq['version'] . '.min.js',
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

  $jq = cellular_jquery_info();
  $ui = $jq['ui'];
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
      $style = array(
        'ui' => array(
          'default' => $default,
          'version' => $ui['version'],
          'group' => CSS_SYSTEM,
          'every_page' => FALSE,
          'weight' => !empty($css[$default]['weight']) ? $css[$default]['weight'] : -9,
          'file' => NULL,
          'preprocess' => TRUE,
        ),
      );
      // Remove default after collecting style info.
      unset($css[$default]);

      if ($ui['theme'] === 'custom') {
        // Set path to local custom file if selected.
        $v = $ui['version'] === '1.10.4' ? '1.10' : '1.9';
        $style['ui']['file'] = "jquery-ui/jquery-ui-" . $v . CELLULAR_CSS_EXT;

        cellular_add_css($style);
      }
      else {
        $ui_path = $ui['path'] . $ui['version'] . '/' . $ui['theme'] . '/';
        $style['ui']['file'] = $ui_path . 'jquery-ui' . CELLULAR_CSS_EXT;
        if (theme_get_setting('jquery_cdn') == 1) {
          $cdn = cellular_cdn();
          // Set cdn source.
          $style['ui']['cdn'] = $cdn['base_url'] . $cdn['theme'];
        }

        cellular_add_css($style, TRUE);
      }
    }
  }
}
