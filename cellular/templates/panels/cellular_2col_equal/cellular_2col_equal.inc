<?php

/**
 * @file
 * Vars & regions for 2 equal column (50%/50%) panel layout.
 */
$plugin = array(
  'category' => t('Cellular'),
  'title' => t('2 Equal Columns'),
  'icon' => 'cellular_2col_equal.png',
  'theme' => 'cellular_2col_equal',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'top' => t('Top Region'),
    'left' => t('Left side'),
    'right' => t('Right side'),
    'bottom' => t('Bottom Region'),
  ),
);
