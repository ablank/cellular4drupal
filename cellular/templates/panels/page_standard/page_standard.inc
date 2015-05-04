<?php
/**
 * @file
 * Vars & regions for 2 column (30%/70%) panel layout.
 */
$plugin = array(
  'category' => t('Cellular | Pages'),
  'title' => t('Standard Page'),
  'icon' => 'standard.png',
  'theme' => 'page_standard',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'body' => t('Main Content'),
    'footer' => t('Footer'),
  ),
);
