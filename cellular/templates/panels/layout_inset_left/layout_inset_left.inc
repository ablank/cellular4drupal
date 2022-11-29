<?php

/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Inset Left'),
  'icon' => 'inset_left.png',
  'theme' => 'layout_inset_left',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'inset' => t('Inset'),
    'header' => t('Header'),
    'body' => t('Main Content'),
    'footer' => t('Footer'),
  ),
);
