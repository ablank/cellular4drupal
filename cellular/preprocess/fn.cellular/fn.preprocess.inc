<?php
/**
 * @file
 * Cellular functions to set content attributes.
 */

/**
 * Set html attributes.
 */
function cellular_html_attributes(&$vars) {
  global $language;
  $html_attributes = array(
    'lang' => $language->language,
    'xml:lang' => $language->language,
    'dir' => $language->dir,
  );
  // Check support for RDF & add DOCTYPE:
  if (module_exists('rdf')) {
    // Set RDFa namespace.
    $html_attributes['xmlns'] = 'http://www.w3.org/1999/xhtml';
  }

  $vars['doctype'] = "<!DOCTYPE html>\n";
  $vars['html_attributes'] = drupal_attributes($html_attributes);
}

/**
 * Convert @xmlns to @profile.
 */
function cellular_rdf(&$vars) {
  // More info @ http://phase2technology.com/?p=552
  // Check support for RDF & add DOCTYPE:
  if (module_exists('rdf')) {

    $head_attributes = array();
    $prefixes = array();
    $namespaces = explode("\n", trim($vars['rdf_namespaces']));

    foreach ($namespaces as $name) {
      list($key, $url) = explode('=', $name, 2);
      list($xml, $space) = explode(':', $key, 2);

      $url = trim(str_replace('"', '', $url));
      $prefixes[] = $space . ": " . $url . "\n";
    }
    $head_attributes['prefix'] = implode(' ', $prefixes);

    $vars['rdf_prefixes'] = drupal_attributes($head_attributes);
  }
}

/**
 * Add variable classes to <body>.
 */
function cellular_body_attributes(&$vars) {
  $body_attributes = array();
  $path = drupal_get_path_alias($_GET['q']);
  $aliases = explode('/', $path);

  $body_attributes['id'] = str_replace(' ', '_', $vars['head_title']);
  // Add URL alias based body classes.
  // i.e. http://host.com/content/widget
  // = <body class="content widget">
  foreach ($aliases as $alias) {
    $body_attributes['class'][] = $alias;
  }

// Sidebar class is generated if region is used on page.
  $body_attributes['class'][] = cellular_test_sidebar($vars);
  drupal_is_front_page() ?
      $body_attributes['class'][] = 'frontpage' : NULL;
  user_is_logged_in() ?
      $body_attributes['class'][] = 'user' : NULL;

  $vars['body_attributes'] = drupal_attributes($body_attributes);
}

/**
 * Build links to favicons & apple-touch-icons.
 */
function cellular_favicons() {
  $favicons = array(
    'favicon-16x16' => array(
      'rel' => 'shortcut icon',
      'type' => 'image/x-icon',
      'size' => NULL,
      'href' => theme_get_setting('favicon'),
      'weight' => 95,
    ),
    'favicon-32x32' => array(
      'rel' => 'shortcut icon',
      'type' => 'image/png',
      'size' => '32x32',
      'href' => theme_get_setting('favicon_32'),
      'weight' => 96,
    ),
    /* Older iOS devices don't understand the sizes attribute and use
     * whichever value is last, so 'default' is given more weight.
     */
    'apple-default' => array(
      'rel' => 'apple-touch-icon',
      'size' => NULL,
      'href' => theme_get_setting('apple_icon_57'),
      'weight' => 100,
    ),
    'apple-72x72' => array(
      'rel' => 'apple-touch-icon',
      'size' => '72x72',
      'href' => theme_get_setting('apple_icon_72'),
      'weight' => 99,
    ),
    'apple-114x114' => array(
      'rel' => 'apple-touch-icon',
      'size' => '114x114',
      'href' => theme_get_setting('apple_icon_114'),
      'weight' => 98,
    ),
    'apple-144x144' => array(
      'rel' => 'apple-touch-icon',
      'size' => '144x144',
      'href' => theme_get_setting('apple_icon_144'),
      'weight' => 97,
    ),
  );

  foreach ($favicons as &$favicon) {
// Set tag type to <link>
    $favicon['tag'] = 'link';
// Set href relative to /assets/favicons/
    $favicon['href'] = path_to_theme() . '/assets/favicons/' . $favicon['href'];
  }

  cellular_build_head_tags($favicons);
}

/**
 * Add meta tags to <head>.
 */
function cellular_metatags(&$vars) {
  $meta_tags = array(
    'viewport' => array(
      'tag' => 'meta',
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
      'weight' => 0,
    ),
    'ie_render_engine' => array(
      'tag' => 'meta',
      'attr' => 'http-equiv',
      'attr_val' => 'X-UA-Compatible',
      'content' => 'IE=Edge,chrome=1',
      'weight' => 1,
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
    'grddl' => isset($vars['grddl_profile']) ? array(
      'tag' => 'link',
      'rel' => 'profile',
      'href' => $vars['grddl_profile'],
      'weight' => 4,
      ) : NULL,
  );

  cellular_build_head_tags($meta_tags);
}

/**
 * Test if sidebar regions are used and return the appropriate class.
 */
function cellular_test_sidebar(&$vars) {
  $sidebar_left = !empty($vars['page']['sidebar_left']) ?
    1 : NULL;
  $sidebar_right = !empty($vars['page']['sidebar_right']) ?
    1 : NULL;

  if (isset($sidebar_left) && isset($sidebar_right)) {
    return 'dual-sidebars';
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
    return 'single-sidebar';
  }
  else {
    return 'no-sidebars';
  }
}

/**
 * Add appropriate classes for sidebars.
 */
function cellular_sidebar_classes(&$vars) {
  $test = cellular_test_sidebar($vars);
  if ($test === 'dual-sidebars') {
    $vars['page']['content_class'] = theme_get_setting('content_class_dual_sidebars');
    $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_dual_sidebars');
  }
  elseif ($test === 'single-sidebar') {
    $vars['page']['content_class'] = theme_get_setting('content_class_single_sidebar');
    $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_single_sidebar');
  }
  else {
    $vars['page']['content_class'] = theme_get_setting('content_class_no_sidebars');
  }

  return $vars;
}

/**
 * Remove core stylesheets based on theme settings.
 */
function cellular_remove_default_css(&$css) {
  // Nuke all css not a member of group CSS_THEME:
  $exclude = array();
  if (theme_get_setting('remove_drupal_css') === 'theme_only') {
    foreach ($css as $key => $value) {
      if ($value['group'] !== CSS_THEME
        // Keep admin stuff.
        && ($key !== 'admin_menu' || $key !== 'toolbar')
      ) {
        $exclude[$key] = FALSE;
      }
    }
  }

// Nuke all SYSTEM css.
  if (theme_get_setting('remove_drupal_css') === 'system') {
    foreach ($css as $key => $value) {
      if ($value['group'] == CSS_SYSTEM) {
        $exclude[$key] = TRUE;
      }
    }
  }

// Remove Drupal css generated by modules.
  if (theme_get_setting('remove_drupal_css') === 'select') {
// Select module css to exclude.
    $exclude = array(
      'system' => array(
        'system.base.css',
        'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block' => 'block.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'menu' => 'menu.css',
      'node' => 'node.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );
  }

  cellular_remove_css($css, $exclude);
}

/**
 * Set content author attributes.
 */
function cellular_set_author(&$vars) {
  $node = $vars['elements']['#node'];
  $uid = user_load($node->uid);
  $safe_value = "['LANGUAGE_NONE'][0]['safe_value']";
  $author = array(
    'name' => l($node->name, 'user/' . $node->uid),
    'description' => isset($author->field_description[$safe_value]) ?
      '<div class="author-description">' . $uid->field_description[$safe_value] . '</div>' : NULL,
    'image' => !empty($uid->picture->uri) ? theme('image_style', array(
        // 'style_name' => 'blog-author-image',
        'path' => $node->picture->uri,
        'width' => NULL,
        'height' => NULL,
        'alt' => t('User') . ' ' . $node->name,
        'title' => t('User') . ' ' . $node->name,
        'attributes' => array('class' => 'author-image'),
      )) : NULL,
  );

  $vars['author'] = $author['image'] . $author['name'] . $author['description'];
}
