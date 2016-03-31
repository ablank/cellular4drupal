<?php
/**
 * @file
 * Cellular theme-settings.
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function cellular_form_system_theme_settings_alter(&$form, $form_state) {
  // Define form to hold pages as tabs.
  $form[0] = array(
    '#type' => 'vertical_tabs',
    '#description' => t('Layout'),
    '#weight' => -10,
    '#attached' => array(),
  );
