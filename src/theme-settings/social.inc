<?php
$form['social'] = array(
  '#title' => t('Social'),
  '#type' => 'details',
  //'#tree' => TRUE,
  '#group' => 'cellular',
);

$form['social']['share'] = array(
  '#title' => t('Share on Social Media'),
  '#type' => 'details',
  '#collapsed' => TRUE,
  '#collapsible' => TRUE,
);

$form['social']['share']['cellular_social_share_enable'] = array(
  '#type' => 'checkbox',
  '#title' => t('Enable social media sharing links.'),
  '#default_value' => theme_get_setting('cellular_social_share_enable'),
);

$form['social']['share']['shared'] = array(
  '#type' => 'details',
  '#title' => t('Social share settings'),
  '#states' => array(
    'invisible' => array(
      '[name="cellular_social_share_enable"]' => array('checked' => FALSE),
    ),
  ),
);


$form['social']['share']['shared']['cellular_social_share_title'] = array(
  '#type' => 'textfield',
  '#title' => t('Social media share title.'),
  '#default_value' => theme_get_setting('cellular_social_share_title'),
);

$form['social']['share']['shared']['cellular_social_share_facebook'] = array(
  '#type' => 'checkbox',
  '#title' => t('Share on facebook.'),
  '#default_value' => theme_get_setting('cellular_social_share_facebook'),
);
