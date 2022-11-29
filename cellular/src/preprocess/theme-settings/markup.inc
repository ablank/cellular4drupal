<?php

/**
 * @file
 * Theme-settings: Display & styling settings.
 */

$form[0]['markup_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Markup'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form[0]['markup_settings']['field_wrappers'] = array(
  '#type' => 'checkbox',
  '#title' => t('Field Wrappers'),
  '#description' => t("Wrap fields with a div containing the field \$attributes"),
  '#default_value' => theme_get_setting('field_wrappers'),
);

$form[0]['markup_settings']['full_menu'] = array(
  '#type' => 'checkbox',
  '#title' => t('Display All Links in Main Menu'),
  '#description' => t('Print the full main_menu tree instead of only top level links. Useful for styling with custom scripts/stylesheets.'),
  '#default_value' => theme_get_setting('full_menu'),
);

$form[0]['markup_settings']['breadcrumb_display'] = array(
  '#type' => 'checkbox',
  '#title' => t('Display Breadcrumbs'),
  '#description' => t("Show breadcrumb navigation (Doesn't display on frontpage)"),
  '#default_value' => theme_get_setting('breadcrumb_display'),
);

$form[0]['markup_settings']['use_colorbox'] = array(
  '#type' => 'checkbox',
  '#title' => t('Use Colorbox for User Login/Register links.'),
  '#description' => t("Use Colorbox Node (<em>if available</em>) to display User Login/Register forms."),
  '#default_value' => theme_get_setting('use_colorbox'),
);

$form[0]['markup_settings']['copyright'] = array(
  '#type' => 'textfield',
  '#title' => t('Copyright'),
  '#description' => t("The name of the person or organization to display indicating copyright ownership. Leave field empty to disable display."),
  '#default_value' => theme_get_setting('copyright'),
);
$form[0]['markup_settings']['login'] = array(
  '#type' => 'fieldset',
  '#title' => t('User Login Block'),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['markup_settings']['login']['login_block_orientation'] = array(
  '#type' => 'select',
  '#title' => t('Login Block Orientation'),
  '#description' => t('This setting adds a class (horizontal || vertical) to the user login block.'),
  '#options' => array(
    'vertical' => t('vertical'),
    'horizontal' => t('horizontal'),
  ),
  '#default_value' => theme_get_setting('login_block_orientation '),
);

$form[0]['markup_settings']['login']['login_block_register'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show link to Register New User Account'),
  '#description' => t('Checking this setting shows the link to register new user account.'),
  '#default_value' => theme_get_setting('login_block_register'),
);

$form[0]['markup_settings']['login']['login_block_password'] = array(
  '#type' => 'checkbox',
  '#title' => t('Show link to reset password'),
  '#description' => t('Checking this setting shows the link to reset user password.'),
  '#default_value' => theme_get_setting('login_block_password'),
);
