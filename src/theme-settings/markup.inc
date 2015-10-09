<?php
$form['markup'] = array(
  '#title' => t('Markup'),
  '#type' => 'details',
  //'#tree' => TRUE,
  '#group' => 'cellular',
);

$form['markup']['user'] = array(
  '#title' => t('User'),
  '#type' => 'details',
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
);

$form['markup']['user']['cellular_markup_user_orientlogin'] = array(
  '#type' => 'radios',
  '#title' => t('Orientation'),
  '#description' => t(''),
  '#options' => array(
    0 => 'horizontal',
    1 => 'vertical',
  ),
  '#default_value' => theme_get_setting('cellular_markup_user_orientlogin'),
);

$form['markup']['user']['cellular_markup_userloginlinks'] = array(
  '#type' => 'checkboxes',
  '#title' => t('Login Links'),
  '#description' => t(''),
  '#options' => array(
    0 => 'Register New Account',
    1 => 'Reset Password',
  ),
  '#default_value' => theme_get_setting('cellular_markup_userloginlinks'),
);
