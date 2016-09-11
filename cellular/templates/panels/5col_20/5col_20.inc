<?php
/**
 * @file
 * Vars & regions for 5 equal columns (20%) panel layout.
 */
$inc_path = drupal_get_path('theme', 'cellular') . '/templates/panels/_include/';

include_once $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('5 Columns @ 20%'),
  'icon' => '5col_20.png',
  'theme' => '5col_20',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'midleft' => t('Middle Left Column'),
    'center' => t('Center Column'),
    'midright' => t('Middle Right Column'),
    'right' => t('Right Column'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_5col_20(&$variables) {

  cellular_panels_preprocess_quintet($variables, 20, 20, 20, 20, 20);
}
