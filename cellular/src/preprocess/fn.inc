<?php

/**
 * @file
 * Cellular utility functions.
 */

/**
 * Get path to the active theme.
 *
 * @param mixed $theme_key
 *   The name of the theme to get path to, defaults to active theme.
 *
 * @return string
 *   Path to active theme.
 */
function cellular_theme_path(&$theme_key = NULL) {
  $theme = $theme_key ?? $GLOBALS['theme_key'];

  return drupal_get_path('theme', $theme);
}

/**
 * Display variables.
 *
 * @param array $element
 *
 * @return void
 */
function cellular_dev(array $element) {
  if (theme_get_setting('dev') == 1) {
    if (module_exists('devel')) {
      dpm($element);
    }
    else {
      drupal_set_message('<pre>' . print_r($element, TRUE) . '</pre>');
    }
  }
}

/**
 * Get media query breakpoints from theme settings.
 *
 * @return array
 *   Media queries settings.
 */
function cellular_mq() {
  $mq = array(
    'mobile' => theme_get_setting('mq_mobile'),
    'normal' => theme_get_setting('mq_normal'),
    'large' => theme_get_setting('mq_large'),
  );

  return $mq;
}

/**
 * Get file extensions as .min based on theme settings.
 *
 * @param string $type
 *   Type of file to test settings for, either css or js.
 *
 * @return array
 *   Extension string for each file type.
 */
function cellular_ext(string $type) {
  $settings = array(
    'css' => '.css',
    'js' => '.js',
  );

  return $settings[$type];
}

/**
 * Add <link> & <meta> tags from an array.
 *
 * @param array $array
 *   Array of tags to add to document <head>.
 */
function cellular_build_head_tags(array $array) {
  foreach ($array as $meta => $val) {
    // Build tag:
    $tag = array(
      '#type' => 'html_tag',
      '#tag' => $val['tag'],
      '#attributes' => array(),
      '#weight' => $val['weight'] ?? 0,
    );
    // Misc. attr/val:
    empty($val['attr']) || empty($val['attr_val']) ? NULL :
      $tag['#attributes'][$val['attr']] = $val['attr_val'];
    empty($val['profile']) ? NULL :
      $tag['#attributes']['profile'] = $val['profile'];
    // General attributes:
    empty($val['name']) ? NULL :
      $tag['#attributes']['name'] = $val['name'];
    empty($val['rel']) ? NULL :
      $tag['#attributes']['rel'] = $val['rel'];
    empty($val['content']) ? NULL :
      $tag['#attributes']['content'] = $val['content'];
    empty($val['href']) ? NULL :
      $tag['#attributes']['href'] = $val['href'];
    // Attributes for favicons:
    empty($val['size']) ? NULL :
      $tag['#attributes']['sizes'] = $val['size'];
    empty($val['type']) ? NULL :
      $tag['#attributes']['type'] = $val['type'];

    drupal_add_html_head($tag, 'meta_' . $meta);
  }
}

/**
 * Removes text formatting options from user input.
 *
 * @param array $form
 *   Form element to set.
 * @param array $form_state
 *   Form element's state.
 */
function cellular_form_format_opt(array &$form, array $form_state) {
  // Remove individual text format options:
  // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
  // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
  // Or Nuke text format options:
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;
  $form[LANGUAGE_NONE][0]['format']['#default_value'] = 'filtered';

  return $form;
}

/**
 * Print variables for development as message, useful if devel isn't active.
 *
 * @param array $element
 *   Element to test and return variables of.
 * @param bool $cellular
 *   Load from cellular lib? or local theme.
 */
function cellular_proccess_asset(array &$asset, bool $cellular = NULL) {
  // Set data source as CDN or local host.
  if (isset($asset['data'])) {
    $data = $asset['data'];
  }
  elseif (isset($asset['cdn'])) {
    $data = $asset['cdn'];
  }
  elseif (isset($asset['file'])) {
    $data = $cellular == TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH;
    // $data .= '/css/' . $asset['file'];
  }
  if (!empty($data)) {
    // Set stylesheet properties.
    $asset['data'] = $data;
    $asset['preprocess'] = $asset['preprocess'] ?? TRUE;
    $asset['every_page'] = $asset['every_page'] ?? TRUE;
    $asset['weight'] = $asset['weight'] ?? 1;
    $asset['type'] = isset($asset['cdn']) ? 'external' : 'file';
  }
}
