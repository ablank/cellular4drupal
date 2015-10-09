<?php
  $form['javascript'] = array(
    '#title' => t('Javascript'),
    '#type' => 'details',
    //'#tree' => TRUE,
    '#group' => 'cellular',
  );

  $form['javascript']['cdn'] = array(
    '#title' => t('CDN'),
    '#type' => 'details',
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );

  $form['javascript']['cdn']['cellular_javascript_cdn_use'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefer CDN'),
    '#description' => t('Prefer loading javascript using a CDN.'),
    '#default_value' => theme_get_setting('cellular_javascript_cdn_use'),
  );

  $form['javascript']['cdn']['cellular_javascript_cdn_source'] = array(
    '#type' => 'checkbox',
    '#title' => t('CDN Provider'),
    '#description' => t('CDN source.'),
    '#default_value' => theme_get_setting('cellular_javascript_cdn_source'),
  );

  $form['javascript']['jquery'] = array(
    '#type' => 'details',
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#title' => t('jQuery'),
  );

  $form['javascript']['jquery']['cellular_javascript_jquery_version'] = array(
    '#type' => 'select',
    '#title' => t('jQuery Version'),
    '#description' => t(''),
    '#options' => array(
      '1.11' => '1.11',
      '2.14' => '2.14',
    ),
    '#default_value' => theme_get_setting('cellular_javascript_jquery_version'),
  );

  $form['javascript']['jquery']['cellular_javascript_jqueryui_version'] = array(
    '#type' => 'select',
    '#title' => t('jQuery UI Version'),
    '#description' => t(''),
    '#options' => array(),
    '#default_value' => theme_get_setting('cellular_javascript_jqueryui_version'),
  );

  $form['javascript']['jquery']['cellular_javascript_jqueryui_theme'] = array(
    '#type' => 'select',
    '#title' => t('jQuery UI Theme'),
    '#description' => t(''),
    '#options' => array(),
    '#default_value' => theme_get_setting('cellular_javascript_jqueryui_theme'),
  );

  $form['javascript']['plugins'] = array(
    '#type' => 'details',
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#title' => t('Javascript plugins'),
  );

  $form['javascript']['plugins']['cellular_javascript_cellularui'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cellular UI'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_cellularui'),
  );

  $form['javascript']['plugins']['cellular_javascript_backstretch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Backstretch'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_backstretch'),
  );

  $form['javascript']['plugins']['cellular_javascript_flowtype'] = array(
    '#type' => 'checkbox',
    '#title' => t('Flowtype'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_flowtype'),
  );

  $form['javascript']['plugins']['cellular_javascript_freetile'] = array(
    '#type' => 'checkbox',
    '#title' => t('Freetile'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_freetile'),
  );

  $form['javascript']['plugins']['cellular_javascript_parallax'] = array(
    '#type' => 'checkbox',
    '#title' => t('Parallax'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_parallax'),
  );


  $form['javascript']['libs'] = array(
    '#type' => 'details',
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#title' => t('Javascript Libraries'),
  );

  $form['javascript']['libs']['cellular_javascript_modernizr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Modernizr'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_modernizr'),
  );

  $form['javascript']['libs']['cellular_javascript_d3'] = array(
    '#type' => 'checkbox',
    '#title' => t('D3'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_d3'),
  );

  $form['javascript']['libs']['cellular_javascript_gsap'] = array(
    '#type' => 'checkbox',
    '#title' => t('GSAP (GreenSock Animation Platform'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_gsap'),
  );

  $form['javascript']['libs']['cellular_javascript_prism'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prism'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_prism'),
  );

  $form['javascript']['libs']['cellular_javascript_snapsvg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Snap SVG'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_snapsvg'),
  );

  $form['javascript']['libs']['cellular_javascript_three'] = array(
    '#type' => 'checkbox',
    '#title' => t('THREE'),
    '#description' => t(''),
    '#default_value' => theme_get_setting('cellular_javascript_three'),
  );
