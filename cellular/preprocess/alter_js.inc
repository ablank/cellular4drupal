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

  if (theme_get_setting('requirejs') == 1) {
    $javascript['requirejs'] = array(
      'data' => cellular_requirejs($javascript),
      'type' => 'inline',
      'scope' => 'critical',
      'group' => JS_LIBRARY,
      'defer' => FALSE,
      'every_page' => TRUE,
      'weight' => 100,
    );
  }

   // dpm($javascript);
}
