<?php
/**
 * @file
 * Theme-settings: Javascript options.
 */

// jQuery CDN options.
/*
 * jQuery & jQuery.ui version options are from this array.
 */
$cdn = array(
  'provider' => array(
    'cloudflare' => t('Cloudflare'),
    'google'     => t('Google'),
    'microsoft'  => t('Microsoft'),
  ),
  'jquery'   => array(
    '1.11.1' => t('1.11.1'),
    '1.10.2' => t('1.10.2'),
    '1.9.1'  => t('1.9.1'),
    '1.8.3'  => t('1.8.3'),
    '1.7.2'  => t('1.7.2'),
    '1.6.4'  => t('1.6.4'),
    '1.5.2'  => t('1.5.2'),
    '1.4.4'  => t('1.4.4 : default'),
  ),
  'jqueryui' => array(
    // @ v.1.11 individual widget js isn't availanle :(
    '1.10.4' => t('1.10.4'),
    '1.9.2'  => t('1.9.2'),
    '1.8.24' => t('1.8.24'),
  ),
);

// Available jQuery.ui themes.
$ui_themes = array(
  'custom'         => t('CUSTOM'),
  'base'           => t('base'),
  'black-tie'      => t('black-tie'),
  'blitzer'        => t('blitzer'),
  'cupertino'      => t('cupertino'),
  'dark-hive'      => t('dark-hive'),
  'dot-luv'        => t('dot-luv'),
  'eggplant'       => t('eggplant'),
  'excite-bike'    => t('excite-bike'),
  'flick'          => t('flick'),
  'hot-sneaks'     => t('hot-sneaks'),
  'humanity'       => t('humanity'),
  'le-frog'        => t('le-frog'),
  'mint-choc'      => t('mint-choc'),
  'overcast'       => t('overcast'),
  'pepper-grinder' => t('pepper-grinder'),
  'redmond'        => t('redmond'),
  'smoothness'     => t('smoothness'),
  'south-street'   => t('south-street'),
  'start'          => t('start'),
  'sunny'          => t('sunny'),
  'swanky-purse'   => t('swanky-purse'),
  'trontastic'     => t('trontastic'),
  'ui-darkness'    => t('ui-darkness'),
  'ui-lightness'   => t('ui-lightness'),
  'vader'          => t('vader'),
);

// Start js opts
$form['c']['js'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Javascript'),
  '#description' => is_dir('sites/all/libraries/cellular')
      ? NULL
      :
      t('<div class="messages error"> <h2>These features require the
<a href="@url">Cellular Library</a>.</h2>
</div>', array(
        '@url' => 'https://github.com/ablank/cellular.library'
      )),
  '#collapsible' => TRUE,
  '#collapsed'   => TRUE
);

// Modernizr stuff
$form['c']['js']['mdrnzr'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t('Modernizr'), 'http://modernizr.com/'),
  '#description'   => t("Include Modernizr.js to test  browser capabilities and
  load resources as needed."),
  '#default_value' => theme_get_setting('modernizr'),
);


$form['c']['js']['Modernizr'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Modernizr'),
  '#description' => t("Browser testing & conditional resource loading."),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
  '#states'      => array(
    'visible' => array(
      ':input[name="mdrnzr"]' => array('checked' => TRUE),
    ),
  ),
);

$form['c']['js']['Modernizr']['mq_mobile_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable Mobile Media Query'),
  '#description'   => t("Enable media query to load extra CSS
  (conditional-mobile.css) for mobile devices."),
  '#default_value' => theme_get_setting('mq_mobile_enable'),
  '#states'        => array(
    'visible' => array(
      ':input[name="modernizr"]' => array('checked' => TRUE),
    ),
  ),
);
$form['c']['js']['Modernizr']['mq_mobile'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Mobile Media Query'),
  '#description'   => t("The media query tested by Modernizr load
  extra CSS for mobile devices. This should match the @media setting in
  conditional-mobile.css."),
  '#default_value' => theme_get_setting('mq_mobile'),
  '#states'        => array(
    'visible' => array(
      ':input[name="mq_mobile_enable"]' => array('checked' => TRUE),
    ),
  ),
);

$form['c']['js']['Modernizr']['mq_normal_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable Desktop Media Query'),
  '#description'   => t("Enable media query to test before loading
  conditional-style.css."),
  '#default_value' => theme_get_setting('mq_normale_enable'),
  '#states'        => array(
    'visible' => array(
      ':input[name="modernizr"]' => array('checked' => TRUE),
    ),
  ),
);
$form['c']['js']['Modernizr']['mq_normal'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Normal Media Query'),
  '#description'   => t("The media query tested by Modernizr load style.css."),
  '#default_value' => theme_get_setting('mq_normal'),
  '#states'        => array(
    'visible' => array(
      ':input[name="mq_normal_enable"]' => array('checked' => TRUE),
    ),
  ),
);

$form['c']['js']['Modernizr']['mq_large_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable Conditional Large Media Query'),
  '#description'   => t("Enable media query to load extra CSS
  (conditional-large.css) for large screen devices."),
  '#default_value' => theme_get_setting('mq_large_enable'),
  '#states'        => array(
    'visible' => array(
      ':input[name="modernizr"]' => array('checked' => TRUE),
    ),
  ),
);
$form['c']['js']['Modernizr']['mq_large'] = array(
  '#type'          => 'textfield',
  '#title'         => t('Large Screen Media Query'),
  '#description'   => t("The media query tested by Modernizr load extra CSS for
   large devices. This should match the @media setting in
   conditional-large.css."),
  '#default_value' => theme_get_setting('mq_large'),
  '#states'        => array(
    'visible' => array(
      ':input[name="mq_large_enable"]' => array('checked' => TRUE),
    ),
  ),
);

// Update jQuery?
$form['c']['js']['jquery_update'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Update jQuery & jQuery UI'),
  '#description'   => t("Select the version of jQuery & jQueryUI to use.
  jquery.once and jquery.form will be updated to current version."),
  '#default_value' => theme_get_setting('jquery_update'),
);

// jQuery & jQuery.ui update settings.
$form['c']['js']['update'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('jQuery & jQuery.ui Settings'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
  '#states'      => array(
    'visible' => array(
      ':input[name="jquery_update"]' => array('checked' => TRUE),
    ),
  ),
);

$form['c']['js']['update']['jquery_cdn'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Update jQuery via CDN'),
  '#description'   => t("Update jQuery & jQuery.ui from a selected Content
   Distribution Network host, falling back to local source
    if CDN is unavailable."),
  '#default_value' => theme_get_setting('jquery_cdn'),
);

$form['c']['js']['update']['cdn'] = array(
  '#type'          => 'select',
  '#title'         => t('CDN Provider'),
  '#description'   => t("Select which CDN your site will use."),
  '#options'       => $cdn['provider'],
  '#default_value' => theme_get_setting('cdn'),
  '#states'        => array(
    'visible' => array(
      ':input[name="jquery_cdn"]' => array('checked' => TRUE),
    ),
  ),
);

// jQuery stuff
$form['c']['js']['update']['jquery'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('jQuery'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
);

$form['c']['js']['update']['jquery']['jquery_version'] = array(
  '#type'          => 'select',
  '#title'         => t('jQuery Version'),
  '#description'   => t("Select the version of jQuery your site will use.
  The jQuery.migrate module will be loaded automatically for versions > 1.9"),
  '#options'       => $cdn['jquery'],
  '#default_value' => theme_get_setting('jquery_version'),
);

// jQuery.ui stuff
$form['c']['js']['update']['jqueryui'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('jQuery UI'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
);

$form['c']['js']['update']['jqueryui']['jqueryui_version'] = array(
  '#type'          => 'select',
  '#title'         => t('jQueryUI Version'),
  '#description'   => t("Select the version of jQueryUI your site will use.
  \nYou will need to match a  version compatible with the selected jQuery
  version."),
  '#options'       => $cdn['jqueryui'],
  '#default_value' => theme_get_setting('jqueryui_version'),
);
$form['c']['js']['update']['jqueryui']['jqueryui_theme'] = array(
  '#type'          => 'select',
  '#title'         => t('jQueryUI Theme'),
  '#description'   => t("Select the jQueryUI theme your site will use.
  \nCustom themes can be used by copying the contents (css & /images) of the themeroller
  css directory to \n/sites/all/themes/cellular/css/jquery-ui/%version/custom\n
            The custom CSS file must be re-named as: \n
            jquery-ui.custom.css
            "),
  '#options'       => $ui_themes,
  '#default_value' => theme_get_setting('jqueryui_theme'),
);

// Pre-configured 3rd party plugins.
$form['c']['js']['plugins'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('JS Plugins'),
  '#description' => t("Javascript plugins will load from the Cloudflare CDN,
    or use local source as fallback if CDN is unavailable."),
  '#collapsible' => TRUE,
  '#collapsed'   => TRUE
);
$form['c']['js']['plugins']['cellularjs'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t('Cellular UI'), 'http://abctahoe.net/cellular-ui'),
  '#description'   => t("The Cellular UI library provides common UI elements that work well with Views."),
  '#default_value' => theme_get_setting('cellularjs'),
);
$form['c']['js']['plugins']['d3js'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t("D3JS"), 'http://d3js.org/'),
  '#description'   => t('D3.js is a JavaScript library for manipulating documents based on data. D3 helps you bring data to life using HTML, SVG and CSS.'),
  '#default_value' => theme_get_setting('d3js'),
);
$form['c']['js']['plugins']['gsap'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t('GSAP (GreenSock Animation Platform)'), 'http://www.greensock.com/gsap-js/'),
  '#description'   => t("GSAP is a suite of tools for scripted, high-performance HTML5 animations that work in all major browsers."),
  '#default_value' => theme_get_setting('gsap'),
);
$form['c']['js']['plugins']['masonry'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t("Masonry"), 'http://masonry.desandro.com/'),
  '#description'   => t('Masonry cascading grid layouts'),
  '#default_value' => theme_get_setting('masonry'),
);
$form['c']['js']['plugins']['prism'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t('Prism Syntax Hilighter'), 'http://prismjs.com/'),
  '#description'   => t("Prism code syntax hilighter."),
  '#default_value' => theme_get_setting('prism'),
);
$form['c']['js']['plugins']['smoove'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t("Smoove"), 'http://smoove.donlabs.com/'),
  '#description'   => t('Smoove makes it easy to implement awesome CSS3 transition effects, making your content smoothly glide into the page as your scroll down the page.'),
  '#default_value' => theme_get_setting('smoove'),
);
$form['c']['js']['plugins']['threejs'] = array(
  '#type'          => 'checkbox',
  '#title'         => l(t('THREE.js'), 'http://threejs.org/'),
  '#description'   => t("A JavaScript 3D Library which makes WebGL simpler."),
  '#default_value' => theme_get_setting('threejs'),
);
