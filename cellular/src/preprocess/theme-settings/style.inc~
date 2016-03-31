<?php
/**
 * @file
 * Theme-settings: Display & styling settings.
 */
//
$form[0]['style_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Style'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form[0]['style_settings']['inline_critical_css'] = array(
  '#type' => 'checkbox',
  '#title' => t('Inline critical CSS.'),
  '#description' => t('Include styles for elements \'above the fold\' inline in the document head. Edit the grunt/criticalcss configuration and run the <code>grunt criticalcss</code> task from your theme\'s base directory to generate critical css (<em>overwrites existing .css</em>).'),
  '#default_value' => theme_get_setting('inline_critical_css'),
);

$form[0]['style_settings']['remove_drupal_css'] = array(
  '#type' => 'radios',
  '#title' => t('Remove Drupal CSS'),
  '#description' => t('Prevent stylesheet groups from loading. Specific stylesheets can be removed by passing the module & stylesheet as an array to function <code>cellular_remove_css()</code> in /inc/css_alter.inc <hr/>'),
  '#default_value' => theme_get_setting('remove_drupal_css'),
  '#options' => array(
    0 => t('Leave CSS intact.'),
    'select' => t('Remove selected system & module CSS chosen by Cellular.'),
    'system' => t('Remove all system CSS (group => <code>CSS_SYSTEM</code>).'),
    'module' => t('Remove all module CSS. (group => <code>CSS_DEFAULT</code>).'),
    'theme_only' => t('Remove all system & module CSS. Only include theme CSS (group => <code>CSS_THEME</code>).'),
  ),
);

$form[0]['style_settings']['add_classes'] = array(
  '#type' => 'fieldset',
  '#title' => t('Content Class Settings'),
  '#description' => t("Classes to add to #content and #sidebars (<em>when using block manager</em>) for simplified layout with a grid."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['style_settings']['add_classes']['content_class_no_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Default Content Class'),
  '#description' => t("Class to add to #content if no sidebars are present."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_no_sidebars'),
);

$form[0]['style_settings']['add_classes'][0] = array(
  '#type' => 'fieldset',
  '#title' => t('Single Sidebar'),
  '#description' => t("Classes to add to #content and #sidebars for simplified layout with a grid."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['style_settings']['add_classes'][0]['content_class_single_sidebar'] = array(
  '#type' => 'textfield',
  '#title' => t('Content Class'),
  '#description' => t("Class to add to #content if one sidebar is displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_single_sidebar'),
);

$form[0]['style_settings']['add_classes'][0]['sidebar_class_single_sidebar'] = array(
  '#type' => 'textfield',
  '#title' => t('Sidebar Class'),
  '#description' => t("Class to add to #sidebar-left || #sidebar-right if a single sidebar is displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_single_sidebar'),
);

$form[0]['style_settings']['add_classes'][1] = array(
  '#type' => 'fieldset',
  '#title' => t('Dual Sidebars'),
  '#description' => t("Classes to add to #content and #sidebars for simplified layout with a grid."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['style_settings']['add_classes'][1]['content_class_dual_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Content Class'),
  '#description' => t("Class to add to #content if both sidebars are displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('content_class_dual_sidebars'),
);

$form[0]['style_settings']['add_classes'][1]['sidebar_class_dual_sidebars'] = array(
  '#type' => 'textfield',
  '#title' => t('Sidebar Class'),
  '#description' => t("Class added to #sidebar-left AND #sidebar-right if both sidebars are displayed."),
  // '#options' => $grid_values,
  '#default_value' => theme_get_setting('sidebar_class_dual_sidebars'),
);
