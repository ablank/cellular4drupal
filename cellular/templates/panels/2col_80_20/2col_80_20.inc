<?php
/**
 * @file
 * Vars & regions for a 2 column (80%/20%) panel layout.
 */
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 80/20'),
  'icon' => '2col_80_20.png',
  'theme' => '2col_80_20',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
