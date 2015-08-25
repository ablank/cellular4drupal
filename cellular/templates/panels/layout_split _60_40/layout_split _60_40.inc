<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Split 60/40'),
  'icon' => 'layout_60_40.png',
  'theme' => 'layout_split_60_40',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'left' => t('Left Content'),
    'right' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
