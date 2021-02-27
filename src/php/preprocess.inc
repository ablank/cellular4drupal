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
