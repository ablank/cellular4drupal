<?php
/**
 * @file
 * Vars & regions for a 2 column (30%/70%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 30/70'),
  'icon' => '2col_30_70.png',
  'theme' => '2col_30_70',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
