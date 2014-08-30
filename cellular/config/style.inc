<?php
/**
 * @file
 * Theme-settings: Display & styling options.
 */

$form['c']['display_settings'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Style'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE
);

$form['c']['display_settings']['full_menu'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Display All Links in Main Menu'),
  '#description'   => t('Print the full main_menu tree instead of only top
  level links.'),
  '#default_value' => theme_get_setting('full_menu'),
);

$form['c']['display_settings']['breadcrumb_display'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Display Breadcrumbs'),
  '#description'   => t("Show breadcrumb navigation (Doesn't display on
  frontpage)"),
  '#default_value' => theme_get_setting('breadcrumb_display'),
);

$form['c']['display_settings']['breadcrumb_separator'] = array(
  '#type'          => 'textfield',
  '#size'          => 8,
  '#maxlength'     => 10,
  '#title'         => t('Breadcrumb separator'),
  '#description'   => t('Symbol used to separate breadcrumb links.'),
  '#default_value' => theme_get_setting('breadcrumb_separator'),
  '#states'        => array(
    'visible' => array(
      ':input[name="breadcrumb_display"]' => array('checked' => TRUE),
    ),
  ),
);

$form['c']['display_settings']['r'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Remove Drupal CSS'),
  '#description' => t('Prevent stylesheet groups from loading. Individual
   stylesheets can be removed by adding the module & stylesheet to the array
   $exclude and calling function cellular_remove_css() in /inc/css_alter.inc'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE
);
$form['c']['display_settings']['r']['remove_all_css'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Remove All Non-Theme CSS'),
  '#description'   => t("Removes all stylesheets that are not a member of group
  'CSS_THEME'."),
  '#default_value' => theme_get_setting('remove_all_css')
);
$form['c']['display_settings']['r']['remove_all_system_css'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Remove Drupal CSS'),
  '#description'   => t("Removes all stylesheets that are a member of group
  'CSS_SYSTEM'"),
  '#default_value' => theme_get_setting('remove_all_system_css')
);
$form['c']['display_settings']['r']['remove_core_css'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Remove Drupal Core CSS'),
  '#description'   => t("Exclude some Drupal core CSS. "),
  '#default_value' => theme_get_setting('remove_core_css'),
);

$form['c']['display_settings']['login'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('User Login Block Settings'),
  '#description' => t("Change User Login Block settings"),
  '#collapsible' => TRUE,
  '#collapsed'   => TRUE
);
$form['c']['display_settings']['login']['login_block_orientation'] = array(
  '#type'          => 'select',
  '#title'         => t('Login Block Orientation'),
  '#description'   => t('This setting adds a class (horizontal || vertical)
   to the user login block.'),
  '#options'       => array(
    'vertical'   => t('vertical'),
    'horizontal' => t('horizontal'),
  ),
  '#default_value' => theme_get_setting('login_block_orientation '),
);
$form['c']['display_settings']['login']['login_block_register'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Show link to Register New User Account'),
  '#description'   => t('Checking this setting shows the link to register a
   new user account.'),
  '#default_value' => theme_get_setting('login_block_register'),
);

$form['c']['display_settings']['login']['login_block_password'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Show link to reset password'),
  '#description'   => t('Checking this setting shows the link to reset
  user password.'),
  '#default_value' => theme_get_setting('login_block_password'),
);


$form['c']['display_settings']['add_classes'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Content Class Settings'),
  '#description' => t("Classes to add to #content and #sidebars for simplified
   layout with a grid."),
  '#collapsible' => TRUE,
  '#collapsed'   => TRUE
);
$form['c']['display_settings']['add_classes']['content_class_no_sidebars'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Default Content Class'),
  '#description'   => t("Class to add to #content if no sidebars are present."),
  //'#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_no_sidebars'),
);
$form['c']['display_settings']['add_classes']['content_class_single_sidebar'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Content Class w/ Single Sidebar'),
  '#description'   => t("Class to add to #content if one sidebar is displayed."),
  //'#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_single_sidebar'),
);
$form['c']['display_settings']['add_classes']['sidebar_class_single_sidebar'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Sidebar Class w/ Single Sidebar'),
  '#description'   => t("Class to add to #sidebar-left || #sidebar-right if a
   single sidebar is displayed."),
  //'#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_single_sidebar'),
);
$form['c']['display_settings']['add_classes']['content_class_dual_sidebars'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Content Class w/ Dual Sidebars'),
  '#description'   => t("Class to add to #content if both sidebars are displayed."),
  //'#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_dual_sidebars'),
);
$form['c']['display_settings']['add_classes']['sidebar_class_dual_sidebars'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Sidebar Class w/ Dual Sidebars'),
  '#description'   => t("Class to add to #sidebar-left && #sidebar-right if both
   sidebars are displayed."),
  //'#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_dual_sidebars'),
);
