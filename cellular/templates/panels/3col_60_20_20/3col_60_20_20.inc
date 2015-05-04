<?php
/**
 * @file
 * Vars & regions for 3 equal columns (60%/20%/20%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Columns @ 60/20/20'),
  'icon' => '3col_60_20_20.png',
  'theme' => '3col_60_20_20',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'middle' => t('Middle Column'),
    'right' => t('Right Column'),
  ),
);
