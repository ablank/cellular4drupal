<?php
/**
 * @file
 * Functions to add javascript plugins.
 */

/**
 * Build default modernizr queries using theme settings.
 */
function cellular_modernizr_default() {
  // $base_url needs to be added to set the correct path.
  $css_dir = $GLOBALS['base_url'] . '/' . path_to_theme() . '/css/';
  // Build yepnope query based on theme settings.
  $mq = cellular_mq();
  $tests = array();

  // Test SVG
  $tests['svg'] = array(
    'test' => 'Modernizr.svg',
    'yep' => $css_dir . "icons-svg.css",
    'nope' => $css_dir . "icons-png.css",
  );

  if (theme_get_setting('mq_mobile_enable') === 1 && !empty($mq['mobile'])) {
    $tests['mobile'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['mobile'] . '\')',
      'yep' => $css_dir . "conditional-mobile.css",
    );
  }
  if (theme_get_setting('mq_normal_enable') === 1 && !empty($mq['normal'])) {
    $tests['normal'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['normal'] . '\')',
      'yep' => $css_dir . "conditional-style.css",
    );
  }
  if (theme_get_setting('mq_large_enable') === 1 && !empty($mq['large'])) {
    $tests['large'] = array(
      'test' => 'Modernizr.mq(\'' . $mq['large'] . '\')',
      'yep' => $css_dir . "conditional-large.css",
    );
  }
  
  cellular_modernizr($tests);
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *  Associative array of plugin data.
 */
function cellular_plugins_js() {
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();
  theme_get_setting('modernizr') !== 1 ? NULL : $js_plugins['modernizr'] = array(
    'group' => JS_LIBRARY,
    'object' => 'Modernizr',
    'file' => 'modernizr.js',
    'version' => '2.8.3',
    'weight' => -1000,
  );
  theme_get_setting('backstretch') !== 1 ? NULL : $js_plugins['backstretch'] = array(
    'object' => 'backstretch',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-backstretch/2.0.4/jquery.backstretch.min.js',
    'file' => 'plugins/jquery.backstretch.min.js',
    'version' => '2.0.4',
    'weight' => -20,
  );
  theme_get_setting('cellularui') !== 1 ? NULL : $js_plugins['cellularui'] = array(
    'object' => 'cellular',
    // 'file' => 'cellularUI/jquery.cellular.js', // Source of dev script.
    'file' => 'plugins/jquery.cellular.min.js',
    'version' => '0.1',
    'weight' => -19,
  );
  theme_get_setting('d3js') !== 1 ? NULL : $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
    'file' => 'plugins/d3.min.js',
    'version' => '3.4.11',
    'weight' => -18,
  );
  theme_get_setting('freetile') !== 1 ? NULL : $js_plugins['freetile'] = array(
    'file' => 'plugins/jquery.freetile.min.js',
    'version' => '0.3.1',
    'weight' => -17,
  );
  theme_get_setting('flowtype') !== 1 ? NULL : $js_plugins['flowtype'] = array(
    'file' => 'plugins/jquery.flowtype.js',
    'version' => '',
    'weight' => -16,
  );
  theme_get_setting('jparallax') !== 1 ? NULL : $js_plugins['jparallax'] = array(
    'object' => 'reveal',
    'cdn' => NULL,
    'file' => 'plugins/jquery.parallax.min.js',
    'version' => '2.0',
    'weight' => -15,
  );
  theme_get_setting('prism') !== 1 ? NULL : $js_plugins['prism'] = array(
    'object' => 'Prism',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
    'file' => 'plugins/prism.min.js',
    'version' => '0.0.1',
    'weight' => -14,
  );
  theme_get_setting('reveal') !== 1 ? NULL : $js_plugins['reveal'] = array(
    'object' => 'reveal',
    'cdn' => '//cdn.jsdelivr.net/jquery.reveal/1.0/jquery.reveal.min.js',
    'file' => 'plugins/jquery.reveal.min.js',
    'version' => '1.0',
    'weight' => -13,
  );
  theme_get_setting('smoove') !== 1 ? NULL : $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
    'file' => 'plugins/jquery.smoove.min.js',
    'version' => '0.2.6',
    'weight' => -12,
  );
  theme_get_setting('snap-svg') !== 1 ? NULL : $js_plugins['snap-svg'] = array(
    'file' => 'plugins/snap.svg.min.js',
    'version' => '0.3.0',
    'weight' => -11,
  );
  theme_get_setting('threejs') !== 1 ? NULL : $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
    'file' => 'plugins/three.min.js',
    'version' => 'r68',
    'weight' => -10,
  );

  if (theme_get_setting('gsap') === 1) {
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
 *  Array of stylesheets used by javascript plugins.
 */
function cellular_plugin_css() {
  // Plugins available through cellular, styles added based on theme settings.
  // $plugin_css paths are relative to /libraries/cellular/css/
  $plugin_css = array();
  theme_get_setting('prism') !== 1 ? NULL : $plugin_css['prism'] = array(
    'file' => 'prism.css',
    'weight' => -10,
    'preprocess' => FALSE,
  );
  theme_get_setting('reveal') !== 1 ? NULL : $plugin_css['reveal'] = array(
    'file' => 'reveal/reveal.min.css',
    'weight' => -10,
    'preprocess' => FALSE,
  );

  return $plugin_css;
}
