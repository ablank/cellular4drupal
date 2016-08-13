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
