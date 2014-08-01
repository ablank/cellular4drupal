<?php

$form['c']['display_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Style'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
);

$form['c']['display_settings']['full_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Full Menu'),
    '#description' => t('Show the full menu tree in main_menu instead of only top level links.'),
    '#default_value' => theme_get_setting('full_menu'),
);

$form['c']['display_settings']['remove_core_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove Drupal CSS'),
    '#description' => t("Exclude Drupal core module CSS."),
    '#default_value' => theme_get_setting('remove_core_css'),
        //'#options' => $drupal_stylesheets,
);

$form['c']['display_settings']['mq_mobile_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Mobile Media Query'),
    '#description' => t("Enable media query to load extra CSS (conditional-mobile.css) for mobile devices."),
    '#default_value' => theme_get_setting('mq_mobile_enable'),
);
$form['c']['display_settings']['mq_mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile Media Query'),
    '#description' => t("The media query tested by Modernizr load extra CSS for mobile devices. This should match the @media setting in conditional-mobile.css."),
    '#default_value' => theme_get_setting('mq_mobile'),
    '#states' => array(
        'visible' => array(
            ':input[name="mq_mobile_enable"]' => array('checked' => TRUE),
        ),
    ),
);
$form['c']['display_settings']['mq_large_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Mobile Media Query'),
    '#description' => t("Enable media query to load extra CSS (conditional-large.css) for large screen devices."),
    '#default_value' => theme_get_setting('mq_large_enable'),
);
$form['c']['display_settings']['mq_large'] = array(
    '#type' => 'textfield',
    '#title' => t('Large Screen Media Query'),
    '#description' => t("The media query tested by Modernizr load extra CSS for large devices. This should match the @media setting in conditional-large.css."),
    '#default_value' => theme_get_setting('mq_large'),
    '#states' => array(
        'visible' => array(
            ':input[name="mq_large_enable"]' => array('checked' => TRUE),
        ),
    ),
);


$form['c']['display_settings']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Breadcrumbs'),
    '#description' => t("Show breadcrumb navigation on pages other than --front."),
    '#default_value' => theme_get_setting('breadcrumb_display'),
);

$form['c']['display_settings']['breadcrumb_separator'] = array(
    '#type' => 'textfield',
    '#size' => 8,
    '#maxlength' => 10,
    '#title' => t('Breadcrumb separator'),
    '#description' => t('Symbol used to separate breadcrumb links.'),
    '#default_value' => theme_get_setting('breadcrumb_separator'),
    '#states' => array(
        'visible' => array(
            ':input[name="breadcrumb_display"]' => array('checked' => TRUE),
        ),
    ),
);

$form['c']['display_settings']['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Login Block Settings'),
    '#description' => t("Change User Login Block settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
);
$form['c']['display_settings']['login']['login_block_orientation'] = array(
    '#type' => 'select',
    '#title' => t('Login Block Orientation'),
    '#description' => t('This setting adds a class (horizontal || vertical) to the user login block.'),
    '#options' => array(
        'vertical' => t('vertical'),
        'horizontal' => t('horizontal'),
    ),
    '#default_value' => theme_get_setting('login_block_orientation '),
);
$form['c']['display_settings']['login']['login_block_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link to Register New User Account'),
    '#description' => t('Checking this setting shows the link to register a new user account.'),
    '#default_value' => theme_get_setting('login_block_register'),
);

$form['c']['display_settings']['login']['login_block_password'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link to reset password'),
    '#description' => t('Checking this setting shows the link to reset user password.'),
    '#default_value' => theme_get_setting('login_block_password'),
);


$form['c']['display_settings']['add_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Class Settings'),
    '#description' => t("Classes to add to #content and #sidebars for simplified layout with a grid."),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
);
$form['c']['display_settings']['add_classes']['content_class_no_sidebars'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Content Class'),
    '#description' => t("Class to add to #content if no sidebars are present."),
    //'#options' => $grid_values,
    '#default_value' => theme_get_setting('content_class_no_sidebars'),
);
$form['c']['display_settings']['add_classes']['content_class_single_sidebar'] = array(
    '#type' => 'textfield',
    '#title' => t('Content Class w/ Single Sidebar'),
    '#description' => t("Class to add to #content if one sidebar is displayed."),
    //'#options' => $grid_values,
    '#default_value' => theme_get_setting('content_class_single_sidebar'),
);
$form['c']['display_settings']['add_classes']['sidebar_class_single_sidebar'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar Class w/ Single Sidebar'),
    '#description' => t("Class to add to #sidebar-left || #sidebar-right if a single sidebar is displayed."),
    //'#options' => $grid_values,
    '#default_value' => theme_get_setting('sidebar_class_single_sidebar'),
);
$form['c']['display_settings']['add_classes']['content_class_dual_sidebars'] = array(
    '#type' => 'textfield',
    '#title' => t('Content Class w/ Dual Sidebars'),
    '#description' => t("Class to add to #content if both sidebars are displayed."),
    //'#options' => $grid_values,
    '#default_value' => theme_get_setting('content_class_dual_sidebars'),
);
$form['c']['display_settings']['add_classes']['sidebar_class_dual_sidebars'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar Class w/ Dual Sidebars'),
    '#description' => t("Class to add to #sidebar-left && #sidebar-right if both sidebars are displayed."),
    //'#options' => $grid_values,
    '#default_value' => theme_get_setting('sidebar_class_dual_sidebars'),
);
