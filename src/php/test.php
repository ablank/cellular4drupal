<?
use \Drupal\Component\Utility\Unicode;
use \Drupal\Core\Asset\AttachedAssetsInterface;

/**
* Implements hook_suggestions_block_alter() for block name suggestions.
*/
function cellular_theme_suggestions_block_alter(array &$suggestions, array $variables) {
if (isset($variables['elements']['content']['#block_content'])) {
array_splice($suggestions, 1, 0, 'block__' . $variables['elements']['content']['#block_content']->bundle());
}
}

/**
* Implements hook_form_FORM_ID_alter().
*/
function cellular_form_search_block_form_alter(&$form, $form_state) {
// Adds placeholder text to the search field.
$form['keys']['#attributes']['placeholder'] = t('Search');
}


/**
* Implements hook_theme_suggestions_HOOK_alter().
*/
function cellular_theme_suggestions_page_alter(array &$suggestions, array $variables) {

$route_name = \Drupal::routeMatch()->getRouteName();
switch ($route_name) {
case 'system.404':
// Page Not Found.
$error = 404;
break;
}
if (isset($error)) {
$suggestions[] = 'page__' . (string) $error;
}
}

/**
* Implements hook_css_alter().
*/
function cellular_css_alter(&$css, \Drupal\Core\Asset\AttachedAssetsInterface $assets) {
$theme_handler = \Drupal::service('theme_handler');
$current_theme = $theme_handler->getDefault();
$path = drupal_get_path('theme', $current_theme);
$info = $theme_handler->getTheme($current_theme)->info;
if (!empty($info['conditional-stylesheets'])) {
foreach ($info['conditional-stylesheets'] as $version => $media) {
foreach ($media as $key => $file_path) {
$full_path = "{$path}/{$file_path}";
$css[$full_path] = [
'group' => CSS_THEME,
'weight' => 999,
'type' => 'file',
'preprocess' => TRUE,
'data' => $full_path,
'media' => $key,
'every_page' => TRUE,
'browsers' => [
'IE'  => $version,
'!IE' => (Unicode::strpos($version, '!IE') !== FALSE),
],
];
}
}
}
}

<?
/**
* Cellular theme preprocess functions.
*/

use Drupal\Core\Form\FormStateInterface;
use Drupal\Component\Utility\Xss;
use Drupal\Core\Render\Markup;

/**
* Implements hook_preprocess_html().
*/
function cellular_preprocess_html(&$variables) {
// Apply a special class to the homepage, which often has no distinct content
// type but often needs special design treatment.
$variables['attributes']['class'][] = \Drupal::service('path.matcher')->isFrontPage() ? 'frontpage' : '';

// Apply a class at the page level based on content type if we're on a node
// page. Also helpful when you need to modify global elements that appear
// outside the node itself.
$variables['attributes']['class'][] = isset($variables['node_type']) ? 'page-node-type--' . $variables['node_type'] : '';

// Check whether the viewer is logged in.
$variables['attributes']['class'][] = $variables['logged_in'] ? 'logged-in' : 'logged-out';
/**
* Inject critical css inline
*/
$criticalCss = file_get_contents('dist/css/critical.css');
$variables['page']['#attached']['html_head'][] = [
[
'#tag' => 'style',
'#value' => Markup::create($criticalCss),
],
'critical-css',
];
}

/**
* Implements hook_preprocess_node().
*/
function cellular_preprocess_node(&$variables) {
// Get the node's content type
$type = $variables['node']->getType();

// Get its view mode
$mode = $variables['view_mode'];

// Make sure we have a class array
if (!isset($variables['attributes']['class'])) {
$variables['attributes']['class'] = [];
}

// Add our classes
$variables['attributes']['class'][] = 'node--type-' . $type; // ex: node--type-article
$variables['attributes']['class'][] = 'node--mode-' . $mode; // ex: node--mode-teaser
$variables['attributes']['class'][] = 'node--type-' . $type . '--mode-' . $mode; // ex: node--type-article--mode-teaser
}

/**
* Implements template_preprocess_block().
*/
function cellular_preprocess_block(&$variables) {
// Custom block type helper classes.
if (!isset($variables['elements']['content']['#block_content'])) {
// This checks whether we actually have a custom, fielded block type, or if
// we're working with a generic out-of-the-box block.
return;
}

// Get the block type name
$bundle = $variables['elements']['content']['#block_content']->bundle();

// Make sure we have a class array
if (!isset($variables['attributes']['class'])) {
$variables['attributes']['class'] = [];
}

// Add our class
$variables['attributes']['class'][] = 'block--bundle-' . $bundle;
}

/**
* Implements hook_preprocess_HOOK() for menu-local-task templates.
*/
function cellular_preprocess_menu_local_task(&$variables) {
$variables['attributes']['class'][] = 'nav-item';
$variables['link']['#options']['attributes']['class'][] = 'nav-link';
}

/**
* Implements hook_preprocess_input() for form submit button.
*/
function cellular_preprocess_input(&$variables) {
$element = $variables['element'];
if ($element['#type'] == 'submit') {
$variables['attributes']['class'][] = 'btn btn-primary btn-sm';
}
elseif ($element['#type'] == 'checkbox' || $element['#type'] == 'radio') {
$variables['attributes']['class'][] = 'form-check-input';
}
else {
$variables['attributes']['class'][] = 'form-control form-control-' . $element['#type'];
}
}
/**
* Implements hook_preprocess_media().
*/
function cellular_preprocess_media(&$variables) {
// Get the media entity's bundle (such as video, image, etc.)
$mediaType = $variables['media']->bundle();

// Make sure we have a class array, just like with the nodes
if (!isset($variables['attributes']['class'])) {
$variables['attributes']['class'] = [];
}

// Add a class
$variables['attributes']['class'][] = 'media--type-' . $mediaType; // ex: media--type-video
}

/**
* Implements hook_preprocess().
*/
function cellular_preprocess(&$variables) {
$config = \Drupal::config('system.site');
// Default variables.
$variables['sitename'] = $config->get('name');
$variables['siteslogan'] = $config->get('slogan');
// Theme variables
$variables['cellular'] = [];
$cellular_settings = [
'display_sample_blocks',
'header_color',
'header_link_style',
'header_type',
'header_type_sticky',
'header_type_sticky_resize',
'copyright_text',
'display_theme_credits',
'display_social_round_icons',
'header_position',
];
$page_settings = [
'page_header_style',
];
$social_profiles = [
'social_facebook',
'social_googleplus',
'social_linkedin',
'social_twitter',
'social_youtube',
];

$textarea_settings = [
'user_page_intro',
];

// Retrieve General and Header options.
foreach ($cellular_settings as $cellular_setting) {
$value = trim(theme_get_setting($cellular_setting, 'cellular'));
if (!empty($value)) {
$variables['cellular'][$cellular_setting] = Xss::filter($value);
}
}

// Retrieve Page related theme options.
foreach ($page_settings as $page_setting) {
$value = trim(theme_get_setting($page_setting, 'cellular'));
if (!empty($value)) {
$variables['cellular'][$page_setting] = Xss::filter($value);
}
}

// Retrieve social profiles.
foreach ($social_profiles as $social_profile) {
$value = trim(theme_get_setting($social_profile, 'cellular'));
if (!empty($value)) {
$variables['cellular']['social_profiles'][$social_profile] = Xss::filter($value);
}
}

// Retrieve textarea and text format related fields.
foreach ($textarea_settings as $textarea_setting) {
$value = check_markup(theme_get_setting($textarea_setting, 'cellular'), 'full_html');
if (!empty($value)) {
$variables['cellular'][$textarea_setting] = Xss::filter($value);
}
}

// Process Copyright text.
$copyright_text = theme_get_setting('copyright_text');
if (!empty($copyright_text)) {
$copyright_text = str_replace('@year', date('Y'), theme_get_setting('copyright_text'));
$variables['cellular']['copyright_text'] = $copyright_text;
}
// Process theme credits.
$display_theme_credits = theme_get_setting('display_theme_credits');
if (!empty($display_theme_credits)) {
$variables['cellular']['theme_credits']['#markup'] = t(
'Built with loving kindness by <a href="@url" target="_blank">ablank</a>',
['@url' => 'https://github.com/ablank']
);
}
}

<?

/**
* Theme settings for Cellular theme.
* Implements hook_form_FORM_ID_alter()
*/
function cellular_form_system_theme_settings_alter(&$form, FormStateInterface $form_state) {

// Footer copyrights settings.
$form['cellular_settings'] = [
'#type' => 'fieldset',
'#title' => t('Cellular Theme Settings'),
'#collapsible' => FALSE,
'#collapsed' => FALSE,
];

$form['cellular_settings']['tabs'] = [
'#type' => 'vertical_tabs',
'#default_tab' => 'general_tab',
];

$form['cellular_settings']['general_tab']['general_options'] = [
'#type' => 'details',
'#title' => t('General Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['general_tab']['general_options']['display_sample_blocks'] = [
'#type' => 'checkbox',
'#title' => t('Show Sample Blocks'),
'#default_value' => theme_get_setting('display_sample_blocks', 'cellular'),
'#description' => t('Just shows sample blocks for your idea. On production disable this'),
];

$form['cellular_settings']['general_tab']['general_options']['user_page_intro'] = [
'#type' => 'textarea',
'#title' => t('User Page Intro'),
'#default_value' => theme_get_setting('user_page_intro', 'cellular'),
'#description' => t('Text will be shown on left side of login, registration, forgot password pages.'),
];

$form['cellular_settings']['header_tab']['header_options'] = [
'#type' => 'details',
'#title' => t('Top Header Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['header_tab']['header_options']['header_position'] = [
'#type' => 'select',
'#title' => t('Header Position'),
'#default_value' => theme_get_setting('header_position', 'cellular'),
'#description' => t('Choose header position'),
'#options' => [
'header-top' => t('Top'),
'header-left' => t('Left'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_color'] = [
'#type' => 'color',
'#title' => t('Header Background Color'),
'#default_value' => theme_get_setting('header_color', 'cellular'),
'#description' => t('Choose color that applies to header as background color. If choose header type Overlay, then background color will apply only when sticky header'),
];

$form['cellular_settings']['header_tab']['header_options']['header_link_style'] = [
'#type' => 'select',
'#title' => t('Header link Style'),
'#default_value' => theme_get_setting('header_link_style', 'cellular'),
'#description' => t('Choose header link style'),
'#options' => [
'navbar-dark' => t('Light'),
'navbar-light' => t('Dark'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_type'] = [
'#type' => 'select',
'#title' => t('Header Type'),
'#description'   => t('Choose header type. If you choose overlay, then header will be overlaid over the below section/content.'),
'#default_value' => theme_get_setting('header_type', 'cellular'),
'#options' => [
'standard' => t('Standard'),
'overlay' => t('Overlay'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_type_sticky'] = [
'#type' => 'checkbox',
'#title' => t('Sticky Header'),
'#default_value' => theme_get_setting('header_type_sticky', 'cellular'),
'#description' => t('Enable the sticky header when scrolling down the page'),
];

$form['cellular_settings']['header_tab']['header_options']['header_type_sticky_resize'] = [
'#type' => 'checkbox',
'#title' => t('Sticky header resizing'),
'#default_value' => theme_get_setting('header_type_sticky_resize', 'cellular'),
'#description' => t('Enable the sticky header to resize when scrolling down the page'),
];

$form['cellular_settings']['page_tab']['page_options'] = [
'#type' => 'details',
'#title' => t('Page Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['page_tab']['page_options']['page_header_style'] = [
'#type' => 'select',
'#title' => t('Page Header Style'),
'#default_value' => theme_get_setting('page_header_style', 'cellular'),
'#description' => t('Choose page header style. Ex. default, Full size, Box size. If node has field_image field then image shown as background for full and box sizes.'),
'#options' => [
'default' => t('Default'),
'full-size' => t('Full Size'),
'box-size' => t('Box Size'),
],
];

$form['cellular_settings']['social_tab']['social_profiles'] = [
'#type' => 'details',
'#title' => t('Social Profiles'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['social_tab']['social_profiles']['display_social_round_icons'] = [
'#type' => 'checkbox',
'#title' => t('Show round icons'),
'#default_value' => theme_get_setting('display_social_round_icons', 'cellular'),
'#description' => t('Enable to show round icons for below updated social profiles'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_facebook'] = [
'#type' => 'textfield',
'#title' => t('Facebook'),
'#default_value' => theme_get_setting('social_facebook', 'cellular'),
'#description' => t('Your facebook page/profile url'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_googleplus'] = [
'#type' => 'textfield',
'#title' => t('Google+'),
'#default_value' => theme_get_setting('social_googleplus', 'cellular'),
'#description' => t('Your Google+ page/profile URL'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_linkedin'] = [
'#type' => 'textfield',
'#title' => t('LinkedIn'),
'#default_value' => theme_get_setting('social_linkedin', 'cellular'),
'#description' => t('Your LinkedIn page/profile url'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_twitter'] = [
'#type' => 'textfield',
'#title' => t('Twitter'),
'#default_value' => theme_get_setting('social_twitter', 'cellular'),
'#description' => t('Your Twitter username (no @).'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_youtube'] = [
'#type' => 'textfield',
'#title' => t('Youtube'),
'#default_value' => theme_get_setting('social_youtube', 'cellular'),
'#description' => t('Your YouTube URL'),
];

$form['cellular_settings']['footer_tab']['footer_options'] = [
'#type' => 'details',
'#title' => t('Footer Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['footer_tab']['footer_options']['copyright_text'] = [
'#type' => 'textfield',
'#title' => t('Enter copyright text'),
'#default_value' => theme_get_setting('copyright_text', 'cellular'),
'#description' => t('The copyright text that appears in the footer. Use @year placeholder for define current year.'),
];

$form['cellular_settings']['footer_tab']['footer_options']['backlink_container'] = [
'#type' => 'fieldset',
'#title' => t('Show Backlink'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
];

$form['cellular_settings']['footer_tab']['footer_options']['backlink_container']['display_theme_credits'] = [
'#type' => 'checkbox',
'#title' => t('Display theme credits'),
'#default_value' => theme_get_setting('display_theme_credits', 'cellular'),
'#description' => t('If checked, a backlink to our site will be shown in the footer. This is not compulsory, but always appreciated!'),
];
}
