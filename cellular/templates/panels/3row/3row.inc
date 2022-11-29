<?php

/**
 * @file
 * Vars & regions for 3 equal columns (33%/33%/33%) panel layout.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/templates/panels/_include/';

include_once $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Rows'),
  'icon' => '3row.png',
  'theme' => 'cellular_3row',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'top' => t('Top Row'),
    'middle' => t('Middle Row'),
    'bottom' => t('Bottom Row'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_cellular_3row(&$variables) {

  foreach ($variables['content'] as $name => $item) {
    $variables['region_attributes'][$name]['class'][] = 'cell';
  }
}
