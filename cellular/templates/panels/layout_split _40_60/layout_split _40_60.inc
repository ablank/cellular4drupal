<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Split 40/60'),
  'icon' => 'layout_40_60.png',
  'theme' => 'layout_split_40_60',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left Content'),
    'right' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
