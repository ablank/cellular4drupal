<?php

/**
 * @file
 * Vars & regions for 2 column (30%/70%) panel layout.
 */

$plugin = array(
  'category' => t('Cellular'),
  'title' => t('Cellular Parallax - 5 rows'),
  'icon' => 'cellular_parallax_5row.png',
  'theme' => 'cellular_parallax_5row',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'g1_top' => t('Group 1 Top Layer'),
    'g1_base' => t('Group 1 Bottom Layer'),
    'g2_top' => t('Group 2 Top Layer'),
    'g2_base' => t('Group 2 Bottom Layer'),
    'g3_top' => t('Group 3 Top Layer'),
    'g3_base' => t('Group 3 Bottom Layer'),
    'g4_top' => t('Group 4 Top Layer'),
    'g4_base' => t('Group 4 Bottom Layer'),
    'g5_top' => t('Group 5 Top Layer'),
    'g5_base' => t('Group 5 Bottom Layer'),
  ),
);
