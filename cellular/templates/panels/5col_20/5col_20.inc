<?php
/**
 * @file
 * Vars & regions for 5 equal columns (20%) panel layout.
 */
/**/
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('5 Columns @ 20%'),
  'icon' => '5col_20.png',
  'theme' => '5col_20',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'mid_left' => t('Middle Left Column'),
    'middle' => t('Middle Column'),
    'mid_right' => t('Middle Right Column'),
    'right' => t('Right Column'),
  ),
);
