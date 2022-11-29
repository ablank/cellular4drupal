<?php

/**
 * @file
 * Functions to add javascript plugins.
 */

/**
 * Stylesheets used by javascript plugins.
 *
 * @return array
 *   Array of stylesheets used by javascript plugins.
 */
function cellular_plugins_css() {
  $plugin_path = '/lib/css/';
  $plugin_css = array();
  // Plugins available through cellular, styles added based on theme settings.
  // $plugin_css paths are relative to /libraries/cellular/css/.
  theme_get_setting('prism') == 1 ? $plugin_css['prism'] = array(
    'file' => 'prism.css',
    'weight' => 101,
  ) : NULL;

  theme_get_setting('nprogress') == 1 ? $plugin_css['nprogress'] = array(
    'file' => 'nprogress.css',
    'weight' => 101,
  ) : NULL;

  foreach ($plugin_css as &$plugin) {
    $plugin['group'] = !empty($plugin['group']) ? $plugin['group'] : CSS_DEFAULT;
    $plugin['file'] = $plugin_path . $plugin['file'];
  }

  return $plugin_css;
}
