<?php

/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Build modernizr query.
 */
function cellular_modernizr() {
  global $base_url, $theme_path;
// Get full path to css directory.
// $base_url needs to be added to reference the correct path.
  $dir_css = $base_url . '/' . $theme_path . '/css/';
// Build yepnope query based on theme settings.
  $mq = array();
  $mq['mobile'] = theme_get_setting('mq_mobile');
  $mq['normal'] = theme_get_setting('mq_normal');
  $mq['large'] = theme_get_setting('mq_large');

  $yepnope = "Modernizr.load([";
  $yepnope .= "
        {
          test : Modernizr.svg,
          yep : [ '" . $dir_css . "icons-svg.css' ],
          nope : ['" . $dir_css . "icons-png.css']
          },";

  if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $$mq['mobile'] . "'),
          yep: ['" . $dir_css . "conditional-mobile.css']
          },
        ";
  }
  if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['normal'] . "'),
          yep: ['" . $$dir_css . "conditional-style.css']
          },
        ";
  }
  if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['large'] . "'),
          yep: ['" . $dir_css . "conditional-large.css']
          },
        ";
  }
  $yepnope .= "]);";

  drupal_add_js($yepnope, array(
    'type' => 'inline',
    'group' => CSS_SYSTEM,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}

/**
 * Add javascript plugins using the cellular libraary.
 */
function cellular_add_js_plugins() {
// Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array(
    'modernizr' => theme_get_setting('modernizr') == 1 ? array(
      'group' => JS_LIBRARY,
      'object' => 'Modernizr',
      'file' => 'modernizr.js',
      'weight' => -1000,
    ) : NULL,
    'cellular' => theme_get_setting('cellularjs') == 1 ? array(
      'object' => 'cellular',
      'file' => 'plugins/jquery.cellular.js',
      'weight' => -10,
    ) : NULL,
    'd3' => theme_get_setting('d3js') == 1 ? array(
      'object' => 'd3',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
      'file' => 'plugins/d3.min.js',
      'weight' => -9,
    ) : NULL,
    'masonry' => theme_get_setting('masonry') == 1 ? array(
      'object' => NULL,
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/masonry/3.1.5/masonry.pkgd.min.js',
      'file' => 'plugins/jquery.masonry.min.js',
      'weight' => -8,
    ) : NULL,
    'prism' => theme_get_setting('prism') == 1 ? array(
      'object' => 'Prism',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
      'file' => 'plugins/prism.min.js',
      'weight' => -7,
    ) : NULL,
    'smoove' => theme_get_setting('smoove') == 1 ? array(
      'object' => 'smoove',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
      'file' => 'plugins/jquery.smoove.min.js',
      'weight' => -6,
    ) : NULL,
    'threejs' => theme_get_setting('threejs') == 1 ? array(
      'object' => 'THREE',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
      'file' => 'plugins/three.min.js',
      'weight' => -5,
    ) : NULL,
  );

  if (theme_get_setting('gsap') == 1) {
    $gsap = array(
      'gsap_css' => array(
        'object' => 'CSSPlugin',
        'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
        'file' => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
        'weight' => -10,
      ),
      'gsap_easing' => array(
        'object' => 'EasePack',
        'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
        'file' => 'plugins/gsap/minified/easing/EasePack.min.js',
        'weight' => -9,
      ),
      'gsap_tweens' => array(
        'object' => 'TweenLite',
        'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
        'file' => 'plugins/gsap/minified/TweenLite.min.js',
        'weight' => -8,
      ),
      'gsap' => array(
        'object' => 'gsap',
        'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
        'file' => 'plugins/gsap/minified/jquery.gsap.min.js',
        'weight' => -7,
      ),
    );

    $js_plugins = array_merge($js_plugins, $gsap);
  }

  return $js_plugins;
}
