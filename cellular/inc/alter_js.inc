<?php

/* * ************
  js_alter()
 * ************** */

function cellular_js_alter(&$javascript) {
    global $base_url;
// Pass variable from drupal to js
//  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');

    /* myVar will be available in Javascript as:
      <script>
      if (Drupal.settings.myVar.key == value){
      alert('Got it!');
      }
      </script>
     */

// Scripts to add
    $scripts = array(
        'script' => array(
            'file' => 'script.js', // Path to file, relative to /yourTheme/js/
            'weight' => 99,
        ),
    );

    cellular_add_js($scripts);

    $js_plugins = array(
        'modernizr' => theme_get_setting('modernizr') == 1 ?
                array(
            'group' => JS_LIBRARY,
            'object' => 'Modernizr',
            'file' => 'modernizr.js',
            'weight' => -1000,
                ) : null,
        'cellular' => theme_get_setting('cellularjs') == 1 ?
                array(
            'object' => 'Cellular',
            'file' => 'plugins/jquery.cellular.min.js',
            'weight' => 0,
                ) : null,
        'd3' => theme_get_setting('d3js') == 1 ?
                array(
            'object' => 'd3',
            'file' => 'plugins/d3.min.js',
            'weight' => 1,
                ) : null,
        'threejs' => theme_get_setting('threejs') == 1 ?
                array(
            'object' => 'THREE',
            'file' => 'plugins/three.min.js',
            'weight' => 1,
                ) : null,
        'prism' => theme_get_setting('prism') == 1 ?
                array(
            'object' => 'Prism',
            'file' => 'plugins/prism.min.js',
            'weight' => 1,
                ) : null,
        'masonry' => theme_get_setting('masonry') == 1 ?
                array(
            'object' => null,
            'file' => 'plugins/jquery.masonry.min.js',
            'weight' => 1,
                ) : null,
    );

    if (theme_get_setting('gsap') == 1) {
        $gsap = array(
            'gsap_css' => array(
                'object' => null,
                'file' => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
                'weight' => -80,
            ),
            'gsap_easing' => array(
                'object' => null,
                'file' => 'plugins/gsap/minified/easing/EasePack.min.js',
                'weight' => -79,
            ),
            'gsap_tweens' => array(
                'object' => null,
                'file' => 'plugins/gsap/minified/TweenLite.min.js',
                'weight' => -78,
            ),
            'gsap' => array(
                'object' => null,
                'file' => 'plugins/gsap/minified/jquery.gsap.min.js',
                'weight' => -77,
            ),
        );

        $js_plugins = array_merge($js_plugins, $gsap);
    }

    foreach ($js_plugins as $script) {
        if (!empty($script)) {
            drupal_add_js(cellular_path() . '/js/' . $script['file'], array(
                'type' => 'file',
                'group' => isset($script['group']) ? $script['group'] : JS_THEME,
                'every_page' => TRUE,
                'weight' => $script['weight']
            ));
        }
    }
    //
// Update jQuery & jQueryUI
    if (theme_get_setting('jquery_update') == 1) {
        cellular_update_jquery($javascript);
        cellular_update_jqueryui($javascript);
    }


    if (theme_get_setting('modernizr') == 1) {
// Build yepnope query based on theme settings
// $base_url needs to be added for scripts to reference the correct path
        $mq = array();
        $mq['mobile'] = theme_get_setting('mq_mobile');
        $mq['normal'] = theme_get_setting('mq_normal');
        $mq['large'] = theme_get_setting('mq_large');


        $yepnope = "Modernizr.load([";
        $yepnope .= "
        {
          test : Modernizr.svg,
          yep : [ '" . $base_url . '/' . cellular_theme_path() . "/css/icons-svg.css' ],
          nope : ['" . $base_url . '/' . cellular_theme_path() . "/css/icons-png.css']
          },";


        if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $$mq['mobile'] . "'),
          yep: ['" . $base_url . '/' . cellular_theme_path() . "/css/conditional-mobile.css']
          },
        ";
        }
        if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['normal'] . "'),
          yep: ['" . $base_url . '/' . cellular_theme_path() . "/css/conditional-style.css']
          },
        ";
        }
        if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['large'] . "'),
          yep: ['" . $base_url . '/' . cellular_theme_path() . "/css/conditional-large.css']
          },
        ";
        }
        $yepnope .= "
]);
";

        drupal_add_js($yepnope, array(
            'type' => 'inline',
            'group' => CSS_SYSTEM,
            'every_page' => TRUE,
            'weight' => -999
        ));
    }
}
