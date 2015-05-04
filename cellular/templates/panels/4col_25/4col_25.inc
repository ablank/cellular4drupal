<?php
/**
 * @file
 * Vars & regions for 3 equal columns (33%/33%/33%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('4 Columns @ 25%'),
  'icon' => '4col_25.png',
  'theme' => '4col_25',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'mid_left' => t('Middle Left Column'),
    'mid_right' => t('Middle Right Column'),
    'right' => t('Right Column'),
  ),
);
