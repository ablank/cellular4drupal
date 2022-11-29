<?php

/**
 * @file
 * Vars & regions for 3 equal columns (33%/33%/33%) panel layout.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/templates/panels/_include/';

include_once $inc_path . 'preprocess.inc';

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Columns @ 33%'),
  'icon' => '3col_33.png',
  'theme' => '3col_33',
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
function template_preprocess_3col_33(&$variables) {

  cellular_panels_preprocess_triptych($variables, 33, 33, 33);
}
