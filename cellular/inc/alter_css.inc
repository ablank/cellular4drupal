<?php

/*
 * @file
 * Add/Update/Delete stylesheets
 */

/*
 * hook_css_alter()
 */

function cellular_css_alter(&$css) {
    global $cellular_lib, $theme_path;
    // Add stylesheets to theme
    // Paths are relative to /active_theme/css/
    $add_css = array(
        'drupal' => array('file' => 'drupal.css', 'weight' => 1),
        'style' => array('file' => 'style.css', 'weight' => 2),
        'print' => array(
            'file' => 'print.css',
            'media' => 'print',
            'weight' => 100,
            'preprocess' => FALSE,
        ),
    );

    cellular_add_css($css, $add_css);


// Plugins available through cellular, styles added based on theme settings
// $plugin_css paths are relative to /libraries/cellular/css/
    $plugin_css = array(
        'prism' => theme_get_setting('prism') == 1 ? array(
            'file' => 'plugins/prism.css' // Path relative to /cellular/css/
                ) : NULL,
    );
    cellular_add_css($css, $plugin_css, TRUE);


    // get the jQuery UI theme
    $ui = array(
        'version' => theme_get_setting('jqueryui_version'),
        'path' => $cellular_lib . '/css/jquery-ui',
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
                $ui['path'] .= '1.10.custom.css';
            } else {
                $ui['path'] .= '1.9.custom.css';
            }
        } else {
            $ui['path'] .= $ui['version'] . '/' . $ui['theme'];
        }

        // Set data source
        foreach ($ui['files'] as $file) {
            if (isset($css["misc/ui/jquery.$file.css"])) {
                if ($ui['theme'] === 'custom') {
                    $css["misc/ui/jquery.$file.css"]['data'] = $ui['path'];
                } else {
                    // Load specific UI theme css
                    $css["misc/ui/jquery.$file.css"]['data'] = $ui['path'] . "/jquery.$file.css";
                }
            }
        }
    }


// Remove Drupal's core CSS
    if (theme_get_setting('remove_core_css') == 1) {
        /* // Nuke  all SYSTEM css
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

        cellular_remove_css($css, $exclude);
    }
    //dsm($css);
}
