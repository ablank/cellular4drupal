<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category'        => t('Cellular'),
  'title'           => t('Inset Left'),
  'icon'            => 'cellular_inset_left.png',
  'theme'           => 'cellular_inset_left',
  'theme arguments' => array('id', 'content'),
  'admin css'       => 'admin.css',
  'regions'         => array(
    'top'    => t('Top'),
    'left'   => t('Left Inset'),
    'middle' => t('Middle Column'),
    'right'  => t('Right Column'),
    'bottom' => t('Bottom'),
  ),
);
