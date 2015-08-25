<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Split 30/70'),
  'icon' => 'layout_30_70.png',
  'theme' => 'layout_split_30_70',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left Content'),
    'right' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
