<?php
/**
 * @file
 * Vars & regions for left inset panel layout.
 */

$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Stacked'),
  'icon' => 'layout_stacked.png',
  'theme' => 'layout_stacked',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => array(
    'header' => t('Header'),
    'cell_0' => t('Cell'),
    'cell_50_left_0' => t('Split Left Content'),
    'cell_50_right_0' => t('Split Right Content'),
    'cell_33_left_0' => t('Triptych Left Content'),
    'cell_33_center_0' => t('Triptych Center Content'),
    'cell_33_right_0' => t('Triptych Right Content'),
    'cell_1' => t('Cell'),
    'cell_50_left_1' => t('Split Left Content'),
    'cell_50_right_1' => t('Split Right Content'),
    'cell_33_left_1' => t('Triptych Left Content'),
    'cell_33_center_1' => t('Triptych Center Content'),
    'cell_33_right_1' => t('Triptych Right Content'),
    'cell_2' => t('Cell'),
    'cell_50_left_2' => t('Split Left Content'),
    'cell_50_right_2' => t('Split Right Content'),
    'cell_33_left_2' => t('Triptych Left Content'),
    'cell_33_center_2' => t('Triptych Center Content'),
    'cell_33_right_2' => t('Triptych Right Content'),
    'footer' => t('Footer'),
  ),
);
