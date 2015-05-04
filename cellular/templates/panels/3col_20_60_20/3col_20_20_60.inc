<?php
/**
 * @file
 * Vars & regions for 3 columns (20%/20%/60%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Columns @ 20/20/60'),
  'icon' => '3col_20_20_60.png',
  'theme' => '3col_20_20_60',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'middle' => t('Middle Column'),
    'right' => t('Right Column'),
  ),
);
