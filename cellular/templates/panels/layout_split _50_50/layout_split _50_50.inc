<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Split 50/50'),
  'icon' => 'layout_50_50.png',
  'theme' => 'layout_split_50_50',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left Content'),
    'right' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
