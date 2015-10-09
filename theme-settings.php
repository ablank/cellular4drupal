<?php
use Drupal\Component\Utility\SafeMarkup;
use Drupal\Core\Form\FormStateInterface;
use Drupal\system\Form\ThemeSettingsForm;
use Drupal\file\Entity\File;
use Drupal\Core\Url;

/*
  $plugins = array(
  'cellularui',
  'backstretch',
  'flowtype',
  'freetile',
  'parallax',
  'smoove'
  );

  $libs = array(
  'd3',
  'gsap',
  'modernizr',
  'prism',
  'snapsvg',
  'three',
  );
 */
$theme = 'cellular';

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function cellular_form_system_theme_settings_alter(&$form, &$form_state) {

  $form['cellular'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'social',
  );

  include_once('src/theme-settings/meta.inc');
  include_once('src/theme-settings/markup.inc');
  include_once('src/theme-settings/javascript.inc');
  include_once('src/theme-settings/style.inc');
  include_once('src/theme-settings/social.inc');
}
