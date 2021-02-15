<?
/**
 * Cellular theme preprocess functions.
 */

use Drupal\Core\Form\FormStateInterface;
use Drupal\Component\Utility\Xss;

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
 * Implements hook_preprocess().
 */
function cellular_preprocess(&$variables) {
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
      '<small>Build with <i class="fas fa-heart"></i> by <a href="@url" target="_blank">Sreenivas Bttv</a></small>',
      ['@url' => 'http://www.bttvs.com']
    );
  }

  // Default variables.
  $variables['sitename'] = \Drupal::config('system.site')->get('name');
  $variables['siteslogan'] = \Drupal::config('system.site')->get('slogan');
}

/**
 * Implements hook_preprocess_HOOK() for menu-local-task templates.
 */
function cellular_preprocess_menu_local_task(&$variables) {
  $variables['attributes']['class'][] = 'nav-item';
  $variables['link']['#options']['attributes']['class'][] = 'nav-link';
}