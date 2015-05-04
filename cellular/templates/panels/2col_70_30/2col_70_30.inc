<?php
/**
 * @file
 * Vars & regions for a 2 column (70%/30%) panel layout.
 */
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 70/30'),
  'icon' => '2col_70_30.png',
  'theme' => '2col_70_30',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
