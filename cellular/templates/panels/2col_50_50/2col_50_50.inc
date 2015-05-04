<?php
/**
 * @file
 * Vars & regions for 2 equal column (50%/50%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('2 Columns @ 50/50'),
  'icon' => '2col_50_50.png',
  'theme' => '2col_50_50',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'right' => t('Right Column'),
  ),
);
