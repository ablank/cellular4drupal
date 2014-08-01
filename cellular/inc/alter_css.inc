<?php

/* * ************
  css_alter()

  Remove / Rearrange stylesheets
 * ************** */

function cellular_css_alter(&$css) {
    global $base_url;
    // Add stylesheets to theme
    $add_css = array(
        'drupal' => array(
            'file' => cellular_theme_path() . '/css/drupal.css',
            'weight' => 1
        ),
        'style' => array(
            'file' => cellular_theme_path() . '/css/style.css',
            'weight' => 2
        ),
        'print' => array(
            'file' => cellular_theme_path() . '/css/print.css',
            'media' => 'print',
            'weight' => 100,
            'preprocess' => FALSE,
        ),
        // Conditional styles based on theme settings:
        'prism' => theme_get_setting('prism') == 1 ?
                array(
            'file' => cellular_path() . '/css/plugins/prism.css'
                ) : null,
    );

    cellular_add_css($add_css, $css);

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
