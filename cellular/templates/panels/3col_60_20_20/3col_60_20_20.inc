<?php
/**
 * @file
 * Vars & regions for 3 columns (60%/20%/20%) panel layout.
 */
$inc_path = drupal_get_path('theme', 'cellular') . '/templates/panels/_include/';

include_once $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Columns @ 60/20/20'),
  'icon' => '3col_60_20_20.png',
  'theme' => '3col_60_20_20',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'center' => t('Center Column'),
    'right' => t('Right Column'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_3col_60_20_20(&$variables) {

  cellular_panels_preprocess_triptych($variables, 60, 20, 20);
}
