<?php
/**
 * @file
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
  $plugin_path = 'drupal/'; // Relative to Cellular Lib
  $plugins = array(
    'drupal' => array(
      'default' => 'misc/drupal.js',
      'version' => '7.38',
      'file' => 'drupal',
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

  foreach ($plugins as &$plugin) {
    $plugin['file'] = $plugin_path . $plugin['file'] . CELLULAR_JS_EXT;
    $plugin['group'] = JS_LIBRARY;
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
  $plugin_path = 'plugins/';
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();
  theme_get_setting('modernizr') == 1 ? $js_plugins['modernizr'] = array(
    'group' => JS_LIBRARY,
    'object' => 'Modernizr',
    'file' => 'modernizr',
    'version' => '2.8.3',
    'weight' => -1000,
  ) : NULL;

  // Add migrate to prevent plugins from breaking with jQuery > v1.9.
  theme_get_setting('jquery_migrate') == 1 && floatval(substr($jquery['version'], 2)) >= 9 ?
  $js_plugins['migrate'] = array(
    'group' => JS_LIBRARY,
    'file' => 'jquery.migrate',
    'version' => '1.2.1',
    'weight' => -96,
  ) : NULL;
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = array(
    'object' => 'backstretch',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-backstretch/2.0.4/jquery.backstretch.min.js',
    'file' => 'jquery.backstretch',
    'version' => '2.0.4',
  ) : NULL;
  theme_get_setting('d3js') == 1 ? $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3',
    'file' => 'd3',
    'version' => '3.4.11',
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
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.min.js',
    'file' => 'prism',
    'version' => '0.0.1',
  ) : NULL;
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
    'file' => 'jquery.smoove',
    'version' => '0.2.6',
  ) : NULL;
  theme_get_setting('snap-svg') == 1 ? $js_plugins['snap-svg'] = array(
    'file' => 'snap.svg',
    'version' => '0.3.0',
  ) : NULL;
  theme_get_setting('threejs') == 1 ? $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three',
    'file' => 'three',
    'version' => 'r68',
  ) : NULL;

  if (theme_get_setting('gsap') == 1) {
    $gsappath = theme_get_setting('min_script') == 1 ? 'gsap/minified/' : 'gsap/uncompressed/';
    $gsap['cssplugin'] = array(
      'object' => 'CSSPlugin',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
      'file' => $gsappath . 'plugins/CSSPlugin',
      'version' => '1.13.1',
      'weight' => 1,
    );
    $gsap['easepack'] = array(
      'object' => 'EasePack',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
      'file' => $gsappath . 'easing/EasePack',
      'version' => '1.13.1',
      'weight' => 2,
    );
    $gsap['tweenlite'] = array(
      'object' => 'TweenLite',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
      'file' => $gsappath . 'TweenLite',
      'version' => '1.13.1',
      'weight' => 3,
    );
    $gsap['jquerygsap'] = array(
      'object' => 'gsap',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
      'file' => $gsappath . 'jquery.gsap',
      'version' => '1.13.1',
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
