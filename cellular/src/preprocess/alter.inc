<?php

/**
 * @file
 * Alter misc. hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 */
function cellular_html_head_alter(&$head_elements) {
  // Remove unwanted meta tags.
  unset($head_elements['system_meta_generator']);
}

/**
 * Implements hook_page_alter().
 */
function cellular_page_alter(&$vars) {
  $element = $vars['content'];

  $styles = array(
    'style' => array(
      'file' => 'style' . CELLULAR_CSS_EXT,
      'weight' => 100,
    ),
    'drupal' => array(
      'file' => 'drupal' . CELLULAR_CSS_EXT,
      'weight' => 99,
    ),
    // Single stylesheet used to hack old internet explorer quirks.
    // Minimal support for deprecated breowsers is fine imo...
    'ie' => array(
      'file' => 'ie' . CELLULAR_CSS_EXT,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'group' => CSS_THEME,
      'weight' => 999,
    ),
    'print' => array(
      'file' => 'print' . CELLULAR_CSS_EXT,
      'media' => 'print',
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'weight' => 101,
    ),
  );

  $scripts = array(
    'script' => array(
      'file' => 'script' . CELLULAR_JS_EXT,
      'group' => JS_THEME,
      'weight' => 100,
    ),
    'plugins' => array(
      'file' => 'plugins' . CELLULAR_JS_EXT,
      'group' => JS_THEME,
      'weight' => 99,
    ),
  );

  if (theme_get_setting('cellularui') == 1) {
    $cellular_settings = array('cellularui' => TRUE);

    $scripts['cellularui'] = array(
      'object' => 'cellular',
      'file' => 'jquery.cellular-ui' . CELLULAR_JS_EXT,
      'group' => JS_THEME,
      'weight' => 98,
    );

    if (theme_get_setting('social_media_follow') == 1) {
      $cellular_settings['jSocial_follow'] = cellular_social_media_follow();
    }

    if (theme_get_setting('social_media_share') == 1) {
      $cellular_settings['jSocial_share'] = cellular_social_media_share();
    }
    // Add cellular to Drupal.settings.
    drupal_add_js(array('cellular' => $cellular_settings), 'setting');
  }
  // Attach styles.
  cellular_attach_css($vars['content'], $styles);
  // Attach scripts.
  cellular_attach_js($vars['content'], $scripts);
  // Add plugin assets.
  cellular_attach_js($vars['content'], cellular_plugins_js(), TRUE);
  cellular_attach_css($vars['content'], cellular_plugins_css(), TRUE);
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Add to Cellular plugin settings to Drupal.settings.
  drupal_add_js(array('cellular' => cellular_js_plugin_settings()), 'setting');
  //dpm($vars);
}
