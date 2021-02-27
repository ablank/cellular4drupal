<?
use \Drupal\Component\Utility\Unicode;
use \Drupal\Core\Asset\AttachedAssetsInterface;

/**
* Implements hook_suggestions_block_alter()
*/
function cellular_theme_suggestions_block_alter(array &$suggestions, array $variables) {
// Suggestions for block templates.
if (isset($variables['elements']['content']['#block_content'])) {
array_splice($suggestions, 1, 0, 'block__' . $variables['elements']['content']['#block_content']->bundle());
}
}

/**
* Implements hook_form_FORM_ID_alter().
*/
function cellular_form_search_block_form_alter(&$form, $form_state) {
// Add placeholder text to the search field.
$form['keys']['#attributes']['placeholder'] = t('Search');
}


/**
* Implements hook_theme_suggestions_HOOK_alter().
*/
function cellular_theme_suggestions_page_alter(array &$suggestions, array $variables) {
// Suggestions for error page templates.
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
// Add conditional stylesheets
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
