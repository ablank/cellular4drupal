<?php
/**
 * @file
 * Functions to add javascript plugins.
 */

/**
 * Add javascript plugins using the cellular libraary.
 */
function cellular_plugins_js() {
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array(
    'cellular' => theme_get_setting('cellularjs') == 1 ? array(
      'object' => 'cellular',
      //'file' => 'cellularUI/jquery.cellular.js',
      'file' => 'plugins/jquery.cellular.min.js',
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
    'modernizr' => theme_get_setting('modernizr') == 1 ? array(
      'group' => JS_LIBRARY,
      'object' => 'Modernizr',
      'file' => 'modernizr.js',
      'weight' => -1000,
    ) : NULL,
    'prism' => theme_get_setting('prism') == 1 ? array(
      'object' => 'Prism',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
      'file' => 'plugins/prism.min.js',
      'weight' => -7,
    ) : NULL,
    'reveal' => theme_get_setting('reveal') == 1 ? array(
      'object' => 'reveal',
      'cdn' => NULL,
      'file' => 'plugins/jquery.reveal.min.js',
      'weight' => -6,
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

/**
 * Build modernizr query.
 */
function cellular_modernizr() {
  global $base_url;
  // $base_url needs to be added to set the correct path.
  $css_dir = $base_url . '/' . path_to_theme() . '/css/';
  // Build yepnope query based on theme settings.
  $mq = cellular_mq();

  $yepnope = "Modernizr.load([";
  $yepnope .= "
        {
          test : Modernizr.svg,
          yep : [ '" . $css_dir . "icons-svg.css' ],
          nope : ['" . $css_dir . "icons-png.css']
          },";

  if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $$mq['mobile'] . "'),
          yep: ['" . $css_dir . "conditional-mobile.css']
          },
        ";
  }
  if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['normal'] . "'),
          yep: ['" . $css_dir . "conditional-style.css']
          },
        ";
  }
  if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
    $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['large'] . "'),
          yep: ['" . $css_dir . "conditional-large.css']
          },
        ";
  }
  $yepnope .= "]);";

  drupal_add_js($yepnope, array(
    'type' => 'inline',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}
