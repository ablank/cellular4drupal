<?php

/**
 * @file
 * Vars & regions for 2 column (30%/70%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular'),
  'title' => t('Cellular - 5 rows'),
  'icon' => 'cellular_5row.png',
  'theme' => 'cellular_5row',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'row1' => t('Row 1'),
    'row2' => t('Row 2'),
    'row3' => t('Row 3'),
    'row4' => t('Row 4'),
    'row5' => t('Row 5'),
  ),
);
