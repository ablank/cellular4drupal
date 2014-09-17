<?php

/**
 * @file
 * Get theme-settings.
 */

/**
 * Cellular hook_form_system_theme_settings_alter().
 */
function cellular_form_system_theme_settings_alter(&$form, $form_state) {
  // Define form to hold pages as tabs.
  $form['c'] = array(
    '#type'        => 'vertical_tabs',
    '#description' => t('Layout'),
    '#weight'      => -10,
    '#attached'    => array(),
  );

  $ipath = drupal_get_path('theme', 'cellular') . '/config/';
  $pages = array(
    'personalize.inc',
    'style.inc',
    'js.inc',
    'social.inc',
  );

  foreach ($pages as $page) {
    require_once $ipath . $page;
  }
}
