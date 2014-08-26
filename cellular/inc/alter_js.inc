<?php

/*
 * @file
 * Add/Update/Delete javascript
 *  hook_js_alter()
 */

function cellular_js_alter(&$javascript) {
  global $base_url, $theme_path, $cellular_lib;

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
      'file'   => 'script.js', // Path to file, relative to /yourTheme/js/
      'weight' => 99,
    ),
  );

  cellular_add_js($scripts);

  $js_plugins = array(
    'modernizr' => theme_get_setting('modernizr') == 1 ? array(
        'group'  => JS_LIBRARY,
        'object' => 'Modernizr',
        'file'   => 'modernizr.js',
        'weight' => -1000,
      ) : NULL,
    'cellular'  => theme_get_setting('cellularjs') == 1 ? array(
        'object' => 'cellular',
        'file'   => 'plugins/jquery.cellular.min.js',
      ) : NULL,
    'd3'        => theme_get_setting('d3js') == 1 ? array(
        'object' => 'd3',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/d3/3.4.11/d3.min.js',
        'file'   => 'plugins/d3.min.js',
      ) : NULL,
    'threejs'   => theme_get_setting('threejs') == 1 ? array(
        'object' => 'THREE',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/three.js/r68/three.min.js',
        'file'   => 'plugins/three.min.js',
      ) : NULL,
    'prism'     => theme_get_setting('prism') == 1 ? array(
        'object' => 'Prism',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/prism/0.0.1/prism.js',
        'file'   => 'plugins/prism.min.js',
      ) : NULL,
    'masonry'   => theme_get_setting('masonry') == 1 ? array(
        'object' => NULL,
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/masonry/3.1.5/masonry.pkgd.min.js',
        'file'   => 'plugins/jquery.masonry.min.js',
      ) : NULL,
  );

  if (theme_get_setting('gsap') == 1) {
    $gsap = array(
      'gsap_css'    => array(
        'object' => 'CSSPlugin',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/plugins/CSSPlugin.min.js',
        'file'   => 'plugins/gsap/minified/plugins/CSSPlugin.min.js',
        'weight' => -80,
      ),
      'gsap_easing' => array(
        'object' => 'EasePack',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/easing/EasePack.min.js',
        'file'   => 'plugins/gsap/minified/easing/EasePack.min.js',
        'weight' => -79,
      ),
      'gsap_tweens' => array(
        'object' => 'TweenLite',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/TweenLite.min.js',
        'file'   => 'plugins/gsap/minified/TweenLite.min.js',
        'weight' => -78,
      ),
      'gsap'        => array(
        'object' => 'gsap',
        'cdn'    => '//cdnjs.cloudflare.com/ajax/libs/gsap/1.13.1/jquery.gsap.min.js',
        'file'   => 'plugins/gsap/minified/jquery.gsap.min.js',
        'weight' => -77,
      ),
    );

    $js_plugins = array_merge($js_plugins, $gsap);
  }
  cellular_add_js($js_plugins, TRUE);

  //
// Update jQuery & jQueryUI
  if (theme_get_setting('jquery_update') == 1) {

    $v_jq = theme_get_setting('jquery_version');
    $v_jqui = theme_get_setting('jqueryui_version');
    // Available cdns & path to scripts
    $networks = array(
      'google'    => array(
        'base_url' => '//ajax.googleapis.com/ajax/libs/',
        'jquery'   => 'jquery/' . $v_jq . '/jquery.min.js',
        'jqueryui' => 'jqueryui/' . $v_jqui . '/jquery-ui.min.js',
      ),
      'microsoft' => array(
        'base_url' => '//ajax.aspnetcdn.com/ajax/',
        'jquery'   => 'jquery/jquery-' . $v_jq . '.min.js',
        'jqueryui' => 'jquery.ui/' . $v_jqui . 'jquery-ui.min.js'
      ),
    );
    // Select cdn to use
    $cdn = $networks[theme_get_setting('cdn')];
// Override jQuery
    $jquery = array(
      'default'    => 'misc/jquery.js', //default script
      'object'     => 'jQuery', // window.object
      'version'    => $v_jq,
      'cdn'        => $cdn['base_url'] . $cdn['jquery'],
      'file'       => 'jquery-' . $v_jq . '.min.js',
      'group'      => JS_LIBRARY,
      'every_page' => TRUE,
      'weight'     => -100,
    );

    cellular_js_override($javascript, $jquery, TRUE);
// Override jQuery.form
    $jqueryform = array(
      'default'    => 'misc/jquery.form.js',
      'object'     => NULL, // window.object
      'version'    => '3.48',
      'file'       => 'plugins/jquery.form.min.js',
      'group'      => JS_LIBRARY,
      'every_page' => TRUE,
      'weight'     => -97,
    );

    cellular_js_override($javascript, $jqueryform, TRUE);
// Override jQueryUI
    $ui_widgets = array(
      'ui.core',
      'ui.accordion',
      'ui.autocomplete',
      'ui.button',
      'ui.datepicker',
      'ui.dialog',
      'ui.draggable',
      'ui.droppable',
      'ui.mouse',
      'ui.position',
      'ui.progressbar',
      'ui.resizable',
      'ui.selectable',
      'ui.slider',
      'ui.sortable',
      'ui.tabs',
      'ui.widget',
      'effects.blind',
      'effects.bounce',
      'effects.clip',
      'effects.drop',
      'effects.explode',
      'effects.fade',
      'effects.fold',
      'effects.highlight',
      'effects.pulsate',
      'effects.scale',
      'effects.shake',
      'effects.slide',
      'effects.transfer',
    );

    foreach ($ui_widgets as $widget) {
      $default = 'misc/ui/jquery.' . $widget . '.min.js';
      if (isset($javascript[$default])) {
        $script = array(
          'default'    => $default,
          'object'     => NULL,
          'version'    => $v_jqui,
          'group'      => JS_LIBRARY,
          'every_page' => FALSE,
          'weight'     => -96,
          'file'       => 'jquery-ui/' . $v_jqui . '/minified/jquery.' . $widget . '.min.js',
        );
        cellular_js_override($javascript, $script, TRUE);
      }
    }
  }

  if (theme_get_setting('modernizr') == 1) {
// Get full path to css directory
    $dir_css = $base_url . '/' . $theme_path . '/css/';
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

    drupal_add_js($yepnope, array('type' => 'inline', 'group' => CSS_SYSTEM, 'every_page' => TRUE, 'weight' => -999));
  }

  // dsm($javascript);
}