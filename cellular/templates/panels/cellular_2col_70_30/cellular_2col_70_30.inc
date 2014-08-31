<?php

/**
 * @file
 * Vars & regions for 2 column (70%/30%) panel layout.
 */
$plugin = array(
  'category'        => t('Cellular'),
  'title'           => t('2 Columns @ 70/30'),
  'icon'            => 'cellular_2col_70_30.png',
  'theme'           => 'cellular_2col_70_30',
  'theme arguments' => array('id', 'content'),
  'admin css'       => 'admin.css',
  'regions'         => array(
    'top'    => t('Top'),
    'left'   => t('Left'),
    'right'  => t('Right'),
    'bottom' => t('Bottom'),
  ),
);
