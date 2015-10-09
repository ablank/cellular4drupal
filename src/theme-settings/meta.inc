<?php
$form['meta'] = array(
  '#title' => t('Meta'),
  '#type' => 'details',
  //'#tree' => TRUE,
  '#group' => 'cellular',
);

$form['meta']['favicon'] = array(
  '#title' => t('Favicon'),
  '#type' => 'details',
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
);

$form['meta']['favicon']['cellular_meta_favicon'] = array(
  '#title' => t('Favicon'),
  '#type' => 'textfield',
  '#description' => t('Default <code>favicon.ico</code>, 16x16px'),
  '#default_value' => theme_get_setting('cellular_meta_favicon'),
);

$form['meta']['favicon']['cellular_meta_favicon32'] = array(
  '#title' => t('Large Favicon'),
  '#type' => 'textfield',
  '#description' => t('Large <code>favicon.png</code>, 32x32px'),
  '#default_value' => theme_get_setting('cellular_meta_favicon32'),
);

$form['meta']['touchicon'] = array(
  '#title' => t('Touch Icon'),
  '#type' => 'details',
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
);

$form['meta']['touchicon']['cellular_meta_touchicon'] = array(
  '#title' => t('57px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('Default <code>apple-touch-icon</code>, 57x57px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon'),
);

$form['meta']['touchicon']['cellular_meta_touchicon60'] = array(
  '#title' => t('60px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('<code>apple-touch-icon</code>, 60x60px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon60'),
);

$form['meta']['touchicon']['cellular_meta_touchicon76'] = array(
  '#title' => t('76px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('<code>apple-touch-icon</code>, 76x76px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon76'),
);

$form['meta']['touchicon']['cellular_meta_touchicon120'] = array(
  '#title' => t('120px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('<code>apple-touch-icon</code>, 120x120px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon120'),
);

$form['meta']['touchicon']['cellular_meta_touchicon152'] = array(
  '#title' => t('152px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('<code>apple-touch-icon</code>, 152x152px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon152'),
);

$form['meta']['touchicon']['cellular_meta_touchicon180'] = array(
  '#title' => t('180px Touch Icon'),
  '#type' => 'textfield',
  '#description' => t('<code>apple-touch-icon</code>, 180x180px'),
  '#default_value' => theme_get_setting('cellular_meta_touchicon180'),
);
