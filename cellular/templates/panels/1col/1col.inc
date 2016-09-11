<?php
/**
 * @file
 * Vars & regions for single column panel layout.
 */
$plugin = array(
  'category' => t('Cellular | Prototype'),
  'title' => t('1 Column'),
  'icon' => '1col.png',
  'theme' => '1col',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'body' => t('Content'),
  ),
);
