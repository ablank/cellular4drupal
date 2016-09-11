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
 * Implements hook_form_system_theme_settings_alter().
 */
function cellular_form_system_theme_settings_alter(&$form, $form_state) {
// Define form to hold pages as tabs.
  $form[0] = array(
    '#type' => 'vertical_tabs',
    '#description' => t('Layout'),
    '#weight' => -10,
    '#attached' => array(),
  );
  /*
   * @see file: src/preprocess/theme-settings/_config.inc
   * jQuery CDN & version settings
   */
  /*
   * jQuery CDN options.
   */
  $cdn = array(
    'provider' => array(
      'jquery' => t('jQuery.com'),
      'google' => t('Google'),
      'microsoft' => t('Microsoft'),
      'cloudflare' => t('Cloudflare'),
    ),
    'jquery' => array(
      '3.1.0' => '3.1.0',
      '2.2.4' => '2.2.4',
      '2.1.4' => '2.1.4',
      '1.12.4' => '1.12.4',
      '1.11.1' => '1.11.1',
      '1.10.2' => '1.10.2',
      '1.9.1' => '1.9.1',
      '1.8.3' => '1.8.3',
      '1.7.2' => '1.7.2',
      '1.6.4' => '1.6.4',
      '1.5.2' => '1.5.2',
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
    'base' => t('Base'),
    'black-tie' => t('Black-Tie'),
    'blitzer' => t('Blitzer'),
    'cupertino' => t('Cupertino'),
    'dark-hive' => t('Dark-Hive'),
    'dot-luv' => t('Dot-Luv'),
    'eggplant' => t('Eggplant'),
    'excite-bike' => t('Excite-Bike'),
    'flick' => t('Flick'),
    'hot-sneaks' => t('Hot-Sneaks'),
    'humanity' => t('Humanity'),
    'le-frog' => t('Le-Frog'),
    'mint-choc' => t('Mint-Choc'),
    'overcast' => t('Overcast'),
    'pepper-grinder' => t('Pepper-Grinder'),
    'redmond' => t('Redmond'),
    'smoothness' => t('Smoothness'),
    'south-street' => t('South-Street'),
    'start' => t('Start'),
    'sunny' => t('Sunny'),
    'swanky-purse' => t('Swanky-Purse'),
    'trontastic' => t('Trontastic'),
    'ui-darkness' => t('UI-Darkness'),
    'ui-lightness' => t('UI-Lightness'),
    'vader' => t('Vader'),
  );
  /*
   * @see file: src/preprocess/theme-settings/meta.inc
   * Theme-settings: Set copyright & favicons.
   */
  $form[0]['meta'] = array(
    '#type' => 'fieldset',
    '#title' => t('Meta'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  /*
    $form[0]['meta']['dev'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode'),
    '#description' => t("Print the page variables array in the messages area, using Devel if available."),
    '#default_value' => theme_get_setting('dev'),
    );
   */
  $form[0]['meta']['copyright'] = array(
    '#type' => 'textfield',
    '#title' => t('Copyright'),
    '#description' => t("The name of the person or organization to display indicating copyright ownership. Leave field empty to disable display."),
    '#default_value' => theme_get_setting('copyright'),
  );
  $form[0]['meta']['cookie_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Cookie Expiration'),
    '#description' => t('Number of days before the theme cookie expires. A <code>first-visit</code> class is added to <code>&lt;body&gt;</code> and <code>Drupal.settings.cellular.first_visit = true</code>. Set to "0" to disable the cookie.'),
    '#default_value' => theme_get_setting('cookie_time'),
  );
  $form[0]['meta']['libpath'] = array(
    '#type' => 'textfield',
    '#title' => t('Cellular Library'),
    '#description' => t('Site relative path to the <a href="@lib">Cellular Library</a>', array(
      '@lib' => 'https://github.com/ablank/cellular.library',
    )),
    '#default_value' => theme_get_setting('libpath'),
  );
  $form[0]['meta']['favicons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Favicons'),
    '#description' => t("Favicons are used by browsers to provide a graphic identity for your site."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form[0]['meta']['favicons']['favicon'] = array(
    '#type' => 'textfield',
    '#title' => t('Favicon'),
    '#description' => t("Default favicon.ico file"),
    '#default_value' => theme_get_setting('favicon'),
  );
  $form[0]['meta']['favicons']['favicon_32'] = array(
    '#type' => 'textfield',
    '#title' => t('32px Favicon'),
    '#description' => t("Favicon image in .PNG format used by newer browsers"),
    '#default_value' => theme_get_setting('favicon_32'),
  );
  $form[0]['meta']['favicons']['apple_icons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Apple-touch-icons'),
    '#description' => t("Apple-touch-icons used by smartphones & tablets. All images should use the .PNG format. Icons that are to be rendered without the default gloss should use the suffix '-precomposed' in the  file name."),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form[0]['meta']['favicons']['apple_icons']['apple_icon_57'] = array(
    '#type' => 'textfield',
    '#title' => t('57px apple-touch-icon'),
    '#description' => t("Defult apple-touch-icon, used by 1st gen iphone."),
    '#default_value' => theme_get_setting('apple_icon_57'),
  );
  $form[0]['meta']['favicons']['apple_icons']['apple_icon_72'] = array(
    '#type' => 'textfield',
    '#title' => t('72px apple-touch-icon'),
    '#description' => t("Icon used by 1st gen ipad."),
    '#default_value' => theme_get_setting('apple_icon_72'),
  );
  $form[0]['meta']['favicons']['apple_icons']['apple_icon_114'] = array(
    '#type' => 'textfield',
    '#title' => t('114px apple-touch-icon'),
    '#description' => t("Icon used by iPhone Retina."),
    '#default_value' => theme_get_setting('apple_icon_114'),
  );
  $form[0]['meta']['favicons']['apple_icons']['apple_icon_144'] = array(
    '#type' => 'textfield',
    '#title' => t('144px apple-touch-icon'),
    '#description' => t("Icon used by iPad Retina."),
    '#default_value' => theme_get_setting('apple_icon_144'),
  );
  /*
   * @see file: src/preprocess/theme-settings/markup.inc
   * Theme-settings: Display & styling settings.
   */
  $form[0]['markup_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Markup'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form[0]['markup_settings']['field_wrappers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Field Wrappers'),
    '#description' => t("Wrap fields with a div containing the field \$attributes"),
    '#default_value' => theme_get_setting('field_wrappers'),
  );
  $form[0]['markup_settings']['full_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display All Links in Main Menu'),
    '#description' => t('Print the full main_menu tree instead of only top level links. Useful for styling with custom scripts/stylesheets.'),
    '#default_value' => theme_get_setting('full_menu'),
  );
  $form[0]['markup_settings']['breadcrumb_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Breadcrumbs'),
    '#description' => t("Show breadcrumb navigation (Doesn't display on frontpage)"),
    '#default_value' => theme_get_setting('breadcrumb_display'),
  );
  $form[0]['markup_settings']['use_colorbox'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Colorbox for User Login/Register links.'),
    '#description' => t("Use Colorbox Node (<em>if available</em>) to display User Login/Register forms."),
    '#default_value' => theme_get_setting('use_colorbox'),
  );
  $form[0]['markup_settings']['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Login Block'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form[0]['markup_settings']['login']['login_block_orientation'] = array(
    '#type' => 'select',
    '#title' => t('Login Block Orientation'),
    '#description' => t('This setting adds a class (horizontal || vertical) to the user login block.'),
    '#options' => array(
      'vertical' => t('vertical'),
      'horizontal' => t('horizontal'),
    ),
    '#default_value' => theme_get_setting('login_block_orientation '),
  );
  $form[0]['markup_settings']['login']['login_block_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show link to Register New User Account'),
    '#description' => t('Checking this setting shows the link to register new user account.'),
    '#default_value' => theme_get_setting('login_block_register'),
  );
  $form[0]['markup_settings']['login']['login_block_password'] = array(
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
  $form[0]['style_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Style'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form[0]['style_settings']['inline_critical_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline critical CSS.'),
    '#description' => t('Include styles for elements \'above the fold\' inline in the document head. Edit the grunt/criticalcss configuration and run the <code>grunt criticalcss</code> task from your theme\'s base directory to generate critical css (<em>overwrites existing .css</em>).'),
    '#default_value' => theme_get_setting('inline_critical_css'),
  );
  $form[0]['style_settings']['remove_drupal_css'] = array(
    '#type' => 'radios',
    '#title' => t('Remove Drupal CSS'),
    '#description' => t('Prevent stylesheet groups from loading. Specific stylesheets can be removed by passing the module & stylesheet as an array to function <code>cellular_remove_css()</code> in /inc/css_alter.inc <hr/>'),
    '#default_value' => theme_get_setting('remove_drupal_css'),
    '#options' => array(
      0 => t('Leave CSS intact.'),
      'select' => t('Remove selected system & module CSS chosen by Cellular.'),
      'system' => t('Remove all system CSS (group => <code>CSS_SYSTEM</code>).'),
      'module' => t('Remove all module CSS. (group => <code>CSS_DEFAULT</code>).'),
      'theme_only' => t('Remove all system & module CSS. Only include theme CSS (group => <code>CSS_THEME</code>).'),
    ),
  );
  /*
   * @see file: src/preprocess/theme-settings/js.inc
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
  /*
   * @see file: src/preprocess/theme-settings/social.inc
   * Theme-settings: Social media link settings.
   */
  $form[0]['social_media'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Media'),
    '#description' => is_dir('sites/all/libraries/cellular') ? NULL :
    t('<div class="messages error"> <h2>These features require the <a href="@url">Cellular Library</a>.</h2> </div>', array('@url' => 'https://github.com/ablank/cellular.library')),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
// Modernizr is used to load the correct icon stylesheet for the browser.
  $form[0]['social_media']['social_media_share'] = array(
    '#type' => 'checkbox',
    '#title' => t('Share this site'),
    '#description' => t("Enable the 'Share this site' bar."),
    '#default_value' => theme_get_setting('social_media_share'),
  );
  $form[0]['social_media']['share'] = array(
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
  $form[0]['social_media']['share']['share_facebook'] = array(
    '#type' => 'checkbox',
    '#title' => t('Facebook'),
    '#default_value' => theme_get_setting('share_facebook'),
  );
  $form[0]['social_media']['share']['share_google_plus'] = array(
    '#type' => 'checkbox',
    '#title' => t('Google+'),
    '#default_value' => theme_get_setting('share_google_plus'),
  );
  $form[0]['social_media']['share']['share_twitter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Twitter'),
    '#default_value' => theme_get_setting('share_twitter'),
  );
  $form[0]['social_media']['share']['share_linkedin'] = array(
    '#type' => 'checkbox',
    '#title' => t('LinkedIn'),
    '#default_value' => theme_get_setting('share_linkedin'),
  );
  $form[0]['social_media']['share']['share_pinterest'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pinterest'),
    '#default_value' => theme_get_setting('share_pinterest'),
  );
  $form[0]['social_media']['share']['share_reddit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reddit'),
    '#default_value' => theme_get_setting('share_reddit'),
  );
  $form[0]['social_media']['share']['share_digg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Digg'),
    '#default_value' => theme_get_setting('share_digg'),
  );
  $form[0]['social_media']['share']['share_stumbleupon'] = array(
    '#type' => 'checkbox',
    '#title' => t('StumbleUpon'),
    '#default_value' => theme_get_setting('share_rstumbleupon'),
  );
  $form[0]['social_media']['share']['share_tumblr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Tumblr'),
    '#default_value' => theme_get_setting('share_tumblr'),
  );
  $form[0]['social_media']['social_media_follow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on social media'),
    '#description' => t("Enable the 'Follow Me' bar."),
    '#default_value' => theme_get_setting('social_media_follow'),
  );
// Social media follow config.
  $form[0]['social_media']['follow'] = array(
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
  $form[0]['social_media']['follow']['follow_facebook'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on Facebook'),
    '#description' => t("Provide a link to follow on facebook."),
    '#default_value' => theme_get_setting('follow_facebook'),
  );
  $form[0]['social_media']['follow']['follow_facebook_url'] = array(
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
  $form[0]['social_media']['follow']['follow_google_plus'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on Google+'),
    '#description' => t("Provide a link to follow on Google+."),
    '#default_value' => theme_get_setting('follow_google_plus'),
  );
  $form[0]['social_media']['follow']['follow_google_plus_url'] = array(
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
  $form[0]['social_media']['follow']['follow_twitter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on Twitter'),
    '#description' => t("Provide a link to follow on Twitter."),
    '#default_value' => theme_get_setting('follow_twitter'),
  );
  $form[0]['social_media']['follow']['follow_twitter_url'] = array(
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
  $form[0]['social_media']['follow']['follow_linkedin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on LinkedIn'),
    '#description' => t("Provide a link to follow on LinkedIn."),
    '#default_value' => theme_get_setting('follow_linkedin'),
  );
  $form[0]['social_media']['follow']['follow_linkedin_url'] = array(
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
  $form[0]['social_media']['follow']['follow_github'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on Github'),
    '#description' => t("Provide a link to follow on Github."),
    '#default_value' => theme_get_setting('follow_github'),
  );
  $form[0]['social_media']['follow']['follow_github_url'] = array(
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
  $form[0]['social_media']['follow']['follow_yelp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Follow on Yelp'),
    '#description' => t("Provide a link to follow on Yelp."),
    '#default_value' => theme_get_setting('follow_yelp'),
  );
  $form[0]['social_media']['follow']['follow_yelp_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Yelp'),
    '#description' => t("URL of the Yelp page."),
    '#default_value' => theme_get_setting('follow_yelp_url'),
    '#states' => array(
      'visible' => array(
        ':input[name="follow_yelp"]' => array('checked' => TRUE),
      ),
    ),
  );
}
