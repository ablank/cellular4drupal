<?php
/**
 * @file
 * HTML preprocess functions.
 */

/**
 * Implements template_preprocess_html().
 */
function cellular_preprocess_html(&$vars) {

  cellular_http_headers();
  $cookies = cellular_cookies();
  cellular_html_attributes($vars);
  cellular_rdf($vars);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars, $cookies);

  $cellular_theme_path = drupal_get_path('theme', 'cellular');

  /* Add javascript. */

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
  // Add to plugin settings to Drupal.settings.
  $cellular_settings = array(
    'first_visit' => !$cookies,
    'plugins' => cellular_js_plugin_settings(),
  );
  if (theme_get_setting('cellularui') == 1) {
    $cellular_settings['ui'] = array();
    $scripts['cellularui'] = array(
      'object' => 'cellular',
      'file' => 'jquery.cellular-ui' . CELLULAR_JS_EXT,
      'group' => JS_THEME,
      'weight' => 98,
    );
    if (theme_get_setting('social_media_follow') == 1) {
      $cellular_settings['ui']['jSocial_follow'] = cellular_social_media_follow();
    }
    if (theme_get_setting('social_media_share') == 1) {
      $cellular_settings['ui']['jSocial_share'] = cellular_social_media_share();
    }
  }
  // Add settings to Drupal.settings.cellular
  drupal_add_js(array('cellular' => $cellular_settings), 'setting');
  // Add theme scripts.
  cellular_add_js($scripts);
  // Add plugin scripts.
  cellular_add_js(cellular_plugins_js(), TRUE);
  // Add JS classes to body.
  drupal_add_js('document.body.className += " javascript cellular";', array(
    'type' => 'inline',
    'scope' => 'critical',
    'weight' => 1,
  ));

  /* Add stylesheets. */

  $styles = array(
    'style' => array(
      'file' => 'style' . CELLULAR_CSS_EXT,
      'weight' => 99,
    ),
    'drupal' => array(
      'file' => 'drupal' . CELLULAR_CSS_EXT,
      'weight' => 100,
    ),
    'print' => array(
      'file' => 'print' . CELLULAR_CSS_EXT,
      'media' => 'print',
      'preprocess' => FALSE,
      'group' => CSS_THEME,
      'weight' => 101,
    ),
    // Single stylesheet used to hack old internet explorer quirks.
    // Minimal support for deprecated breowsers is fine imo...
    'ie' => array(
      'file' => 'ie' . CELLULAR_CSS_EXT,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'group' => CSS_THEME,
      'weight' => 999,
    ),
  );
  // Add styles.
  cellular_add_css($styles);
  // Add JS Plugin CSS.
  cellular_add_css(cellular_plugins_css(), TRUE);
  // Add critical css inline if set.
  cellular_critical_css($vars);

  /* Additional assets for logged-in users */
  if (user_is_logged_in()) {
    // Add JS.
    drupal_add_js($cellular_theme_path . '/js/user.js', array());
    // Add CSS
    $user_style = array(
      'weight' => 999,
      'group' => CSS_THEME,
      'preprocess' => TRUE,
      'media' => 'all',
      'every_page' => TRUE,
      'browsers' => array('IE' => TRUE, '!IE' => TRUE)
    );
    drupal_add_css($cellular_theme_path . '/css/user.css', $user_style);
  }

  //dpm($vars);
}

/**
 * Add HTTP Response Headers.
 */
function cellular_http_headers() {
  // Try to prevent clickjacking.
  drupal_add_http_header('X-Frame-Options', 'DENY');
  // Set IE compatibility mode.
  drupal_add_http_header('X-UA-Compatible', 'IE=Edge');
}

/**
 * Set cookie for site, used to load additional resources if needed.
 */
function cellular_cookies() {
  if (theme_get_setting('cookie_time') == TRUE) {
    $cookie = variable_get('site_name', "Just another Drupal Site");
    $cookie = preg_replace("/[ \d]+/", '', strtolower($cookie)) . '98';

    setcookie($cookie, TRUE, time() + (86400 * theme_get_setting('cookie_time')));

    return !empty($_COOKIE[$cookie]) ? TRUE : FALSE;
  }
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

  // Check if google+ metatags are present, add emtpy string if not.
  if (!module_exists('metatag_google_plus')) {
    $vars['schemaorg'] = '';
  }
}

/**
 * Add variable classes to <body>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_body_attributes(&$vars, $visited) {
  $body_attributes = array();
  $path = drupal_get_path_alias();
  // Page URL is used to set id & classes of body.
  $aliases = explode('/', $path);
  // Set the current page as body id:
  $body_attributes['id'] = array_pop($aliases);
  // Add class for 1st-time visitors.
  $visited ? NULL : $body_attributes['class'][] = 'first-visit';
  // Add path-based classes.
  foreach ($aliases as $alias) {
    $body_attributes['class'][] = $alias;
  }
  // Sidebar class is generated if region is used on page.
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
