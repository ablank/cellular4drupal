<?php
/**
 * @file
 * Vars & regions for 3 equal columns (33%/33%/33%) panel layout.
 */
$inc_path = drupal_get_path('theme', 'cellular') . '/templates/panels/_include/';

include_once $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('4 Columns @ 25%'),
  'icon' => '4col_25.png',
  'theme' => '4col_25',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'midleft' => t('Middle Left Column'),
    'midright' => t('Middle Right Column'),
    'right' => t('Right Column'),
  ),
);

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_4col_25(&$variables) {

  cellular_panels_preprocess_quarters($variables, 25, 25, 25, 25);
}
