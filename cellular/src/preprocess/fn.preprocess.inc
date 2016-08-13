<?php
/**
 * @file
 * Cellular functions to set content attributes.
 */
/**
 * Test if sidebar regions are used and return the appropriate class.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.

  function cellular_test_sidebar(&$vars) {
  empty($vars['page']['sidebar_left']) ? NULL : $sidebar_left = 1;
  empty($vars['page']['sidebar_right']) ? NULL : $sidebar_right = 1;

  if (!isset($sidebar_left) && !isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_no_sidebar');
  }
  elseif (isset($sidebar_left) && isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_dual_sidebars');
  $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_dual_sidebars');
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_single_sidebar');
  $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_single_sidebar');
  }
  } */

/**
 *
 */
function cellular_author_info(&$vars) {
  // Author info
  $aid = user_load($vars['uid']);
  if (!empty($aid)) {
    dpm($vars);
    /* $author = theme('image_style', array(
     * 'style_name' => 'thumbnail',
     * 'path' => $user->picture->uri,
     * )); */
    $author = theme('user_picture', array(
      'account' => $aid,
      'style_name' => 'thumbnail',
      '#attributes' => array('class' => array('author-image')),
    ));
    $author .= $aid->name;
  }

  // Push formatted author block to $vars array.
  return $author;
}

function cellular_post_date($node) {
  // Date node was created.
  $date = "\n<span class=\"day\">" . date("j", $node->created) . "</span>\n";
  $date .= "<span class=\"month\">" . date("M", $node->created) . "</span>\n";
  $date .= "<span class=\"year\">" . date("Y", $node->created) . "</span>\n";

  return $date;
}

/**
 * Set path to page-error.tpl if header error code is returned.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_error_page(&$vars) {
  $http_status = drupal_get_http_header("status");
  // Set error page template if error.
  switch ($http_status) {
    case "403 Forbidden":
    case "404 Not Found":
    case "500 Internal Server Error":
      $vars['theme_hook_suggestions'][] = 'page__error';
      $vars['http_status'] = "Error: " . $http_status;
      $vars['classes_array'][] = 'page-error';
      $vars['error_message'] = drupal_get_messages();
      break;
  }
}
