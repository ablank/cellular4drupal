<?php
/**
 * @file
 * Functions to add javascript plugins.
 */

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
  $plugin_path = '/drupal/'; // Relative to Cellular Lib
  $plugins = array(
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

  foreach ($plugins as &$plugin) {
    $plugin['file'] = $plugin_path . $plugin['file'] . CELLULAR_JS_EXT;
    $plugin['group'] = JS_LIBRARY;
    cellular_js_override($javascript, $plugin, TRUE);
  }
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js_plugin_settings() {
  // Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
  $js_plugins = array();
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = TRUE : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = TRUE : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = TRUE : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = TRUE : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = TRUE : NULL;
  theme_get_setting('nprogress') == 1 ? $js_plugins['nprogress'] = TRUE : NULL;

  return $js_plugins;
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *   Associative array of plugin data.
 */
function cellular_plugins_js() {
  $jquery = cellular_jquery_info();
  $plugin_path = '/lib/';
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();

  // Add migrate to prevent plugins from breaking with jQuery > v1.9.
  if (theme_get_setting('jquery_migrate') == 1) {
    if (intval($jquery['version'], 0) === 3) {
      $js_plugins['migrate'] = array(
        'group' => JS_LIBRARY,
        'file' => 'jquery.migrate-3.0.0',
        'version' => '3.0.0',
        'weight' => -96,
      );
    }
    if (intval($jquery['version'], 0) === 2 ||
    intval($jquery['version'], 0) === 1 && floatval(substr($jquery['version'], 2)) >= 9) {
      $js_plugins['migrate'] = array(
        'group' => JS_LIBRARY,
        'file' => 'jquery.migrate-1.4.1',
        'version' => '1.4.1',
        'weight' => -96,
      );
    }
  }
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = array(
    'object' => 'backstretch',
    'file' => 'jquery.backstretch',
    'version' => '2.0.4',
  ) : NULL;
  theme_get_setting('d3js') == 1 ? $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/4.2.1/d3.js',
    'file' => 'd3',
    'version' => '4.2.1',
  ) : NULL;
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = array(
    'file' => 'jquery.freetile',
    'version' => '0.3.1',
  ) : NULL;
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = array(
    'file' => 'jquery.flowtype',
    'version' => '',
  ) : NULL;
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = array(
    'file' => 'jquery.parallax',
    'version' => '2.0',
  ) : NULL;
  theme_get_setting('prism') == 1 ? $js_plugins['prism'] = array(
    'group' => JS_DEFAULT,
    'object' => 'Prism',
    'file' => 'prism',
    'version' => '1.5.1',
  ) : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'file' => 'jquery.smoove',
    'version' => '0.2.8',
  ) : NULL;
  theme_get_setting('snap-svg') == 1 ? $js_plugins['snap-svg'] = array(
    'file' => 'snap.svg',
    'version' => '0.4.1',
  ) : NULL;
  theme_get_setting('threejs') == 1 ? $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => 'https://cdnjs.cloudflare.com/ajax/libs/three.js/r79/three.js',
    'file' => 'three',
    'version' => 'r79',
  ) : NULL;

  if (theme_get_setting('nprogress') == 1) {
    $js_plugins['nprogress'] = array(
      'object' => 'NProgress',
      'file' => 'nprogress',
      'scope' => 'critical',
      'weight' => 1
    );
    $js_plugins['nprogress_init'] = array(
      'file' => 'nprogress_init',
      'scope' => 'critical',
      'weight' => 2,
    );
  }
  if (theme_get_setting('gsap') == 1) {
    $gsappath = CELLULAR_JS_EXT === '.js' ? 'gsap/uncompressed/' : 'gsap/minified/';
    $gsap['cssplugin'] = array(
      'object' => 'CSSPlugin',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/plugins/CSSPlugin.min.js',
      'file' => $gsappath . 'plugins/CSSPlugin',
      'version' => '1.19.0',
      'weight' => 1,
    );
    $gsap['easepack'] = array(
      'object' => 'EasePack',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/easing/EasePack.min.js',
      'file' => $gsappath . 'easing/EasePack',
      'version' => '1.15.5',
      'weight' => 2,
    );
    $gsap['tweenlite'] = array(
      'object' => 'TweenLite',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/TweenLite.min.js',
      'file' => $gsappath . 'TweenLite',
      'version' => '1.19.0',
      'weight' => 3,
    );
    $gsap['jquerygsap'] = array(
      'object' => 'gsap',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/jquery.gsap.min.js',
      'file' => $gsappath . 'jquery.gsap',
      'version' => '0.1.12',
      'weight' => 4,
    );

    $js_plugins = array_merge($js_plugins, $gsap);
  }

  foreach ($js_plugins as &$plugin) {
    $plugin['group'] = !empty($plugin['group']) ? $plugin['group'] : JS_DEFAULT;
    $plugin['file'] = $plugin_path . $plugin['file'] . CELLULAR_JS_EXT;
  }

  return $js_plugins;
}
