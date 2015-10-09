<?php
$form['style'] = array(
  '#title' => t('Style'),
  '#type' => 'details',
  //'#tree' => TRUE,
  '#group' => 'cellular',
);

$form['style']['remove'] = array(
  '#title' => t('Remove CSS'),
  '#type' => 'details',
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
);

$form['style']['remove']['cellular_style_remove'] = array(
  '#type' => 'radios',
  '#title' => t('Remove CSS'),
  '#description' => t(''),
  '#options' => array(
    0 => 'none',
    4 => 'selected',
    1 => 'core',
    2 => 'module',
    3 => 'core + module',
  ),
  '#default_value' => theme_get_setting('cellular_style_remove'),
);
