<?php
/**
 * @file
 * Vars & regions for a 2 column (20%/80%) panel layout.
 */

$inc_path = drupal_get_path('theme', 'cellular') .'/templates/panels/_include/';

include_once  $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 20/80'),
  'icon' => '2col_20_80.png',
  'theme' => '2col_20_80',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_2col_20_80(&$variables) {

  cellular_panels_preprocess_split($variables, 20, 80);
}
