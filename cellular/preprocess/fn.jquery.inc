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
function cellular_jquery_update(array &$javascript) {
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
function cellular_jqueryui_update_js(array &$javascript) {
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
function cellular_jqueryui_update_css(array &$css) {
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
