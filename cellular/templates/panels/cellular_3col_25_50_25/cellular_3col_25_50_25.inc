<?php

/**
 * @file
 * Vars & regions for 3 column (25%/50%/25%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular'),
  'title' => t('3 Columns @ 25/50/25'),
  'icon' => 'cellular_3col_25_50_25.png',
  'theme' => 'cellular_3col_25_50_25',
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
