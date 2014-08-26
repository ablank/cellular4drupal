<?php
/**
 * @file
 * Create/Update/Delete js
 */

/**
 * hook_js_alter()
 */
function cellular_js_alter(&$javascript)
{
    global $full_theme_path;

// Pass variable from drupal to js
//  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');

    /* myVar will be available in Javascript as:
      <script>
      if (Drupal.settings.myVar.key == value){
      alert('Got it!');
      }
      </script>
     */

// General scripts to add
    $scripts = array(
        'script' => array(
            'file' => 'script.js', // Path to file, relative to /yourTheme/js/
            'weight' => 99,
        ),
    );

    cellular_add_js($scripts);

    // Add js plugins based on theme settings
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
        'smoove' => theme_get_setting('smoove') == 1 ?
                array(
                    'object' => null,
                    'file' => 'plugins/jquery.smoove.min.js',
                    'weight' => 1,
                ) : null,
        'masonry' => theme_get_setting('masonry') == 1 ?
                array(
                    'object' => 'Masonry',
                    'cdn' => '//cdnjs.cloudflare.com/ajax/libs/masonry/3.1.5/masonry.pkgd.min.js',
                    'file' => 'plugins/jquery.masonry.min.js',
                    'weight' => 1,
                ) : null,
    );
//
    if (theme_get_setting('gsap') == 1) {
        $gsap = array(
            'gsap_css' => array(
                'object' => 'CSSPlugin',
                'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
                'file' => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
                'weight' => -80,
            ),
            'gsap_easing' => array(
                'object' => 'EasePack',
                'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
                'file' => 'plugins/gsap/minified/easing/EasePack.min.js',
                'weight' => -79,
            ),
            'gsap_tweens' => array(
                'object' => 'TweenLite',
                'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
                'file' => 'plugins/gsap/minified/TweenLite.min.js',
                'weight' => -78,
            ),
            'gsap' => array(
                'object' => 'gsap',
                'cdn' => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
                'file' => 'plugins/gsap/minified/jquery.gsap.min.js',
                'weight' => -77,
            ),
        );

        $js_plugins = array_merge($js_plugins, $gsap);
    }

    cellular_add_js($js_plugins, TRUE);

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
          yep : [ '" . $full_theme_path . "/css/icons-svg.css' ],
          nope : ['" . $full_theme_path . "/css/icons-png.css']
          },";


        if (theme_get_setting('mq_mobile_enable') == 1 && !empty($mq['mobile'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $$mq['mobile'] . "'),
          yep: ['" . $full_theme_path . "/css/conditional-mobile.css']
          },
        ";
        }
        if (theme_get_setting('mq_normal_enable') == 1 && !empty($mq['normal'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['normal'] . "'),
          yep: ['" . $full_theme_path . "/css/conditional-style.css']
          },
        ";
        }
        if (theme_get_setting('mq_large_enable') == 1 && !empty($mq['large'])) {
            $yepnope .= "
        {
          test : Modernizr.mq('" . $mq['large'] . "'),
          yep: ['" . $full_theme_path . "/css/conditional-large.css']
          },
        ";
        }
        $yepnope .= "]);";

        drupal_add_js($yepnope, array(
            'type' => 'inline',
            'group' => CSS_SYSTEM,
            'every_page' => TRUE,
            'weight' => -999
        ));
    }
}
