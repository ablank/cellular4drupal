<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * hook_css_alter()
 */

function cellular_css_alter(&$css) {
// Add stylesheets to theme.
  $add_css = array(
// Paths are relative to /active_theme/css/
    'drupal' => array(
      'file'   => 'drupal.css',
      'weight' => 1,
    ),
    'style'  => array(
      'file'   => 'style.css',
      'weight' => 2,
    ),
    'print'  => array(
      'file'       => 'print.css',
      'media'      => 'print',
      'weight'     => 100,
      'preprocess' => FALSE,
    ),
  );


// Plugins available through cellular, styles added based on theme settings.
// $plugin_css paths are relative to /libraries/cellular/css/
  $plugin_css = array(
    'prism' => theme_get_setting('prism') == 1 ? array(
        'file' => 'plugins/prism.css',
      ) : NULL,
  );

  if (theme_get_setting('jquery_update') == 1) {
// Update the jQuery UI theme.
    $ui = array();
    $ui['update'] = NULL;
    $ui['version'] = theme_get_setting('jqueryui_version');
    $ui['theme'] = theme_get_setting('jqueryui_theme');
    $ui['use_cdn'] = theme_get_setting('jquery_cdn');
    $ui['path'] = 'jquery-ui/';
    $ui['widgets'] = array(
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
    );

    foreach ($ui['widgets'] as $widget) {
      $default = "misc/ui/jquery.$widget.css";
      if (isset($css[$default])) {
        // Unset default style.
        unset ($css[$default]);
        // Check if stylesheet is already added.
        // Set path to updated file.
        $file = $ui['path'] . $ui['version'] . '/' . $ui['theme'] . '/';
        $file .= 'jquery.ui.theme.css';

        if ($ui['theme'] === 'custom') {
          $ui['version'] === '1.10.4' ? $v = '1.10' : '1.9';
          $file = $ui['path'] . "jquery-ui.$v.css";

          $add_css['jquery-ui']['file'] = $file;
        }
        else {
          $file = $ui['path'] . $ui['version'] . '/' . $ui['theme'] . '/';
          $file .= 'jquery.ui.theme.css';
          //$plugin_css['jquery-ui']['cdn'] = isset($cdn) ? $cdn : NULL;
          $plugin_css['jquery-ui']['file'] = $file;
        }

        /* CDN stuff
        // Construct path based on theme settings
                if (($ui['use_cdn'] == 1) && ($ui['theme'] !== custom)) {
                  $v = $ui['version'];
                  $t = $ui['theme'];
        // Available cdns & path to scripts
                  $networks = array(
                    'google'    => array(
        // href="//ajax.googleapis.com/ajax/libs/jqueryui/1.11.1/themes/smoothness/jquery-ui.css"
                      'base_url' => "//ajax.googleapis.com/ajax/libs/jqueryui/",
                    ),
                    'microsoft' => array(
        // href="//ajax.aspnetcdn.com/ajax/jquery.ui/1.9.2/themes/black-tie/jquery-ui.css"
                      'base_url' => "//ajax.aspnetcdn.com/ajax/jquery.ui/",
                    ),
                  );
        // Select cdn to use
                  $cdn = $networks[theme_get_setting('cdn')];

                  $style = $cdn['base_url'] . "$v/themes/$t/jquery-ui.css";
                }
*/
      }
    }
  }

  cellular_add_css($css, $plugin_css, TRUE);
  cellular_add_css($css, $add_css);

// Nuke  all css not a member of group CSS_THEME
  if (theme_get_setting('remove_all_core_css') == 1) {
    foreach ($css as $key => $value) {
      if ($value['group'] != CSS_THEME) {
        $exclude[$key] = FALSE;
      }
    }
    $css = array_diff_key($css, $exclude);
  }

// Nuke  all SYSTEM css.
  if (theme_get_setting('remove_all_core_css') == 1) {
    foreach ($css as $key => $value) {
      if ($value['group'] == CSS_SYSTEM) {
        $exclude[$key] = TRUE;
      }
    }
    $css = array_diff_key($css, $exclude);
  }

// Remove Drupal's core css.
  if (theme_get_setting('remove_core_css') == 1) {
// Select module css to exclude.
    $exclude = array(
      'system'   => array(
        'system.base.css',
        'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block'    => 'block.css',
      'comment'  => 'comment.css',
      'field'    => 'theme/field.css',
      'filter'   => 'filter.css',
      'help'     => 'help.css',
      'menu'     => 'menu.css',
      'node'     => 'node.css',
      'search'   => 'search.css',
      'shortcut' => 'shorcut.css',
      'user'     => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
// dsm($css);
}
