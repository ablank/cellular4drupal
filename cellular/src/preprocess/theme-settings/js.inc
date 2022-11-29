<?php

/**
 * @file
 * Theme-settings: Javascript options.
 */

// Start js opts.
$form[0]['js'] = array(
  '#type' => 'fieldset',
  '#title' => t('Javascript'),
  '#description' => is_dir('sites/all/libraries/cellular') ? NULL :
  t('<div class="messages error"> <h2>These features require the <a href="@url">Cellular Library</a>.</h2> </div>', array('@url' => 'https://github.com/ablank/cellular.library')),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

// Update jQuery?
$form[0]['js']['jquery_update'] = array(
  '#type' => 'checkbox',
  '#title' => t('Update jQuery & jQuery UI'),
  '#description' => t("Update jQuery, jQueryUI, and Drupal's default jQuery plugins (minified current versions)."),
  '#default_value' => theme_get_setting('jquery_update'),
);

// jQuery & jQuery.ui update settings.
$form[0]['js']['update'] = array(
  '#type' => 'fieldset',
  '#title' => t('jQuery & jQuery.ui Settings'),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  '#states' => array(
    'visible' => array(
      ':input[name="jquery_update"]' => array('checked' => TRUE),
    ),
  ),
);

$form[0]['js']['update']['jquery_cdn'] = array(
  '#type' => 'checkbox',
  '#title' => t('Update via CDN'),
  '#description' => t("Update jQuery & jQuery.ui from a selected Content Distribution Network host, falling back to local javascript sources if CDN is unavailable."),
  '#default_value' => theme_get_setting('jquery_cdn'),
);

$form[0]['js']['update']['jquery_cdn_source'] = array(
  '#type' => 'select',
  '#title' => t('CDN Provider'),
  '#description' => t("Select which CDN your site will use."),
  '#options' => $cdn['provider'],
  '#default_value' => theme_get_setting('jquery_cdn_source'),
  '#states' => array(
    'visible' => array(
      ':input[name="jquery_cdn"]' => array('checked' => TRUE),
    ),
  ),
);

// jQuery stuff.
$form[0]['js']['update']['jquery'] = array(
  '#type' => 'fieldset',
  '#title' => t('jQuery'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form[0]['js']['update']['jquery']['jquery_version'] = array(
  '#type' => 'select',
  '#title' => t('jQuery Version'),
  '#description' => t("Select the version of jQuery your site will use."),
  '#options' => $cdn['jquery'],
  '#default_value' => theme_get_setting('jquery_version'),
);

$form[0]['js']['update']['jquery']['jquery_migrate'] = array(
  '#type' => 'checkbox',
  '#title' => t('jQuery Migrate'),
  '#description' => t("Include jQuery.migrate for versions > 1.9 to prevent deprecated functions from breaking."),
  '#default_value' => theme_get_setting('jquery_migrate'),
 /*
  '#states' => array(
  'visible' => array(
  ':input[name="jquery_version"]' => array('selected' => floatval(substr( $somevarforjquery['version'], 2)) >= 9 ),
  ),
  ),
 */
);

// jQuery.ui stuff.
$form[0]['js']['update']['jqueryui'] = array(
  '#type' => 'fieldset',
  '#title' => 'jQuery UI',
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form[0]['js']['update']['jqueryui']['jqueryui_version'] = array(
  '#type' => 'select',
  '#title' => t('jQueryUI Version'),
  '#description' => t("Select the version of jQueryUI your site will use.\nYou will need to match a  version compatible with the selected jQuery version."),
  '#options' => $cdn['jqueryui'],
  '#default_value' => theme_get_setting('jqueryui_version'),
);
$form[0]['js']['update']['jqueryui']['jqueryui_theme'] = array(
  '#type' => 'select',
  '#title' => t('jQueryUI Theme'),
  '#description' => t("Select the jQueryUI theme your site will use. \nCustom themes can be used by copying the contents (css & /images) of the themeroller css directory to \n/sites/all/themes/cellular/css/jquery-ui/%version/custom \nThe custom CSS file must be re-named as: \njquery-ui.custom.css"),
  '#options' => $ui_themes,
  '#default_value' => theme_get_setting('jqueryui_theme'),
);

// Pre-configured 3rd party plugins.
$form[0]['js']['plugins'] = array(
  '#type' => 'fieldset',
  '#title' => t('jQuery Plugins'),
  '#description' => t("jQuery plugins are called from <code>/js/plugins.js</code> using simple configurations that you may update to meet your needs- see each plugin's documentation page for all available options. <br/>The required plugin files will load from CDNJS if possible, or use the local Cellular library to provide a fallback file if the CDN source is unavailable."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['js']['plugins']['backstretch'] = array(
  '#type' => 'checkbox',
  '#title' => l('Backstretch', 'http://srobbin.com/jquery-plugins/backstretch/'),
  '#description' => t("A simple jQuery plugin that allows you to add a dynamically resized, slideshow-capable background image to any page or element."),
  '#default_value' => theme_get_setting('backstretch'),
);

$form[0]['js']['plugins']['cellularui'] = array(
  '#type' => 'checkbox',
  '#title' => l('Cellular UI', 'http://live-cellular.gotpantheon.com/cellular-ui'),
  '#description' => t("The Cellular UI library provides common UI elements that work well with Views."),
  '#default_value' => theme_get_setting('cellularui'),
);

$form[0]['js']['plugins']['flowtype'] = array(
  '#type' => 'checkbox',
  '#title' => l('Flowtype', 'http://simplefocus.com/flowtype/'),
  '#description' => t('Responsive font-size based on element width.'),
  '#default_value' => theme_get_setting('flowtype'),
);

$form[0]['js']['plugins']['freetile'] = array(
  '#type' => 'checkbox',
  '#title' => l('Freetile', 'http://yconst.com/web/freetile/'),
  '#description' => t('Freetile is a plugin for jQuery that enables the organization of webpage content in an efficient, dynamic and responsive layout.'),
  '#default_value' => theme_get_setting('freetile'),
);

$form[0]['js']['plugins']['jparallax'] = array(
  '#type' => 'checkbox',
  '#title' => l("jParallax", 'http://stephband.info/jparallax/'),
  '#description' => t('jParallax turns nodes into absolutely positioned layers that move in response to the mouse. Depending on their dimensions these layers move at different rates, in a parallaxy kind of way.'),
  '#default_value' => theme_get_setting('jparallax'),
);

$form[0]['js']['plugins']['smoove'] = array(
  '#type' => 'checkbox',
  '#title' => l('Smoove', 'http://smoove.donlabs.com/'),
  '#description' => t('Smoove makes it easy to implement awesome CSS3 transition effects, making your content smoothly glide into the page as your scroll down the page.'),
  '#default_value' => theme_get_setting('smoove'),
);

$form[0]['js']['plugins']['nprogress'] = array(
  '#type' => 'checkbox',
  '#title' => l('NProgress', 'http://ricostacruz.com/nprogress/'),
  '#description' => t('Slim progress bars for Ajaxy applications. Inspired by Google, YouTube, and Medium.'),
  '#default_value' => theme_get_setting('nprogress'),
);

// Pre-configured 3rd party plugins.
$form[0]['js']['lib'] = array(
  '#type' => 'fieldset',
  '#title' => t('Javascript Libraries'),
  '#description' => t("Javascript libraries load the library specified and nothing more- you may add your script to call library functions in <code>/js/script.js</code>, or add a separate js file in <code>/preprocess/alter_js.inc</code> and re-compile with grunt. <br/>The required library files will load from CDNJS if possible, or use the local Cellular library to provide a fallback file if the CDN source is unavailable."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['js']['lib']['d3js'] = array(
  '#type' => 'checkbox',
  '#title' => l('D3JS', 'http://d3js.org/'),
  '#description' => t('D3.js is a JavaScript library for manipulating documents based on data. D3 helps you bring data to life using HTML, SVG and CSS.'),
  '#default_value' => theme_get_setting('d3js'),
);
$form[0]['js']['lib']['gsap'] = array(
  '#type' => 'checkbox',
  '#title' => l(t('GSAP (GreenSock Animation Platform)'), 'http://www.greensock.com/gsap-js/'),
  '#description' => t("GSAP is a suite of tools for scripted, high-performance HTML5 animations that work in all major browsers."),
  '#default_value' => theme_get_setting('gsap'),
);

$form[0]['js']['lib']['prism'] = array(
  '#type' => 'checkbox',
  '#title' => l(t('Prism Syntax Hilighter'), 'http://prismjs.com/'),
  '#description' => t("Prism code syntax hilighter."),
  '#default_value' => theme_get_setting('prism'),
);

$form[0]['js']['lib']['snap-svg'] = array(
  '#type' => 'checkbox',
  '#title' => l('Snap.SVG', 'http://snapsvg.io/'),
  '#description' => t('The Snap.svg JavaScript library makes working with your SVG assets as easy as jQuery makes working with the DOM.'),
  '#default_value' => theme_get_setting('snap-svg'),
);

$form[0]['js']['lib']['threejs'] = array(
  '#type' => 'checkbox',
  '#title' => l('THREE.js', 'http://threejs.org/'),
  '#description' => t("A JavaScript 3D Library which makes WebGL simpler."),
  '#default_value' => theme_get_setting('threejs'),
);
