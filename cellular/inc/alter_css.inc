<?php

/* * ************
  css_alter()

  Remove / Rearrange stylesheets
 * ************** */

function cellular_css_alter(&$css) {

    // Add stylesheets to theme
    // Paths are relative to /active_theme/css/
    $add_css = array(
        'drupal' => array(
            'file' => 'drupal.css',
            'weight' => 1
        ),
        'style' => array(
            'file' => 'style.css',
            'weight' => 2
        ),
        'print' => array(
            'file' => 'print.css',
            'media' => 'print',
            'weight' => 100,
            'preprocess' => FALSE,
        ),
    );

    cellular_add_css($add_css, $css);


// Plugins available through cellular, styles added based on theme settings
// $plugin_css paths are relative to /cellular/css/
    $plugin_css = array(
        'prism' => theme_get_setting('prism') == 1 ?
                array(
            'file' => 'plugins/prism.css' // Path relative to /cellular/css/
                ) : null,
    );

    if (!empty($plugin_css)) {
        foreach ($plugin_css as $style) {
            if (isset($style)) {
                $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
                $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
                $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
                $style['weight'] = isset($style['weight']) ? $style['weight'] : 10;
                $style['type'] = 'file';
                $style['data'] = cellular_path() . '/css/' . $style['file'];
                $style['media'] = isset($style['media']) ? $style['media'] : 'all';
                $style['browsers'] = array(
                    'IE' => TRUE,
                    '!IE' => TRUE
                );

                $css[$style['file']] = $style;
            }
        }
    }


    // get the jQuery UI theme
    $ui = array(
        'version' => theme_get_setting('jqueryui_version'),
        'path' => cellular_path() . '/css' . '/jquery-ui',
        'theme' => theme_get_setting('jqueryui_theme'),
        'files' => array(
            'ui.core',
            'ui.theme',
            'ui.accordion',
            'ui.autocomplete',
            'ui.button',
            'ui.datepicker',
            'ui.dialog',
            'ui.progressbar',
            'ui.resizable',
            'ui.selectable',
            'ui.slider',
            'ui.tabs',
        ),
    );

    // Construct path based on theme settings
    if (theme_get_setting('jquery_update') == 1) {

        if ($ui['theme'] == 'custom') {
            if ($ui['version'] == '1.10.1') {
                $ui['path'] = cellular_theme_path() . '/css/jquery-ui/1.10.custom.css';
            } else {
                $ui['path'] = cellular_theme_path() . '/css/jquery-ui/1.9.custom.css';
            }
        } else {
            $ui['path'] = $ui['path'] . '/' . $ui['version'] . '/' . $ui['theme'];
        }
    } else {
        $ui['path'] = $ui['path'] . '/1.8.7/' . $ui['theme'];
    }

    // Custom UI themes made with themeroller don't come with individual stylesheets
    //

    // Set data source

    foreach ($ui['files'] as $file) {
        if (isset($css["misc/ui/jquery.$file.css"])) {
            if ($ui['theme'] == 'custom') {
                $css["misc/ui/jquery.$file.css"]['data'] = $ui['path'];
            } else {
                // Load specific UI theme css
                $css["misc/ui/jquery.$file.css"]['data'] = $ui['path'] . "/jquery.$file.css";
            }
        }
    }


// Remove Drupal's core CSS
    if (theme_get_setting('remove_core_css') == 1) {
        /* // Remove all SYSTEM css
          foreach ($css as $key => $value) {
          if ($value['group'] == CSS_SYSTEM) {
          $exclude[$key] = TRUE;
          }
          }
          $css = array_diff_key($css, $exclude);
         */

        $exclude = array(
            'system' => array(
                'system.base.css',
                'system.menus.css',
                'system.messages.css',
                'system.theme.css'
            ),
            'block' => 'block.css',
            'comment' => 'comment.css',
            'field' => 'theme/field.css',
            'filter' => 'filter.css',
            'help' => 'help.css',
            'menu' => 'menu.css',
            'node' => 'node.css',
            'search' => 'search.css',
            'shortcut' => 'shorcut.css',
            'user' => 'user.css'
        );

        cellular_remove_css($exclude, $css);
    }
    //dsm($css);
}
