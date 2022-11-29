<?php

/**
 * @file
 * Vars & regions for right inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Inset Right'),
  'icon' => 'inset_right.png',
  'theme' => 'layout_inset_right',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'inset' => t('Inset'),
    'header' => t('Header'),
    'body' => t('Main Content'),
    'footer' => t('Footer'),
  ),
);
