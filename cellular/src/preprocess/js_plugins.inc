<?php
/**
 * @file
 * Functions to add javascript plugins.
 */

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
function cellular_modernizr(array $tests) {
// $base_url needs to be added to set the correct path.
  $dir = $GLOBALS['base_url'] . '/' . path_to_theme();
  $query = '';

  foreach ($tests as $test) {
    if (empty($test['test'])) {
      return;
    }
    else {
      $query .= "{\n";
      $query .= "test : " . $test['test'] . ",\n";
      empty($test['yep']) ? NULL : $query .= "yep : ['" . $dir . $test['yep'] . "'],\n";
      empty($test['nope']) ? NULL : $query .= "nope : ['" . $dir . $test['nope'] . "'],\n";
      empty($test['both']) ? NULL : $query .= "both : ['" . $dir . $test['both'] . "'],\n";
      empty($test['complete']) ? NULL : $query .= "complete : function(){\n" . $test['complete'] . "},\n";

      // $query .= "nope : ['" . $test['nope'] . "'],\n";
      $query .= "},\n";
    }
  }

  $query = "Modernizr.load([\n$query]);\n";

  drupal_add_js($query, array(
    'type' => 'inline',
    'group' => JS_LIBRARY,
    'every_page' => TRUE,
    'weight' => -999,
  ));
}

/**
 * Build default modernizr queries using theme settings.
 */
function cellular_modernizr_default() {
  $css_dir = '/build/css';
  $ext = theme_get_setting('dev') == 0 ? 'min.css' : 'css';
  // Build yepnope query based on theme settings.
  $mq = cellular_mq();

  $tests = array();
  // Test Flexbox
  $tests['flexbox'] = array(
    'test' => 'Modernizr.flexbox',
    'nope' => " $css_dir/fallback/grid.$ext",
  );
  // Test SVG
  $tests['svg'] = array(
    'test' => 'Modernizr.svg',
    'yep' => "$css_dir/icons-svg.$ext",
    'nope' => " $css_dir/icons-png.$ext",
  );
// Mobile screen size test.
  if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
    $tests['mobile'] = array(
      'test' => "Modernizr.mq('" . $mq['mobile'] . "')",
      'yep' => "$css_dir/conditional-mobile.$ext",
    );
  }
// Normal screen size test.
  if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
    $tests['normal'] = array(
      'test' => "Modernizr.mq('" . $mq['normal'] . "')",
      'yep' => "$css_dir/conditional-style.$ext",
    );
  }
// Large screen size test.
  if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
    $tests['large'] = array(
      'test' => "Modernizr.mq('" . $mq['large'] . "')",
      'yep' => "$css_dir/conditional-large.$ext",
    );
  }

  cellular_modernizr($tests);
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *   Associative array of plugin data.
 */
function cellular_plugins_js() {
  // Scripts to add, relative to /libraries/cellular/js/
  $js_plugins = array();
  // Modernizr
  theme_get_setting('modernizr') == 1 ? $js_plugins['modernizr'] = array(
    'group' => JS_LIBRARY,
    'object' => 'Modernizr',
    'file' => 'modernizr',
    'version' => '2.8.3',
    'weight' => -1000,
  ) : NULL;
  // Backstretch
  theme_get_setting('backstretch') == 1 ? $js_plugins['backstretch'] = array(
    'object' => 'backstretch',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-backstretch/2.0.4/jquery.backstretch.min.js',
    'file' => 'plugins/jquery.backstretch',
    'version' => '2.0.4',
    'weight' => -20,
  ) : NULL;
  // D3
  theme_get_setting('d3js') == 1 ? $js_plugins['d3'] = array(
    'object' => 'd3',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
    'file' => 'plugins/d3',
    'version' => '3.4.11',
    'weight' => -18,
  ) : NULL;
  // Freetile
  theme_get_setting('freetile') == 1 ? $js_plugins['freetile'] = array(
    'file' => 'plugins/jquery.freetile',
    'version' => '0.3.1',
    'weight' => -17,
  ) : NULL;
  // Flowtype
  theme_get_setting('flowtype') == 1 ? $js_plugins['flowtype'] = array(
    'file' => 'plugins/jquery.flowtype',
    'version' => '',
    'weight' => -16,
  ) : NULL;
  // jParallax
  theme_get_setting('jparallax') == 1 ? $js_plugins['jparallax'] = array(
    'file' => 'plugins/jquery.parallax',
    'version' => '2.0',
    'weight' => -15,
  ) : NULL;
  // Prism
  theme_get_setting('prism') == 1 ? $js_plugins['prism'] = array(
    'object' => 'Prism',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
    'file' => 'plugins/prism',
    'version' => '0.0.1',
    'weight' => -14,
  ) : NULL;
  // Smoove
  theme_get_setting('smoove') == 1 ? $js_plugins['smoove'] = array(
    'object' => 'smoove',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/jquery-smoove/0.2.6/jquery.smoove.min.js',
    'file' => 'plugins/jquery.smoove',
    'version' => '0.2.6',
    'weight' => -12,
  ) : NULL;
  // SnapSVG
  theme_get_setting('snap-svg') == 1 ? $js_plugins['snap-svg'] = array(
    'file' => 'plugins/snap.svg',
    'version' => '0.3.0',
    'weight' => -11,
  ) : NULL;
  // Three
  theme_get_setting('threejs') == 1 ? $js_plugins['threejs'] = array(
    'object' => 'THREE',
    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
    'file' => 'plugins/three',
    'version' => 'r68',
    'weight' => -10,
  ) : NULL;
  // Greensocks Animation
  if (theme_get_setting('gsap') == 1) {
    $gsap['cssplugin'] = array(
      'object' => 'CSSPlugin',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
      'file' => 'plugins/gsap/minified/plugins/CSSPlugin',
      'version' => '1.13.1',
      'weight' => -9,
    );
    $gsap['easepack'] = array(
      'object' => 'EasePack',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
      'file' => 'plugins/gsap/minified/easing/EasePack',
      'version' => '1.13.1',
      'weight' => -8,
    );
    $gsap['tweenlite'] = array(
      'object' => 'TweenLite',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
      'file' => 'plugins/gsap/minified/TweenLite',
      'version' => '1.13.1',
      'weight' => -7,
    );
    $gsap['jquerygsap'] = array(
      'object' => 'gsap',
      'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
      'file' => 'plugins/gsap/minified/jquery',
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
  $plugin_css = array();
  // Prism
  theme_get_setting('prism') == 1 ? $plugin_css['prism'] = array(
    'file' => 'prism',
    'weight' => -10,
  ) : NULL;

  return $plugin_css;
}
