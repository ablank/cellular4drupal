<?php

/**
 * @file
 * Vars & regions for 3 column (50%/25%/25%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular'),
  'title' => t('3 Columns @ 50/25/25'),
  'icon' => 'cellular_3col_50_25_25.png',
  'theme' => 'cellular_3col_50_25_25',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left Column'),
    'middle' => t('Middle Column'),
    'right' => t('Right Column'),
    'bottom' => t('Bottom'),
  ),
);
