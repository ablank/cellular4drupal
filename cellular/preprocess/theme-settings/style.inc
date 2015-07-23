<?php
/**
 * @file
 * Theme-settings: Display & styling settings.
 */
//
$form['c']['style_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Style'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form['c']['style_settings']['min_style'] = array(
  '#type' => 'checkbox',
  '#title' => t('Use minified stylesheets (<em>.min.css</em>).'),
  '#default_value' => theme_get_setting('min_style'),
);

$form['c']['style_settings']['r'] = array(
  '#type' => 'fieldset',
  '#title' => t('Remove Drupal CSS'),
  '#description' => t('Prevent stylesheet groups from loading. Individual stylesheets can be removed by adding the module & stylesheet to the array $exclude and calling function cellular_remove_css() in /inc/css_alter .inc <hr/>'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form['c']['style_settings']['r']['remove_drupal_css'] = array(
  '#type' => 'radios',
  '#title' => t('Remove Drupal CSS'),
  '#default_value' => theme_get_setting('remove_drupal_css'),
  '#options' => array(
    0 => t('Leave CSS intact.'),
    'system' => t('Remove all system CSS.'),
    'select' => t('Remove system & module CSS chosen by Cellular.'),
    'theme_only' => t('Remove all system & module CSS- Only use theme CSS.'),
  ),
);

$form['c']['style_settings']['add_classes'] = array(
  '#type' => 'fieldset',
  '#title' => t('Content Class Settings'),
  '#description' => t("Classes to add to #content and #sidebars for simplified layout with a grid."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['c']['style_settings']['add_classes']['content_class_no_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Default Content Class'),
  '#description' => t("Class to add to #content if no sidebars are present."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_no_sidebars'),
);

$form['c']['style_settings']['add_classes']['content_class_single_sidebar'] = array(
  '#type' => 'textfield',
  '#title' => t('Content Class w/ Single Sidebar'),
  '#description' => t("Class to add to #content if one sidebar is displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_single_sidebar'),
);

$form['c']['style_settings']['add_classes']['sidebar_class_single_sidebar'] = array(
  '#type' => 'textfield',
  '#title' => t('Sidebar Class w/ Single Sidebar'),
  '#description' => t("Class to add to #sidebar-left || #sidebar-right if a single sidebar is displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_single_sidebar'),
);

$form['c']['style_settings']['add_classes']['content_class_dual_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Content Class w/ Dual Sidebars'),
  '#description' => t("Class to add to #content if both sidebars are displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_dual_sidebars'),
);

$form['c']['style_settings']['add_classes']['sidebar_class_dual_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Sidebar Class w/ Dual Sidebars'),
  '#description' => t("Class to add to #sidebar-left && #sidebar-right if both sidebars are displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_dual_sidebars'),
);
