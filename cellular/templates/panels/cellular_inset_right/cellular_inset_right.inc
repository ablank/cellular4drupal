<?php
/**
 * @file
 * Vars & regions for right inset panel layout.
 */

/**/
$plugin = array(
  'category' => t('Cellular'),
  'title' => t('Cellular Inset Right'),
  'icon' => 'cellular_inset_right.png',
  'theme' => 'cellular_inset_right',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left Column'),
    'middle' => t('Middle Column'),
    'bottom' => t('Bottom'),
    'right' => t('Right Inset'),
  ),
);
