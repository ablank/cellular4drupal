<?php
/**
 * @file
 * Cellular utility functions.
 */

/**
 * Add <link> & <meta> tags from an array.
 */
function cellular_build_head_tags($array) {
  foreach ($array as $meta => $val) {
    if (isset($val)) {
      // Build tag:
      $tag = array(
        '#type' => 'html_tag',
        '#tag' => $val['tag'],
        '#attributes' => array(),
        '#weight' => isset($val['weight']) ?
          $val['weight'] : 0,
      );
      // Misc. attr/val:
      isset($val['attr']) && isset($val['attr_val']) ?
          $tag['#attributes'][$val['attr']] = $val['attr_val'] : NULL;
      isset($val['profile']) ?
          $tag['#attributes']['profile'] = $val['profile'] : NULL;
      // General attributes:
      isset($val['name']) ?
          $tag['#attributes']['name'] = $val['name'] : NULL;
      isset($val['rel']) ?
          $tag['#attributes']['rel'] = $val['rel'] : NULL;
      isset($val['content']) ?
          $tag['#attributes']['content'] = $val['content'] : NULL;
      isset($val['href']) ?
          $tag['#attributes']['href'] = $val['href'] : NULL;
      // Attributes for favicons:
      isset($val['size']) ?
          $tag['#attributes']['sizes'] = $val['size'] : NULL;
      isset($val['type']) ?
          $tag['#attributes']['type'] = $val['type'] : NULL;

      drupal_add_html_head($tag, 'meta_' . $meta);
    }
  }
}

/**
 * Set path to page-error.tpl if http error is returned.
 */
function cellular_error_page(&$vars) {
// Set custom error template:
  $http_status = drupal_get_http_header("status");

  if (isset($http_status)) {

    switch ($http_status) {
      case "403 Forbidden":
      case "404 Not Found":
      case "500 Internal Server Error":
        $vars['theme_hook_suggestions'][] = 'page__error';
        $vars['http_status'] = "Error: " . $http_status;
        $vars['error_message'] = drupal_get_messages();
        $vars['classes_array'][] = 'page-error';
        break;
    }
  }
}

  /**
   * Removes text formatting options from user input.
   */
  function cellular_form_strip_access(&$form) {
    // Remove individual text format options:
    // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
    // Or Nuke text format options:
    $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;

    return $form;
  }

  /**
   * Print variables.
   */
  function cellular_dev($element) {
    if (theme_get_setting('dev') == 1) {
      if (module_exists('devel')) {
        dpm($element);
      }
      else {
        drupal_set_message('<pre>'. print_r($element, TRUE) .'</pre>');
      }
    }
  }
