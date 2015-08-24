<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Standard'),
  'icon' => 'standard.png',
  'theme' => 'layout_standard',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'body' => t('Main Content'),
    'footer' => t('Footer'),
  ),
);
