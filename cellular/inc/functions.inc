<?php
/**
 * @file
 * Cellular utility functions
 */

/*
*  Get path to cellular
 */

function cellular_path()
{
    // global $base_url;
    //$output =  $base_url . '/';
    return drupal_get_path('theme', 'cellular');
}

/*
*  Get path to active theme
 */

function cellular_theme_path(&$theme_key = null)
{
    $t_theme = isset($theme_key) ? $theme_key : $GLOBALS['theme'];
    $theme_path = drupal_get_path('theme', $t_theme);

    return $theme_path;
}

/*
*  Merge attributes arrays
*/

function cellular_merge($arr)
{
    foreach ($arr as $a) {
        $output = (is_array($a)) ? implode_r(' ', $a) : " " . $a;
    }
    return $output;
}

/*
 * Add head tags (<link> & <meta>)from array
 */

function cellular_build_head_tags(&$array)
{
    $base_weight = 0;

    foreach ($array as $meta => $val) {
        // Build tag
        $tag = array(
            '#type' => 'html_tag',
            '#tag' => $val['tag'],
            '#attributes' => array(),
            '#weight' => isset($val['weight']) ? $val['weight'] : $base_weight
        );

        // Misc. attr/val
        isset($val['attr']) && isset($val['attr_val']) ? $tag['#attributes'][$val['attr']] = $val['attr_val'] : NULL;
        // General attributes
        isset($val['name']) ? $tag['#attributes']['name'] = $val['name'] : NULL;
        isset($val['rel']) ? $tag['#attributes']['rel'] = $val['rel'] : NULL;
        isset($val['content']) ? $tag['#attributes']['content'] = $val['content'] : NULL;
        isset($val['href']) ? $tag['#attributes']['href'] = $val['href'] : NULL;
        // Attributes for favicons
        isset($val['size']) ? $tag['#attributes']['sizes'] = $val['size'] : NULL;
        isset($val['type']) ? $tag['#attributes']['type'] = $val['type'] : NULL;

        drupal_add_html_head($tag, 'meta_' . $meta);

    }
}


/*
 * Add stylesheets
 */

function cellular_add_css(&$css, $array, $cellular)
{
    foreach ($array as $style) {
        if (!empty($style)) {

            $spath = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];

            $spath .= '/css/' . $style['file'];

            $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
            $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
            $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
            $style['weight'] = isset($style['weight']) ? $style['weight'] : 10;
            $style['type'] = isset($style['type']) ? $style['type'] : 'file';
            $style['data'] = $spath;
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


/*
*  Remove stylesheets
 */

function cellular_remove_css(&$css, $exclude)
{
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

/*
 * Override stylesheets
 */
/*
function cellular_override_css(&$css, $ostyle, $stylesheet)
{
    foreach ($stylesheet as $override) {
        if (isset($css[$style])) {
            $css[$ostyle]['version'] = isset($override['version']) ? $override['version'] : NULL;
            $css[$ostyle]['type'] = isset($override['type']) ? $override['type'] : 'external';
            $css[$ostyle]['group'] = isset($override['group']) ? $override['group'] : CSS_THEME;
            $css[$ostyle]['every_page'] = isset($override['every_page']) ? $override['every_page'] : TRUE;
            $css[$ostyle]['weight'] = isset($override['weight']) ? $override['weight'] : 0;

            // Set data source to cdn if available
            if (isset($override['cdn'])) {
                $css[$ostyle]['data'] = $override['cdn'];
                // Add local fallback
                cellular_js_fallback($override, TRUE);
            } else {
                // Set data source to local script if no cdn
                $css[$ostyle]['data'] = $GLOBALS['cellular_lib'] . 'css/' . $override['file'];
            }
        }
        return $css;
    }

}
*/

/*
*  Override javascript
*/
function cellular_js_override(&$javascript, $script, $override)
{
    if (isset($javascript[$script])) {
        $javascript[$script]['version'] = isset($override['version']) ? $override['version'] : NULL;
        $javascript[$script]['type'] = isset($override['type']) ? $override['type'] : 'external';
        $javascript[$script]['group'] = isset($override['group']) ? $override['group'] : JS_THEME;
        $javascript[$script]['every_page'] = isset($override['every_page']) ? $override['every_page'] : TRUE;
        $javascript[$script]['weight'] = isset($override['weight']) ? $override['weight'] : 0;
        $javascript[$script]['preprocess'] = isset($override['preprocess']) ? $override['preprocess'] : TRUE;
        $javascript[$script]['defer'] = isset($override['defer']) ? $override['defer'] : FALSE;
        $javascript[$script]['cache'] = isset($override['cache']) ? $override['cache'] : TRUE;
        // Set data source to cdn if available
        if (isset($override['cdn'])) {
            $javascript[$script]['data'] = $override['cdn'];
            // Add local fallback
            cellular_js_fallback($override, TRUE);
        } else {
            // Set data source to cellular.lib script if no cdn
            $javascript[$script]['data'] = $GLOBALS['cellular_lib'] . '/js/' . $override['file'];
        }
    }
}

/*
 * Add scripts to $javascript from an array of parameters
*/

function cellular_add_js($array, $cellular)
{
    foreach ($array as $script) {
        // Do we have info?
        if (!empty($script)) {
            //Check if link is local or cdn to set paths
            if (isset($script['cdn'])) {
                $spath = $script['cdn'];
                // Call local fallback if CDN unavailable
                cellular_js_fallback($script, $cellular);
            } else {
                // Set path to base theme if $cellular
                $spath = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
                $spath .= '/js/' . $script['file'];
            }

            // Add $script
            drupal_add_js($spath, array(
                'type' => isset($script['cdn']) ? 'external' : 'file',
                'group' => isset($script['group']) ? $script['group'] : JS_THEME,
                'every_page' => $script['every_page'] = isset($script['every_page']) ? $script['every_page'] : TRUE,
                'weight' => isset($script['weight']) ? $script['weight'] : 0,
            ));
        }
    }
}

/*
 * Inline javascript fallback call to local source if CDN fails
 */

function cellular_js_fallback($script, $cellular)
{
// Check if base or child theme
    $spath = $cellular ? $GLOBALS['cellular_lib'] : $GLOBALS['theme_path'];
    $spath .= '/js/' . $script['file'];
    $fallback = 'window.' . $script['object'] . ' || document.write("<script src=\"' . $spath . '\">\x3C/script>")';

    drupal_add_js($fallback, array(
        'type' => 'inline',
        'group' => isset($script['group']) ? $script['group'] : JS_THEME,
        'weight' => isset($script['weight']) ? $script['weight'] + 1 : 0,
        'every_page' => isset($script['every_page']) ? $script['every_page'] : TRUE,
    ));
}

/*
*Remove text formatting options from forms
 */

function cellular_form_strip_access(&$form)
{
    // Nuke text format options
    $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;
    /*
        // Remove individual text format options
          $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
          $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
          $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
          $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
         */

    return $form;
}

/*
* Update jquery & any related javascript
 */

function cellular_update_jquery(&$javascript)
{
    // Set jQuery override params
    $jquery = [
        'object' => 'jQuery', // window.object
        'version' => theme_get_setting('jquery_version'),
        'group' => JS_LIBRARY,
        'every_page' => TRUE,
        'file' => 'jquery-' . theme_get_setting('jquery_version') . '.min.js',
        'weight' => -998,
    ];
// Query cellular_cdn() to build path based on theme settings
    $jquery['cdn'] = cellular_cdn($jquery);

    cellular_js_override($javascript, 'misc/jquery.js', $jquery);
//
    $jqueryform = array(
        'object' => null, // window.object
        'version' => '3.48',
        'group' => JS_LIBRARY,
        'every_page' => TRUE,
        'file' => '/plugins/jquery.form.min.js',
        'weight' => -97,

    );
    cellular_js_override($javascript, 'misc/jquery.form.js', $jqueryform);
}


/*
* Update jqueryui javascript
 */
function cellular_update_jqueryui(&$javascript)
{

    $ui_version = theme_get_setting('jqueryui_version');
    $ui_path = $GLOBALS['cellular_lib'] . 'js/jquery-ui/' . $ui_version . '/minified';
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

/*
 * Build paths to Google or Microsoft CDN assets based on theme settings
 */
function cellular_cdn(&$script)
{
    $output = '';
    $provider = theme_get_setting('cdn');
    $v = (string)$script['version'];

    $cdn = array();

    if ($provider == 'google') {
        $cdn['base_path'] = '//ajax.googleapis.com/ajax/libs/';
        $cdn['jquery'] = 'jquery/' . $v . '/jquery.min.js';
        $cdn['jqueryui'] = 'jqueryui/' . $v . '/jquery-ui.min.js';
    } elseif ($provider == 'microsoft') {
        $cdn['base_path'] = '//ajax.aspnetcdn.com/ajax/';
        $cdn['jquery'] = 'jQuery/jquery-' . $v . '.min.js';
        $cdn['jqueryui'] = 'jquery.ui/' . $v . '/jquery-ui.min.js';
    }

    if ($script['object'] === 'jQuery') {
        $output = $cdn['base_path'] . $cdn['jquery'];;
    } elseif ($script['object'] === 'jQuery.ui') {
        $output = $cdn['base_path'] . $cdn['jqueryui'];
    }

    return $output;
}

/*
* Get the full main menu tree
 */

function cellular_main_menu()
{
    if (theme_get_setting('full_menu') == 1) {

        // Render the full main menu tree
        // Use css / js to show/hide sub-menus
        $main_menu_tree = menu_tree_all_data('main-menu');
    } else {
        $main_menu_tree = menu_main_menu();
    }

    return menu_tree_output($main_menu_tree);
}

/*
*  Test if sidebar blocks regions are used on page & return appropriate class
*/

function cellular_test_sidebar(&$vars)
{
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
