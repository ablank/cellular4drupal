<?php
/**
 * @file
 * Cellular javascript functions.
 */

/**
 * Add array of javascripts to $javascript, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * the 'object' value is provided.
 */
function cellular_add_js($array, $cellular = FALSE) {
  foreach ($array as $script) {
    if (!empty($script)) {
      // Set default attributes.
      $script['type'] = isset($script['cdn']) ? 'external' : 'file';
      $script['version'] = isset($script['version']) ? $script['version'] : NULL;
      $script['group'] = isset($script['group']) ? $script['group'] : JS_THEME;
      $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE;
      $script['weight'] = isset($script['weight']) ? $script['weight'] : 1;

      if (!empty($script['cdn'])) {
        $data = $script['cdn'];
        cellular_js_fallback($script, $cellular);
      }
      else {
        $data = $cellular ?
        constant('CELLULAR_LIB') : path_to_theme();
        $data .= '/js/' . $script['file'];
      }

      drupal_add_js($data, $script);
    }
  }
}

/**
 * Javascript fallback to local source if CDN fails.
 */
function cellular_js_fallback($script, $cellular = FALSE) {
  $attributes = array(
    'group' => $script['group'],
    'weight' => $script['weight'] + 0.1,
    'type' => 'inline',
    'every_page' => isset($script['every_page']) ? $script['every_page'] : TRUE,
  );
  if (isset($script['object'])) {
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= $cellular ? constant('CELLULAR_LIB') : path_to_theme();
    $fallback .= '/js/' . $script['file'];
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, $attributes);
  }
}

/**
 * Override existing $javascript sources.
 */
function cellular_js_override(&$javascript, $script, $cellular = FALSE) {
  // Only override if js is being called.
  if (isset($javascript[$script['default']])) {
    $ojs = $script['default'];

    if (isset($script['cdn'])) {
      // If cdn is provided, set data to external source & call local fallback.
      $data = $script['cdn'];
      cellular_js_fallback($script, $cellular);
    }
    else {
      // Or set data to local file if no CDN.
      // Set path relative to $cellular_lib or $theme path depending on context.
      $data = $cellular ?
      constant('CELLULAR_LIB') : path_to_theme();
      $data .= isset($script['file']) ? '/js/' . $script['file'] : NULL;
    }

    $javascript[$ojs]['data'] = $data;
    $javascript[$ojs]['version'] = isset($script['version']) ?
    $script['version'] : NULL;
    $javascript[$ojs]['group'] = isset($script['group']) ?
    $script['group'] : JS_LIBRARY;
    $javascript[$ojs]['every_page'] = isset($script['every_page']) ?
    $script['every_page'] : TRUE;
    $javascript[$ojs]['weight'] = isset($script['weight']) ?
    $script['weight'] : 0;
    $javascript[$ojs]['type'] = isset($script['cdn']) ?
    'external' : 'file';
    $javascript[$ojs]['preprocess'] = isset($script['preprocess']) ?
    $script['preprocess'] : FALSE;
  }
}

/**
 * Build modernizr query.
 */
function cellular_modernizr() {
  global $base_url;
  // Get full path to css directory.
  // $base_url needs to be added to reference the correct path.
  $dir_css = $base_url . '/' . path_to_theme() . '/css/';
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
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}

/**
 * Add javascript plugins using the cellular libraary.
 */
function cellular_plugins_js() {
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
    'reveal' => theme_get_setting('reveal') == 1 ? array(
      'object' => 'smoove',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
      'file' => 'plugins/jquery.smoove.min.js',
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
