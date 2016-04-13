<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Standard'),
  'icon' => 'standard.png',
  'theme' => 'layout_standard',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'body' => t('Main Content'),
    'footer' => t('Footer'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_layout_standard(&$variables) {
  // Add a class to the panel
  //$variables['attributes_array']['class'][] = 'some-class';

  foreach($variables['content'] as $name => $item) {
    $variables['region_attributes'][$name]['class'][] = 'cell';
    $variables['region_attributes'][$name]['class'][] = drupal_clean_css_identifier($name);
  }
}
