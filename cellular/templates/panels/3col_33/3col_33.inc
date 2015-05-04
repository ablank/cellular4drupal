<?php
/**
 * @file
 * Vars & regions for 3 equal columns (33%/33%/33%) panel layout.
 */
/**/
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('3 Columns @ 33%'),
  'icon' => '3col_33.png',
  'theme' => '3col_33',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'left' => t('Left Column'),
    'middle' => t('Middle Column'),
    'right' => t('Right Column'),
  ),
);
