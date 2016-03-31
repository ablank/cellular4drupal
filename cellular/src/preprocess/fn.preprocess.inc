<?php
/**
 * @file
 * Cellular functions to set content attributes.
 */

/**
 * Add HTTP Response Headers.
 */
function cellular_http_headers() {
  // Try to prevent clickjacking.
  drupal_add_http_header('X-Frame-Options', 'DENY');
  // Set IE compatibility mode.
  drupal_add_http_header('X-UA-Compatible', 'IE=Edge,chrome=1');
}

/**
 * Set html attributes.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_html_attributes(&$vars) {
  global $language;

  $vars['doctype'] = "<!DOCTYPE html>\n";
  $html_attributes = array(
    'lang' => $language->language,
    'xml:lang' => $language->language,
    'dir' => $language->dir,
  );
  // Check support for RDF, adding namespace if needed.
  if (module_exists('rdf')) {
    // Set namespace.
    $html_attributes['xmlns'] = 'http://www.w3.org/1999/xhtml';
  }

  $vars['html_attributes'] = drupal_attributes($html_attributes);
}

/**
 * Convert xmlns to profile.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_rdf(&$vars) {
  // Add extra namespaces if needed:
  // $vars['rdf_namespaces'] .= "\nxmlns:og=\"http://opengraphprotocol.org/schema/\"";
  // Check support for RDF & add attributes:
  if (module_exists('rdf')) {
    // @see http://phase2technology.com/?p=552
    $head_attributes = array();
    $prefixes = array();
    $namespaces = explode("\n", trim($vars['rdf_namespaces']));

    foreach ($namespaces as $name) {
      list($key, $url) = explode('=', $name, 2);
      list($xml, $space) = explode(':', $key, 2);
      unset($xml);
      $url = trim(str_replace('"', '', $url));
      $prefixes[] = "\n" . $space . ": " . $url;
    }
    $head_attributes['prefix'] = implode(' ', $prefixes);

    $vars['rdf_prefixes'] = drupal_attributes($head_attributes);
  }
}

/**
 * Add variable classes to <body>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_body_attributes(&$vars) {
  $body_attributes = array();
  $path = drupal_get_path_alias();
  // Page URL is used to set id & classes of body.
  $aliases = explode('/', $path);
  // Set the current page as body id:
  $body_attributes['id'] = array_pop($aliases);

  // Add body classes:
  foreach ($aliases as $alias) {
    $body_attributes['class'][] = $alias;
  }

  // Sidebar class is generated if region is used on page.
  $body_attributes['class'][] = cellular_test_sidebar($vars);
  drupal_is_front_page() ? $body_attributes['class'][] = 'frontpage' : NULL;
  user_is_logged_in() ? $body_attributes['class'][] = 'user' : NULL;

  $vars['body_attributes'] = drupal_attributes($body_attributes);
}

/**
 * Build links to favicons & apple-touch-icons.
 */
function cellular_favicons() {
  // Get icon file names from theme settings.
  $settings = array(
    'favicon' => theme_get_setting('favicon'),
    'favicon-32' => theme_get_setting('favicon_32'),
    'apple-default' => theme_get_setting('apple_icon_57'),
    'apple-72' => theme_get_setting('apple_icon_72'),
    'apple-114' => theme_get_setting('apple_icon_114'),
    'apple-144' => theme_get_setting('apple_icon_144'),
  );

  $favicons = array();
  !empty($settings['favicon']) ? $favicons['favicon-16x16'] = array(
    'rel' => 'shortcut icon',
    'type' => 'image/x-icon',
    'size' => NULL,
    'href' => $settings['favicon'],
    'weight' => 95,
  ) : NULL;
  !empty($settings['favicon-32']) ? $favicons['favicon-32x32'] = array(
    'rel' => 'shortcut icon',
    'type' => 'image/png',
    'size' => '32x32',
    'href' => $settings['favicon-32'],
    'weight' => 96,
  ) : NULL;
  /* Older iOS devices don't understand the sizes attribute and use
   * whichever value is last, so 'default' is given highest weight.
   */
  !empty($settings['apple-default']) ? $favicons['apple-default'] = array(
    'rel' => 'apple-touch-icon',
    'size' => NULL,
    'href' => $settings['apple-default'],
    'weight' => 100,
  ) : NULL;
  !empty($settings['apple-72']) ? $favicons['apple-72x72'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '72x72',
    'href' => $settings['apple-72'],
    'weight' => 99,
  ) : NULL;
  !empty($settings['apple-114']) ? $favicons['apple-114x114'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '114x114',
    'href' => $settings['apple-114'],
    'weight' => 98,
  ) : NULL;
  !empty($settings['apple-144']) ? $favicons['apple-144x144'] = array(
    'rel' => 'apple-touch-icon',
    'size' => '144x144',
    'href' => $settings['apple-144'],
    'weight' => 97,
  ) : NULL;

  foreach ($favicons as &$favicon) {
    if (isset($favicon)) {
      // Set tag type to <link>
      $favicon['tag'] = 'link';
      // Set href relative to /assets/favicons/
      $favicon['href'] = $GLOBALS['base_url'] . '/' . CURRENT_THEME_PATH . '/assets/favicons/' . $favicon['href'];
    }
  }

  cellular_build_head_tags($favicons);
}

/**
 * Add meta tags to <head>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_metatags(&$vars) {
  $meta_tags = array(
    'viewport' => array(
      'tag' => 'meta',
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
      'weight' => 0,
    ),
    'robots' => array(
      'tag' => 'meta',
      'name' => 'robots',
      'content' => 'index, follow',
      'weight' => 2,
    ),
    'humans' => array(
      'tag' => 'link',
      'type' => 'text/plain',
      'rel' => 'author',
      'href' => $GLOBALS['base_url'] . '/humans.txt',
      'weight' => 3,
    ),
  );

  // Add conditional metatags:
  isset($vars['grddl_profile']) ? $meta_tags['grddl'] = array(
    'tag' => 'link',
    'rel' => 'profile',
    'href' => $vars['grddl_profile'],
    'weight' => 4,
  ) : NULL;

  cellular_build_head_tags($meta_tags);
}

/**
 * Test if sidebar regions are used and return the appropriate class.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
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
}

/* Under development, process vars for comment & node */

/**
 *
 */
function cellular_author_info(&$vars) {
  // Author info
  $aid = user_load($vars['uid']);
  if (!empty($aid)) {
    $author = theme('user_picture', array('account' => $aid));
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
