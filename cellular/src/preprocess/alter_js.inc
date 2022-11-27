<?php
/**
 * @file
 * Add/Update/Delete javascript.
 */

/**
 * Implements hook_js_alter().
 */
function cellular_js_alter(&$javascript) {
  // Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jquery_update($javascript);
    cellular_jqueryui_update_js($javascript);
  }

  // Override misc. js
  $override = array();
  /*
  if (module_exists('admin_menu')) {
    /*
    $override['admin_menu'] = array(
      'default' => drupal_get_path('module', 'admin_menu') . '/admin_menu.js',
      'file' => drupal_get_path('theme', 'cellular') . '/js/admin_menu.js',
    //'version' => '',
    );*/
  }
  */
  foreach ($override as &$js) {
    $js['group'] = JS_LIBRARY;
    cellular_js_override($javascript, $js);
  }

  // dpm($javascript);
}
