<?php
/**
 * @file
 * Vars & regions for a parallax layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Parallax'),
  'icon' => 'parallax.png',
  'theme' => 'layout_parallax',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'g1_top' => t('Top Layer'),
    'g1_base' => t('Bottom Layer'),
    'g2_top' => t('Top Layer'),
    'g2_base' => t('Bottom Layer'),
    'g3_top' => t('Top Layer'),
    'g3_base' => t('Bottom Layer'),
    'g4_top' => t('Top Layer'),
    'g4_base' => t('Bottom Layer'),
    'g5_top' => t('Top Layer'),
    'g5_base' => t('Bottom Layer'),
    'footer' => t('Footer'),
  ),
);
