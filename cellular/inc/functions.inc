<?php

/* * ************
  Get path to cellular
 * ************** */

function cellular_path() {
    // global $base_url;
    //$output =  $base_url . '/';

    $output = drupal_get_path('theme', 'cellular');

    return $output;
}

/* * ************
  Get path to current || child theme
 * ************** */

function cellular_theme_path(&$theme_key = null) {
    global $theme;

    $t_theme = isset($theme_key) ? $theme_key : $theme;

    $theme_path = drupal_get_path('theme', $t_theme);

    return $theme_path;
}

/* * ************
  Merge attributes arrays
 * ************** */

function cellular_merge(&$arr) {
    $output = '';
    foreach ($arr as $a) {
        $output .= (is_array($a)) ? implode_r(' ', $a) : " " . $a;
    }
    return $output;
}

/* * ************
  Add <link> & <meta> tags from array
 * ************** */

function cellular_build_head_tags(&$meta_array) {
    $base_weight = 0;


    foreach ($meta_array as $meta) {
        // Build tag
        /*
        $tag = array(
            '#type' => 'html_tag',
            '#tag' => isset($meta['tag']) ? $meta['tag'] : 'link',
            '#attributes' => array(
                $meta['attr'] => $meta['attr_val'],
                'content' => $meta['content']
            ),
            '#weight' => isset($meta['weight']) ? $meta['weight'] : $base_weight
        );
        isset($meta['rel']) ? $tag['#attributes']['rel'] = $meta['rel'] : NULL;
        isset($meta['type']) ? $tag['#attributes']['type'] = $meta['type'] : NULL;
        isset($meta['size']) ? $tag['#attributes']['sizes'] = $meta['size'] : NULL;
        isset($meta['href']) ? $tag['#attributes']['href'] = $meta['href'] : NULL;
        // Add tag
        drupal_add_html_head($tag, 'meta_' . $meta['attr_val']);
*/
        
          $tag = array(
          '#type' => 'html_tag',
          '#tag' => 'meta',
          '#attributes' => array(
          $meta['attr'] => $meta['attr_val'],
          'content' => $meta['content']
          ),
          '#weight' => isset($meta['weight']) ? $meta['weight'] : $base_weight
          );
          drupal_add_html_head($tag, 'meta_' . $meta['attr_val']);
         
    }
}

/* * ************
  favicons & apple-touch-icons
 * ************** */

function cellular_favicon(&$icon_array) {

    $icon_dir = cellular_theme_path() . '/assets/icons';
    $base_weight = 0;

    foreach ($icon_array as $icon) {
        $link = array(
            '#type' => 'html_tag',
            '#tag' => 'link',
            '#attributes' => array(
                'rel' => $icon['rel'],
            ),
            '#weight' => isset($icon['weight']) ? $icon['weight'] : $base_weight++,
        );
        isset($icon['type']) ? $link['#attributes']['type'] = $icon['type'] : NULL;
        isset($icon['size']) ? $link['#attributes']['sizes'] = $icon['size'] : NULL;
        isset($icon['href']) ? $link['#attributes']['href'] = $icon_dir . '/' . $icon['href'] : NULL;

        drupal_add_html_head($link, 'icon_' . $link['#attributes']['href']);
    }
}

/* * ************
  Main Menu
 * ************** */

function cellular_main_menu(&$vars) {
    if (theme_get_setting('full_menu') == 1) {

        // Render the full main menu tree
        // Use css / js to show/hide sub-menus
        $main_menu_tree = menu_tree_all_data('main-menu');
    } else {
        $main_menu_tree = menu_main_menu();
    }
    return menu_tree_output($main_menu_tree);
}

/* * ************
  Sidebar Test
 * ************** */

function cellular_test_sidebar(&$vars) {
    $sidebar_left = !empty($vars['page']['sidebar_left']) ? 1 : null;
    $sidebar_right = !empty($vars['page']['sidebar_right']) ? 1 : null;

    // Check if sidebars are rendered & set classes accordingly
    if (isset($sidebar_left) && isset($sidebar_right)) {
        $sidebars = 'dual-sidebars';
    } elseif (isset($sidebar_left) || isset($sidebar_right)) {
        $sidebars = 'single-sidebar';
    } else {
        $sidebars = 'no-sidebars';
    }

    return $sidebars;
}

/* * ************
  Remove stylesheets
 * ************** */

function cellular_remove_css($exclude, &$css) {

    foreach ($exclude as $module => $stylesheet) {
        // Remove multiple stylesheets attached by module
        if (is_array($stylesheet)) {
            foreach ($stylesheet as $style) {
                unset($css[drupal_get_path('module', $module) . '/' . $style]);
            }
            // Remove individual stylesheet
        } else {
            unset($css[drupal_get_path('module', $module) . '/' . $stylesheet]);
        }
    }
}

/* * ************
  Add stylesheets
 * ************** */

function cellular_add_css($array, &$css) {
    foreach ($array as $style) {
        if (isset($style)) {
            $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
            $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
            $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
            $style['weight'] = isset($style['weight']) ? $style['weight'] : 10;
            $style['type'] = 'file';
            $style['data'] = cellular_theme_path() . '/css/' . $style['file'];
            $style['media'] = isset($style['media']) ? $style['media'] : 'all';
            $style['browsers'] = array(
                'IE' => TRUE,
                '!IE' => TRUE,
            );

            $css[$style['file']] = $style;
        }
    }
    return $css;
}

/* * ************
  Add scripts from array
 * ************** */

function cellular_add_js($array) {
    foreach ($array as $script) {
        if (!empty($script)) {
            drupal_add_js(cellular_theme_path() . '/js/' . $script['file'], array(
                'type' => 'file',
                'group' => isset($script['group']) ? $script['group'] : JS_THEME,
                'every_page' => $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE,
                'weight' => $script['weight']
            ));
        }
    }
}

/* * ************
  Load jQuery libs via CDN
 * ************** */

function cellular_js_cdn(&$script) {

    $cdn = theme_get_setting('cdn');
    $v = (string) $script['version'];
    /*
      $jQuery = array(
      'object' => 'jQuery', // window.object
      'version' => theme_get_setting('jquery_version'),
      'weight' => -9999,
      'group' => JS_LIBRARY,
      );
     */

    $src = array();

    switch ($cdn) {
        case 'google' :
//<script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.1/jquery.min.js"></script>
            $src['jquery'] = '//ajax.googleapis.com/ajax/libs/jquery/' . $v . '/jquery.min.js';
//<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.10.3/jquery-ui.min.js"></script>
            $src['jqueryui'] = '//ajax.googleapis.com/ajax/libs/jqueryui/' . $v . '/jquery-ui.min.js';
            break;
        case 'microsoft' :
//<script src="http://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.8.2.min.js"></script>
            $src['jquery'] = '//ajax.aspnetcdn.com/ajax/jQuery/jquery-' . $v . '.min.js';
//<script src="http://ajax.aspnetcdn.com/ajax/jquery.ui/1.8.22/jquery-ui.js"></script>
            $src['jqueryui'] = '//ajax.aspnetcdn.com/ajax/jquery.ui/' . $v . '/jquery-ui.min.js';
            break;
    }
    switch ($script['object']) {
        case 'jQuery' :
            $output = $src['jquery'];
            break;
        case 'jQuery.ui' :
            $output = $src['jqueryui'];
            break;
    }

    return $output;
}

/* * ************
  Javascript fallback to local source if CDN fails
 * ************** */

function cellular_js_fallback(&$script) {

    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"';
    $fallback .= cellular_path() . '/js/' . strtolower($script['object']) . '-' . $script['version'] . '.min.js';
    $fallback .= '\">\x3C/script>")';

    drupal_add_js($fallback, array(
        'group' => $script['group'],
        'weight' => $script['weight'],
        'type' => 'inline',
        'every_page' => TRUE,
    ));
}

function cellular_form_strip_access(&$form) {
    // Nuke text format options
    $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;

    // Remove individual text format options
    /*
      $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
      $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
      $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
      $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
     */

    return $form;
}

function cellular_update_jquery(&$javascript) {
    $jquery = array(
        'jquery' => array(
            'object' => 'jQuery', // window.object
            'version' => theme_get_setting('jquery_version'),
            'group' => JS_LIBRARY,
            'every_page' => TRUE,
            'weight' => -998,
        ),
        'jqueryform' => array(
            'object' => null, // window.object
            'version' => '3.4.8',
            'group' => JS_LIBRARY,
            'every_page' => TRUE,
            'weight' => -97,
        ),
    );
    // Replace jQuery with updated version
    if (isset($javascript['misc/jquery.js'])) {
        $javascript['misc/jquery.js']['data'] = cellular_js_cdn($jquery['jquery']);
        $javascript['misc/jquery.js']['version'] = $jquery['jquery']['version'];
        $javascript['misc/jquery.js']['group'] = $jquery['jquery']['group'];
        $javascript['misc/jquery.js']['every_page'] = $jquery['jquery']['every_page'];
        $javascript['misc/jquery.js']['weight'] = $jquery['jquery']['weight'];
        $javascript['misc/jquery.js']['type'] = 'external';

        cellular_js_fallback($jquery['jquery']);
    }

    // Replace jQuery.form with updated version
    if (isset($javascript['misc/jquery.form.js'])) {
        $javascript['misc/jquery.form.js']['data'] = cellular_path() . '/js/plugins/jquery.form.min.js';
        $javascript['misc/jquery.form.js']['version'] = $jquery['jqueryform']['version'];
        $javascript['misc/jquery.form.js']['group'] = $jquery['jqueryform']['group'];
        $javascript['misc/jquery.form.js']['every_page'] = $jquery['jqueryform']['every_page'];
        $javascript['misc/jquery.form.js']['weight'] = $jquery['jqueryform']['weight'];
        $javascript['misc/jquery.form.js']['type'] = 'file';
    }
}

function cellular_update_jqueryui(&$javascript) {

    $ui_version = theme_get_setting('jqueryui_version');
    $ui_path = drupal_get_path('theme', 'cellular') . '/js/jquery-ui/' . $ui_version . '/minified';
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

    // Construct the jQuery UI path and replace the JavaScript.
    foreach ($ui_widgets as $file) {

        $corefile = 'misc/ui/jquery.' . $file . '.min.js';

        if (isset($javascript[$corefile])) {
            $javascript[$corefile]['data'] = $ui_path . '/jquery.' . $file . '.min.js';
            $javascript[$corefile]['version'] = $ui_version;
        }
    }
}
