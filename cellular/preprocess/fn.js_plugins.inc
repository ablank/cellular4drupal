<?php
/**
 * @file
 * Functions to add javascript plugins.
 */

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
    'weight' => 1,
  );
  theme_get_setting('cellularui') !== 1 ? NULL : $js_plugins['cellularui'] = array(
    'object' => 'cellular',
    // 'file' => 'cellularUI/jquery.cellular.js', // Source of dev script.
    'file' => 'plugins/jquery.cellular.min.js',
    'version' => '0.1',
    'weight' => 1,
  );
  theme_get_setting('d3js') !== 1 ? NULL : $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
    'file' => 'plugins/d3.min.js',
    'version' => '3.4.11',
    'weight' => 1,
  );
  theme_get_setting('freetile') !== 1 ? NULL : $js_plugins['freetile'] = array(
    'file' => 'plugins/jquery.freetile.min.js',
    'version' => '0.3.1',
    'weight' => 1,
  );
  theme_get_setting('flowtype') !== 1 ? NULL : $js_plugins['flowtype'] = array(
    'file' => 'plugins/jquery.flowtype.js',
    'version' => '',
    'weight' => 1,
  );
  theme_get_setting('jparallax') !== 1 ? NULL : $js_plugins['jparallax'] = array(
    'object' => 'reveal',
    'cdn' => NULL,
    'file' => 'plugins/jquery.parallax.min.js',
    'version' => '2.0',
    'weight' => 1,
  );
  theme_get_setting('prism') !== 1 ? NULL : $js_plugins['prism'] = array(
    'object' => 'Prism',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
    'file' => 'plugins/prism.min.js',
    'version' => '0.0.1',
    'weight' => 1,
  );
  theme_get_setting('reveal') !== 1 ? NULL : $js_plugins['reveal'] = array(
    'object' => 'reveal',
    'cdn' => '//cdn.jsdelivr.net/jquery.reveal/1.0/jquery.reveal.min.js',
    'file' => 'plugins/jquery.reveal.min.js',
    'version' => '1.0',
    'weight' => 1,
  );
  theme_get_setting('smoove') !== 1 ? NULL : $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
    'file' => 'plugins/jquery.smoove.min.js',
    'version' => '0.2.6',
    'weight' => 1,
  );
  theme_get_setting('snap-svg') !== 1 ? NULL : $js_plugins['snap-svg'] = array(
    'file' => 'plugins/snap.svg.min.js',
    'version' => '0.3.0',
    'weight' => 1,
  );
  theme_get_setting('threejs') !== 1 ? NULL : $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
    'file' => 'plugins/three.min.js',
    'version' => 'r68',
    'weight' => 1,
  );

  if (theme_get_setting('gsap') === 1) {
    $gsap['cssplugin'] = array(
      'object' => 'CSSPlugin',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
      'file' => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
      'version' => '1.13.1',
      'weight' => 1,
    );
    $gsap['easepack'] = array(
      'object' => 'EasePack',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
      'file' => 'plugins/gsap/minified/easing/EasePack.min.js',
      'version' => '1.13.1',
      'weight' => 2,
    );
    $gsap['tweenlite'] = array(
      'object' => 'TweenLite',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
      'file' => 'plugins/gsap/minified/TweenLite.min.js',
      'version' => '1.13.1',
      'weight' => 3,
    );
    $gsap['jquerygsap'] = array(
      'object' => 'gsap',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
      'file' => 'plugins/gsap/minified/jquery.gsap.min.js',
      'version' => '1.13.1',
      'weight' => 4,
    );

    $js_plugins = array_merge($js_plugins, $gsap);
  }

  return $js_plugins;
}

/**
 * Build modernizr query and add script inline on page.
 */
function cellular_modernizr() {
  // $base_url needs to be added to set the correct path.
  $css_dir = $GLOBALS['base_url'] . '/' . path_to_theme() . '/css/';
  // Build yepnope query based on theme settings.
  $mq = cellular_mq();

  $yepnope = "Modernizr.load([
    {
      test : Modernizr.svg,
      yep : [ '" . $css_dir . "icons-svg.css' ],
      nope : ['" . $css_dir . "icons-png.css']
    },";

  if (theme_get_setting('mq_mobile_enable') === 1 && !empty($mq['mobile'])) {
    $yepnope .= "\n{
        test : Modernizr.mq('" . $$mq['mobile'] . "'),
        yep: ['" . $css_dir . "conditional-mobile.css']
      },";
  }
  if (theme_get_setting('mq_normal_enable') === 1 && !empty($mq['normal'])) {
    $yepnope .= "\n{
      test : Modernizr.mq('" . $mq['normal'] . "'),
      yep: ['" . $css_dir . "conditional-style.css']
    },";
  }
  if (theme_get_setting('mq_large_enable') === 1 && !empty($mq['large'])) {
    $yepnope .= "\n{
      test : Modernizr.mq('" . $mq['large'] . "'),
      yep: ['" . $css_dir . "conditional-large.css']
    },";
  }
  $yepnope .= "\n]);";

  drupal_add_js($yepnope, array(
    'type' => 'inline',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
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
    'weight' => 1,
    'preprocess' => FALSE,
  );
  theme_get_setting('reveal') !== 1 ? NULL : $plugin_css['reveal'] = array(
    'file' => 'reveal/reveal.min.css',
    'weight' => 1,
    'preprocess' => FALSE,
  );

  return $plugin_css;
}
