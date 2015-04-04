<?php
/**
 * @file
 * 
 * Cellular Theme Settings
 */
/*
* @see file: src/preprocess/theme-settings/_init_theme-settings.inc
* Cellular theme-settings.
*/
/**
* Cellular hook_form_system_theme_settings_alter().
*/
function cellular_form_system_theme_settings_alter(&$form, $form_state) {
// Define form to hold pages as tabs.
$form['c'] = array(
'#type' => 'vertical_tabs',
'#description' => t('Layout'),
'#weight' => -10,
'#attached' => array(),
);
/*
* @see file: src/preprocess/theme-settings/meta.inc
* Theme-settings: Set copyright & favicons.
*/
$form['c']['meta'] = array(
'#type' => 'fieldset',
'#title' => t('Meta'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['meta']['dev'] = array(
'#type' => 'checkbox',
'#title' => t('Development Mode'),
'#description' => t("Load unminified css & js assets from <code>/buildtest/</code> and return page variables in  \$messages."),
'#default_value' => theme_get_setting('dev'),
);
$form['c']['meta']['favicons'] = array(
'#type' => 'fieldset',
'#title' => t('Favicons'),
'#description' => t("Favicons are used by browsers to provide a graphic identity for your site."),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
$form['c']['meta']['favicons']['favicon'] = array(
'#type' => 'textfield',
'#title' => t('Favicon'),
'#description' => t("Default favicon.ico file"),
'#default_value' => theme_get_setting('favicon'),
);
$form['c']['meta']['favicons']['favicon_32'] = array(
'#type' => 'textfield',
'#title' => t('32px Favicon'),
'#description' => t("Favicon image in .PNG format used by newer browsers"),
'#default_value' => theme_get_setting('favicon_32'),
);
$form['c']['meta']['favicons']['apple_icons'] = array(
'#type' => 'fieldset',
'#title' => t('Apple-touch-icons'),
'#description' => t("Apple-touch-icons used by smartphones & tablets. All images should use the .PNG format. Icons that are to be rendered without  the default gloss should use the suffix '-precomposed' in the  file name."),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['meta']['favicons']['apple_icons']['apple_icon_57'] = array(
'#type' => 'textfield',
'#title' => t('57px apple-touch-icon'),
'#description' => t("Defult apple-touch-icon, used by 1st gen iphone."),
'#default_value' => theme_get_setting('apple_icon_57'),
);
$form['c']['meta']['favicons']['apple_icons']['apple_icon_72'] = array(
'#type' => 'textfield',
'#title' => t('72px apple-touch-icon'),
'#description' => t("Icon used by 1st gen ipad."),
'#default_value' => theme_get_setting('apple_icon_72'),
);
$form['c']['meta']['favicons']['apple_icons']['apple_icon_114'] = array(
'#type' => 'textfield',
'#title' => t('114px apple-touch-icon'),
'#description' => t("Icon used by iPhone Retina."),
'#default_value' => theme_get_setting('apple_icon_114'),
);
$form['c']['meta']['favicons']['apple_icons']['apple_icon_144'] = array(
'#type' => 'textfield',
'#title' => t('144px apple-touch-icon'),
'#description' => t("Icon used by iPad Retina."),
'#default_value' => theme_get_setting('apple_icon_144'),
);
/*
* @see file: src/preprocess/theme-settings/markup.inc
* Theme-settings: Display & styling settings.
*/
$form['c']['markup_settings'] = array(
'#type' => 'fieldset',
'#title' => t('Markup'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['markup_settings']['copyright'] = array(
'#type' => 'textfield',
'#title' => t('Copyright'),
'#description' => t("The name of the person or organization to display indicating copyright ownership. Leave field empty to disable display."),
'#default_value' => theme_get_setting('copyright'),
);
$form['c']['markup_settings']['full_menu'] = array(
'#type' => 'checkbox',
'#title' => t('Display All Links in Main Menu'),
'#description' => t('Print the full main_menu tree instead of only top level links. Useful for styling with custom scripts/stylesheets.'),
'#default_value' => theme_get_setting('full_menu'),
);
$form['c']['markup_settings']['breadcrumb_display'] = array(
'#type' => 'checkbox',
'#title' => t('Display Breadcrumbs'),
'#description' => t("Show breadcrumb navigation (Doesn't display on frontpage)"),
'#default_value' => theme_get_setting('breadcrumb_display'),
);
$form['c']['markup_settings']['field_wrappers'] = array(
'#type' => 'checkbox',
'#title' => t('Field Wrappers'),
'#description' => t("Wrap fields with a div and the field's \$attributes"),
'#default_value' => theme_get_setting('field_wrappers'),
);
$form['c']['markup_settings']['login'] = array(
'#type' => 'fieldset',
'#title' => t('User Login Block Settings'),
'#description' => t("Change User Login Block settings"),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
$form['c']['markup_settings']['login']['login_block_orientation'] = array(
'#type' => 'select',
'#title' => t('Login Block Orientation'),
'#description' => t('This setting adds a class (horizontal || vertical) to the user login block.'),
'#options' => array(
'vertical' => t('vertical'),
'horizontal' => t('horizontal'),
),
'#default_value' => theme_get_setting('login_block_orientation '),
);
$form['c']['markup_settings']['login']['login_block_register'] = array(
'#type' => 'checkbox',
'#title' => t('Show link to Register New User Account'),
'#description' => t('Checking this setting shows the link to register a new user account.'),
'#default_value' => theme_get_setting('login_block_register'),
);
$form['c']['markup_settings']['login']['login_block_password'] = array(
'#type' => 'checkbox',
'#title' => t('Show link to reset password'),
'#description' => t('Checking this setting shows the link to reset user password.'),
'#default_value' => theme_get_setting('login_block_password'),
);
/*
* @see file: src/preprocess/theme-settings/style.inc
* Theme-settings: Display & styling settings.
*/
//
$form['c']['style_settings'] = array(
'#type' => 'fieldset',
'#title' => t('Style'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['style_settings']['min_style'] = array(
'#type' => 'checkbox',
'#title' => t('Use minified stylesheets.'),
'#description' => t("Use the minified source (style.min.css)."),
'#default_value' => theme_get_setting('min_style'),
);
$form['c']['style_settings']['r'] = array(
'#type' => 'fieldset',
'#title' => t('Remove Drupal CSS'),
'#description' => t('Prevent stylesheet groups from loading. Individual stylesheets can be removed by adding the module & stylesheet to the array $exclude and calling function cellular_remove_css() in /inc/css_alter.inc.<hr/>'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['style_settings']['r']['remove_drupal_css'] = array(
'#type' => 'radios',
'#title' => t('Remove Drupal CSS'),
'#default_value' => theme_get_setting('remove_drupal_css'),
'#options' => array(
0 => t('Leave CSS intact.'),
'system' => t('Remove all system CSS.'),
'select' => t('Remove system & module CSS chosen by Cellular.'),
'theme_only' => t('Remove all system & module CSS-\n Only use theme CSS.'),
),
);
$form['c']['style_settings']['add_classes'] = array(
'#type' => 'fieldset',
'#title' => t('Content Class Settings'),
'#description' => t("Classes to add to #content and #sidebars for simplified layout with a grid."),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
$form['c']['style_settings']['add_classes']['content_class_no_sidebars'] = array(
'#type' => 'textfield',
'#title' => t('Default Content Class'),
'#description' => t("Class to add to #content if no sidebars are present."),
// '#options' => $grid_values,
'#default_value' => theme_get_setting('content_class_no_sidebars'),
);
$form['c']['style_settings']['add_classes']['content_class_single_sidebar'] = array(
'#type' => 'textfield',
'#title' => t('Content Class w/ Single Sidebar'),
'#description' => t("Class to add to #content if one sidebar is displayed."),
// '#options' => $grid_values,
'#default_value' => theme_get_setting('content_class_single_sidebar'),
);
$form['c']['style_settings']['add_classes']['sidebar_class_single_sidebar'] = array(
'#type' => 'textfield',
'#title' => t('Sidebar Class w/ Single Sidebar'),
'#description' => t("Class to add to #sidebar-left || #sidebar-right if a single sidebar is displayed."),
// '#options' => $grid_values,
'#default_value' => theme_get_setting('sidebar_class_single_sidebar'),
);
$form['c']['style_settings']['add_classes']['content_class_dual_sidebars'] = array(
'#type' => 'textfield',
'#title' => t('Content Class w/ Dual Sidebars'),
'#description' => t("Class to add to #content if both sidebars are displayed."),
// '#options' => $grid_values,
'#default_value' => theme_get_setting('content_class_dual_sidebars'),
);
$form['c']['style_settings']['add_classes']['sidebar_class_dual_sidebars'] = array(
'#type' => 'textfield',
'#title' => t('Sidebar Class w/ Dual Sidebars'),
'#description' => t("Class to add to #sidebar-left && #sidebar-right if both sidebars are displayed."),
// '#options' => $grid_values,
'#default_value' => theme_get_setting('sidebar_class_dual_sidebars'),
);
/*
* @see file: src/preprocess/theme-settings/js.inc
* Theme-settings: Javascript options.
*/
/*
* jQuery CDN options.
* jQuery & jQuery.ui version options are from this array.
*/
$cdn = array(
'provider' => array(
'jquery' => t('jQuery.com'),
'google' => t('Google'),
'microsoft' => t('Microsoft'),
'cloudflare' => t('Cloudflare'),
),
'jquery' => array(
'1.11.1' => t('1.11.1'),
'1.10.2' => t('1.10.2'),
'1.9.1' => t('1.9.1'),
'1.8.3' => t('1.8.3'),
'1.7.2' => t('1.7.2'),
'1.6.4' => t('1.6.4'),
'1.5.2' => t('1.5.2'),
'1.4.4' => t('1.4.4 : default'),
),
'jqueryui' => array(
// @ v.1.11 individual widget js isn't availanle :(
'1.10.4' => t('1.10.4'),
'1.9.2' => t('1.9.2'),
'1.8.24' => t('1.8.24'),
),
);
// Available jQuery.ui themes:
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
// Start js opts.
$form['c']['js'] = array(
'#type' => 'fieldset',
'#title' => t('Javascript'),
'#description' => is_dir('sites/all/libraries/cellular') ? NULL :
t('<div class="messages error"> <h2>These features require the <a href="@url">Cellular Library</a>.</h2></div>', array('@url' => 'https://github.com/ablank/cellular.library')),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
// Modernizr stuff.
$form['c']['js']['modernizr'] = array(
'#type' => 'checkbox',
'#title' => l(t('Modernizr'), 'http://modernizr.com/'),
'#description' => t("Include Modernizr.js to test browser capabilities. The default build tests media queries, flexbox, and svg and includes yepnope.js."),
'#default_value' => theme_get_setting('modernizr'),
);
$form['c']['js']['mdrnzr'] = array(
'#type' => 'fieldset',
'#title' => t('Modernizr'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#states' => array(
'visible' => array(
':input[name="modernizr"]' => array('checked' => TRUE),
),
),
);
$form['c']['js']['mdrnzr']['mq_mobile_enable'] = array(
'#type' => 'checkbox',
'#title' => t('Enable Mobile Media Query'),
'#description' => t("Enable media query to load extra CSS (conditional-mobile.css) for mobile devices."),
'#default_value' => theme_get_setting('mq_mobile_enable'),
'#states' => array(
'visible' => array(
':input[name="modernizr"]' => array('checked' => TRUE),
),
),
);
$form['c']['js']['mdrnzr']['mq_mobile'] = array(
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
$form['c']['js']['mdrnzr']['mq_normal_enable'] = array(
'#type' => 'checkbox',
'#title' => t('Enable Desktop Media Query'),
'#description' => t("Enable media query to test before loading conditional-style.css."),
'#default_value' => theme_get_setting('mq_normale_enable'),
'#states' => array(
'visible' => array(
':input[name="modernizr"]' => array('checked' => TRUE),
),
),
);
$form['c']['js']['mdrnzr']['mq_normal'] = array(
'#type' => 'textfield',
'#title' => t('Normal Media Query'),
'#description' => t("The media query tested by Modernizr load style.css."),
'#default_value' => theme_get_setting('mq_normal'),
'#states' => array(
'visible' => array(
':input[name="mq_normal_enable"]' => array('checked' => TRUE),
),
),
);
$form['c']['js']['mdrnzr']['mq_large_enable'] = array(
'#type' => 'checkbox',
'#title' => t('Enable Conditional Large Media Query'),
'#description' => t("Enable media query to load extra CSS (conditional-large.css) for large screen devices."),
'#default_value' => theme_get_setting('mq_large_enable'),
'#states' => array(
'visible' => array(
':input[name="modernizr"]' => array('checked' => TRUE),
),
),
);
$form['c']['js']['mdrnzr']['mq_large'] = array(
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
// Update jQuery?
$form['c']['js']['jquery_update'] = array(
'#type' => 'checkbox',
'#title' => t('Update jQuery & jQuery UI'),
'#description' => t("Select the version of jQuery & jQueryUI to use. jquery.once &amp; jquery.form will also be updated to the current version."),
'#default_value' => theme_get_setting('jquery_update'),
);
// jQuery & jQuery.ui update settings.
$form['c']['js']['update'] = array(
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
$form['c']['js']['update']['jquery_cdn'] = array(
'#type' => 'checkbox',
'#title' => t('Update via CDN'),
'#description' => t("Update jQuery & jQuery.ui from a selected Content Distribution Network host, falling back to local javascript sources if CDN is unavailable."),
'#default_value' => theme_get_setting('jquery_cdn'),
);
$form['c']['js']['update']['jquery_cdn_source'] = array(
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
$form['c']['js']['update']['jquery'] = array(
'#type' => 'fieldset',
'#title' => t('jQuery'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['js']['update']['jquery']['jquery_version'] = array(
'#type' => 'select',
'#title' => t('jQuery Version'),
'#description' => t("Select the version of jQuery your site will use. The jQuery.migrate module will be loaded automatically for versions > 1.9"),
'#options' => $cdn['jquery'],
'#default_value' => theme_get_setting('jquery_version'),
);
$form['c']['js']['update']['jquery']['jquery_migrate'] = array(
'#type' => 'checkbox',
'#title' => t('jQuery Migrate'),
'#description' => t("Include jQuery.migrate for versions > 1.9 to prevent deprecated functions from breaking."),
'#default_value' => theme_get_setting('jquery_migrate'),
);
// jQuery.ui stuff.
$form['c']['js']['update']['jqueryui'] = array(
'#type' => 'fieldset',
'#title' => t('jQuery UI'),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
$form['c']['js']['update']['jqueryui']['jqueryui_version'] = array(
'#type' => 'select',
'#title' => t('jQueryUI Version'),
'#description' => t("Select the version of jQueryUI your site will use. \nYou will need to match a version compatible with the selected jQuery version."),
'#options' => $cdn['jqueryui'],
'#default_value' => theme_get_setting('jqueryui_version'),
);
$form['c']['js']['update']['jqueryui']['jqueryui_theme'] = array(
'#type' => 'select',
'#title' => t('jQueryUI Theme'),
'#description' => t("Select the jQueryUI theme your site will use. \nCustom themes can be used by copying the contents (css & /images) of the themeroller css directory to \n/sites/all/themes/cellular/css/jquery-ui/%version/custom \nThe custom CSS file must be re-named as:\njquery-ui.custom.css"),
'#options' => $ui_themes,
'#default_value' => theme_get_setting('jqueryui_theme'),
);
// Pre-configured 3rd party plugins.
$form['c']['js']['plugins'] = array(
'#type' => 'fieldset',
'#title' => t('jQuery Plugins'),
'#description' => t("jQuery plugins will load from CDNJS if possible, or use local source as fallback if the CDN source is unavailable."),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
$form['c']['js']['plugins']['backstretch'] = array(
'#type' => 'checkbox',
'#title' => l(t('Backstretch'), 'http://srobbin.com/jquery-plugins/backstretch/'),
'#description' => t("A simple jQuery plugin that allows you to add a  dynamically resized, slideshow-capable background image to any page or element."),
'#default_value' => theme_get_setting('backstretch'),
);
$form['c']['js']['plugins']['flowtype'] = array(
'#type' => 'checkbox',
'#title' => l(t("Flowtype"), 'http://simplefocus.com/flowtype/'),
'#description' => t('Responsive font-size based on element width.'),
'#default_value' => theme_get_setting('flowtype'),
);
$form['c']['js']['plugins']['freetile'] = array(
'#type' => 'checkbox',
'#title' => l(t("Freetile"), 'http://yconst.com/web/freetile/'),
'#description' => t('Freetile is a plugin for jQuery that enables the organization of webpage content in an efficient, dynamic and responsive layout.'),
'#default_value' => theme_get_setting('freetile'),
);
$form['c']['js']['plugins']['jparallax'] = array(
'#type' => 'checkbox',
'#title' => l(t("jParallax"), 'http://stephband.info/jparallax/'),
'#description' => t('jParallax turns nodes into absolutely positioned layers that move in response to the mouse. Depending on their dimensions these layers move at different rates, in a parallaxy kind of way.'),
'#default_value' => theme_get_setting('jparallax'),
);
$form['c']['js']['plugins']['smoove'] = array(
'#type' => 'checkbox',
'#title' => l(t("Smoove"), 'http://smoove.donlabs.com/'),
'#description' => t('Smoove makes it easy to implement awesome CSS3 transition effects, making your content smoothly glide into the page as your scroll down the page.'),
'#default_value' => theme_get_setting('smoove'),
);
// Pre-configured 3rd party js libraries.
$form['c']['js']['lib'] = array(
'#type' => 'fieldset',
'#title' => t('Javascript Libraries'),
'#description' => t("Javascript libraries will load from CDNJS if possible, or use local source as fallback if CDN is unavailable."),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);
$form['c']['js']['lib']['d3js'] = array(
'#type' => 'checkbox',
'#title' => l(t("D3JS"), 'http://d3js.org/'),
'#description' => t('D3.js is a JavaScript library for manipulating documents based on data. D3 helps you bring data to life using HTML, SVG and CSS.'),
'#default_value' => theme_get_setting('d3js'),
);
$form['c']['js']['lib']['gsap'] = array(
'#type' => 'checkbox',
'#title' => l(t('GSAP (GreenSock Animation Platform)'), 'http://www.greensock.com/gsap-js/'),
'#description' => t("GSAP is a suite of tools for scripted, high-performance HTML5 animations that work in all major browsers."),
'#default_value' => theme_get_setting('gsap'),
);
$form['c']['js']['lib']['prism'] = array(
'#type' => 'checkbox',
'#title' => l(t('Prism Syntax Hilighter'), 'http://prismjs.com/'),
'#description' => t("Prism code syntax hilighter."),
'#default_value' => theme_get_setting('prism'),
);
$form['c']['js']['lib']['snap-svg'] = array(
'#type' => 'checkbox',
'#title' => l(t("Snap.SVG"), 'http://snapsvg.io/'),
'#description' => t('The Snap.svg JavaScript library makes working with your SVG assets as easy as jQuery makes working with the DOM.'),
'#default_value' => theme_get_setting('snap-svg'),
);
$form['c']['js']['lib']['threejs'] = array(
'#type' => 'checkbox',
'#title' => l(t('THREE.js'), 'http://threejs.org/'),
'#description' => t("A JavaScript 3D Library which makes WebGL simpler."),
'#default_value' => theme_get_setting('threejs'),
);
/*
* @see file: src/preprocess/theme-settings/social.inc
* Theme-settings: Social media link settings.
*/
/*
settings[sm_follow_title]       = Follow Us
settings[sm_share_title]        = Share this page
*/
$form['c']['social_media'] = array(
'#type' => 'fieldset',
'#title' => t('Social Media'),
'#description' => is_dir('sites/all/libraries/cellular') ? NULL :
t('<div class="messages error"> <h2>These features require the <a href="@url">Cellular Library</a>.</h2> </div>', array('@url' => 'https://github.com/ablank/cellular.library')),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);
// Modernizr is used to load the correct icon stylesheet for the browser.
$form['c']['social_media']['social_media_share'] = array(
'#type' => 'checkbox',
'#title' => t('Share this site'),
'#description' => t("Enable the 'Share this site' bar."),
'#default_value' => theme_get_setting('social_media_share'),
);
$form['c']['social_media']['sm_share_title'] = array(
'#type' => 'textfield',
'#title' => t('Share on Social Media Title'),
'#default_value' => theme_get_setting('sm_share_title'),
'#states' => array(
'visible' => array(
':input[name="social_media_share"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['share'] = array(
'#type' => 'fieldset',
'#title' => t('Social Media Sharing'),
'#description' => t("Select the social media sites to include in the 'Share this site' bar."),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
'#states' => array(
'visible' => array(
':input[name="social_media_share"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['share']['share_facebook'] = array(
'#type' => 'checkbox',
'#title' => t('Facebook'),
'#default_value' => theme_get_setting('share_facebook'),
);
$form['c']['social_media']['share']['share_google_plus'] = array(
'#type' => 'checkbox',
'#title' => t('Google+'),
'#default_value' => theme_get_setting('share_google_plus'),
);
$form['c']['social_media']['share']['share_twitter'] = array(
'#type' => 'checkbox',
'#title' => t('Twitter'),
'#default_value' => theme_get_setting('share_twitter'),
);
$form['c']['social_media']['share']['share_linkedin'] = array(
'#type' => 'checkbox',
'#title' => t('LinkedIn'),
'#default_value' => theme_get_setting('share_linkedin'),
);
$form['c']['social_media']['share']['share_pinterest'] = array(
'#type' => 'checkbox',
'#title' => t('Pinterest'),
'#default_value' => theme_get_setting('share_pinterest'),
);
$form['c']['social_media']['share']['share_reddit'] = array(
'#type' => 'checkbox',
'#title' => t('Reddit'),
'#default_value' => theme_get_setting('share_reddit'),
);
$form['c']['social_media']['social_media_follow'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on social media'),
'#description' => t("Enable the 'Follow Me' bar."),
'#default_value' => theme_get_setting('social_media_follow'),
);
$form['c']['social_media']['sm_follow_title'] = array(
'#type' => 'textfield',
'#title' => t('Follow on Social Media Title'),
'#default_value' => theme_get_setting('sm_follow_title'),
'#states' => array(
'visible' => array(
':input[name="social_media_follow"]' => array('checked' => TRUE),
),
),
);
// Social media follow config.
$form['c']['social_media']['follow'] = array(
'#type' => 'fieldset',
'#title' => t('Follow on Social Media'),
'#description' => t("Links for following your activity on social media sites."),
'#collapsible' => TRUE,
'#collapsed' => FALSE,
'#states' => array(
'visible' => array(
':input[name="social_media_follow"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['follow']['follow_facebook'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on Facebook'),
'#description' => t("Provide a link to follow on facebook."),
'#default_value' => theme_get_setting('follow_facebook'),
);
$form['c']['social_media']['follow']['follow_facebook_url'] = array(
'#type' => 'textfield',
'#title' => t('Facebook URL'),
'#description' => t("URL of the facebook page users may follow."),
'#default_value' => theme_get_setting('follow_facebook_url'),
'#states' => array(
'visible' => array(
':input[name="follow_facebook"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['follow']['follow_google_plus'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on Google+'),
'#description' => t("Provide a link to follow on Google+."),
'#default_value' => theme_get_setting('follow_google_plus'),
);
$form['c']['social_media']['follow']['follow_google_plus_url'] = array(
'#type' => 'textfield',
'#title' => t('Google+ URL'),
'#description' => t("URL of the Google+ profile users may follow."),
'#default_value' => theme_get_setting('follow_google_plus_url'),
'#states' => array(
'visible' => array(
':input[name="follow_google_plus"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['follow']['follow_twitter'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on Twitter'),
'#description' => t("Provide a link to follow on Twitter."),
'#default_value' => theme_get_setting('follow_twitter'),
);
$form['c']['social_media']['follow']['follow_twitter_url'] = array(
'#type' => 'textfield',
'#title' => t('Twitter URL'),
'#description' => t("URL of the Twitter profile users may follow."),
'#default_value' => theme_get_setting('follow_twitter_url'),
'#states' => array(
'visible' => array(
':input[name="follow_twitter"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['follow']['follow_linkedin'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on LinkedIn'),
'#description' => t("Provide a link to follow on LinkedIn."),
'#default_value' => theme_get_setting('follow_linkedin'),
);
$form['c']['social_media']['follow']['follow_linkedin_url'] = array(
'#type' => 'textfield',
'#title' => t('LinkedIn'),
'#description' => t("URL of the LinkedIn profile users may follow."),
'#default_value' => theme_get_setting('follow_linkedin_url'),
'#states' => array(
'visible' => array(
':input[name="follow_linkedin"]' => array('checked' => TRUE),
),
),
);
$form['c']['social_media']['follow']['follow_github'] = array(
'#type' => 'checkbox',
'#title' => t('Follow on Github'),
'#description' => t("Provide a link to follow on Github."),
'#default_value' => theme_get_setting('follow_github'),
);
$form['c']['social_media']['follow']['follow_github_url'] = array(
'#type' => 'textfield',
'#title' => t('Github'),
'#description' => t("URL of the Github profile."),
'#default_value' => theme_get_setting('follow_github_url'),
'#states' => array(
'visible' => array(
':input[name="follow_github"]' => array('checked' => TRUE),
),
),
);
}