<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Split 70/30'),
  'icon' => 'layout_70_30.png',
  'theme' => 'layout_split_70_30',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left Content'),
    'right' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
