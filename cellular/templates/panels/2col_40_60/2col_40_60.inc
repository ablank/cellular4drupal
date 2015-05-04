<?php
/**
 * @file
 * Vars & regions for a 2 column (40%/60%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 40/60'),
  'icon' => '2col_40_60.png',
  'theme' => '2col_40_60',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
