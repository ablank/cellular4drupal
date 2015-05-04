<?php
/**
 * @file
 * Vars & regions for a 2 column (60%/40%) panel layout.
 */
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 60/40'),
  'icon' => '2col_60_40.png',
  'theme' => '2col_60_40',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
