<?php

$cdn = array(
    'provider' => array(
        'google' => t('Google'),
        'microsoft' => t('Microsoft'),
    ),
    'jquery' => array(
        '1.8.2' => t('1.8.2'),
        '1.7.1' => t('1.7.1'),
        '1.5.1' => t('1.5.1'),
        '1.4.4' => t('1.4.4 : default'),
    ),
    'jqueryui' => array(
        '1.10.1' => t('1.10.1'),
        '1.9.2' => t('1.9.2'),
        '1.8.11' => t('1.8.11'),
        '1.8.7' => t('1.8.7 : default'),
    ),
);

$ui_themes = array(
    'custom' => t('CUSTOM'),
    'base' => t('base'),
    'black-tie' => t('black-tie'),
    'blitzer' => t('blitzer'),
    'cupertino' => t('cupertino'),
    'dark-hive' => t('dark-hive'),
    'dot-luv' => t('dot-luv'),
    'eggplant' => t('eggplant'),
    'excite-bike' => t('excite-bike'),
    'flick' => t('flick'),
    'hot-sneaks' => t('hot-sneaks'),
    'humanity' => t('humanity'),
    'le-frog' => t('le-frog'),
    'mint-choc' => t('mint-choc'),
    'overcast' => t('overcast'),
    'pepper-grinder' => t('pepper-grinder'),
    'redmond' => t('redmond'),
    'smoothness' => t('smoothness'),
    'south-street' => t('south-street'),
    'start' => t('start'),
    'sunny' => t('sunny'),
    'swanky-purse' => t('swanky-purse'),
    'trontastic' => t('trontastic'),
    'ui-darkness' => t('ui-darkness'),
    'ui-lightness' => t('ui-lightness'),
    'vader' => t('vader'),
);

$form['c']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('Javascript'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
);

$form['c']['js']['jquery_update'] = array(
    '#type' => 'checkbox',
    '#title' => t('Update jQuery'),
    '#description' => t("Update jQuery & jQueryUI to newer version, loading first from CDN with a local fallback source if the CDN script is unavailable."),
    '#default_value' => theme_get_setting('jquery_update'),
);

$form['c']['js']['jquery'] = array(
    '#type' => 'fieldset',
    '#title' => t('jQuery'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
        'visible' => array(
            ':input[name="jquery_update"]' => array('checked' => TRUE),
        ),
    ),
);

$form['c']['js']['jquery']['cdn'] = array(
    '#type' => 'select',
    '#title' => t('CDN Provider'),
    '#description' => t("Select which CDN your site will use."),
    '#options' => $cdn['provider'],
    '#default_value' => theme_get_setting('cdn'),
);
$form['c']['js']['jquery']['jquery_version'] = array(
    '#type' => 'select',
    '#title' => t('jQuery Version'),
    '#description' => t("Select the version of jQuery your site will use."),
    '#options' => $cdn['jquery'],
    '#default_value' => theme_get_setting('jquery_version'),
);


$form['c']['js']['jqueryui'] = array(
    '#type' => 'fieldset',
    '#title' => t('jQuery UI'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
        'visible' => array(
            ':input[name="jquery_update"]' => array('checked' => TRUE),
        ),
    ),
);
$form['c']['js']['jqueryui']['jqueryui_version'] = array(
    '#type' => 'select',
    '#title' => t('jQueryUI Version'),
    '#description' => t("Select the version of jQueryUI your site will use. \nYou will need to match a  version compatible with the selected jQuery version."),
    '#options' => $cdn['jqueryui'],
    '#default_value' => theme_get_setting('jqueryui_version'),
);
$form['c']['js']['jqueryui']['jqueryui_theme'] = array(
    '#type' => 'select',
    '#title' => t('jQueryUI Theme'),
    '#description' => t("Select the jQueryUI theme your site will use.  \nCustom themes can be used by copying the contents (css & /images) of the themeroller css directory to \n/sites/all/themes/cellular/css/jquery-ui/%version/custom\n
            The custom CSS file must be re-named as: \n
            jquery-ui.custom.css
            "),
    '#options' => $ui_themes,
    '#default_value' => theme_get_setting('jqueryui_theme'),
);


$form['c']['js']['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Plugins'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE
);
$form['c']['js']['plugins']['modernizr'] = array(
    '#type' => 'checkbox',
    '#title' => l(t('Modernizr'), 'http://modernizr.com/'),
    '#description' => t("Include Modernizr to test HTML5 & CSS3 support."),
    '#default_value' => theme_get_setting('modernizr'),
);
$form['c']['js']['plugins']['gsap'] = array(
    '#type' => 'checkbox',
    '#title' => l(t('GSAP (GreenSock Animation Platform)'), 'http://www.greensock.com/gsap-js/'),
    '#description' => t("Include GreenSock Animation Platform."),
    '#default_value' => theme_get_setting('gsap'),
);
$form['c']['js']['plugins']['d3js'] = array(
    '#type' => 'checkbox',
    '#title' => l(t("D3JS"), 'http://d3js.org/'),
    '#description' => t('Include D3JS for visualization.'),
    '#default_value' => theme_get_setting('d3js'),
);
$form['c']['js']['plugins']['threejs'] = array(
    '#type' => 'checkbox',
    '#title' => l(t('THREE.js'), 'http://threejs.org/'),
    '#description' => t("Include THREE.js for visualization."),
    '#default_value' => theme_get_setting('threejs'),
);
$form['c']['js']['plugins']['prism'] = array(
    '#type' => 'checkbox',
    '#title' => l(t('Prism Syntax Hilighter'), 'http://prismjs.com/'),
    '#description' => t("Include Prism code syntax hilighter."),
    '#default_value' => theme_get_setting('prism'),
);
$form['c']['js']['plugins']['cellularjs'] = array(
    '#type' => 'checkbox',
    '#title' => l(t('Cellular UI'), 'http://abctahoe.net/cellular-ui'),
    '#description' => t("Include Cellular UI library."),
    '#default_value' => theme_get_setting('cellularjs'),
);
$form['c']['js']['plugins']['masonry'] = array(
    '#type' => 'checkbox',
    '#title' => l(t("Masonry"), 'http://masonry.desandro.com/'),
    '#description' => t('Include the Masonry cascading grid layout library'),
    '#default_value' => theme_get_setting('masonry'),
);
