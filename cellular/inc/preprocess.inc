<?php

/**
 * @file
 * Template preprocess variables.
 */

/**
 * template_preprocess_html()
 */
function cellular_preprocess_html(&$vars) {
  global $language, $base_url, $theme_path;

  // Check support for RDF & addDOCTYPE:
  if (module_exists('rdf')) {
    $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
    $vars['rdf_version'] = ' version="HTML+RDFa 1.1"';
    $vars['rdf_profile'] = ' profile="' . $vars['grddl_profile'] . '"';
  }
  else {
    $vars['doctype'] = "<!DOCTYPE html>\n";
    $vars['rdf_version'] = '';
    $vars['rdf_profile'] = '';
  }

  // Set <HTML> attributes:
  $html_attributes = array(
    'lang' => $language->language,
    'dir'  => $language->dir,
  );
  $vars['html_attributes'] = drupal_attributes($html_attributes);

// Add meta tags to <head>:
  $meta_tags = array(
    'viewport'         => array(
      'tag'     => 'meta',
      'name'    => 'viewport',
      'content' => 'width=device-width, initial-scale=1',
      'weight'  => 0,
    ),
    'ie_render_engine' => array(
      'tag'      => 'meta',
      'attr'     => 'http-equiv',
      'attr_val' => 'X-UA-Compatible',
      'content'  => 'IE=Edge,chrome=1',
      'weight'   => 1,
    ),
    'robots'           => array(
      'tag'     => 'meta',
      'name'    => 'robots',
      'content' => 'index, follow',
      'weight'  => 2,
    ),
    'humans'           => array(
      'tag'    => 'link',
      'type'   => 'text/plain',
      'rel'    => 'author',
      'href'   => $base_url . '/humans.txt',
      'weight' => 3,
    ),
    'grddl'            => !empty($vars['grddl_profile']) ? array(
        'tag'    => 'link',
        'rel'    => 'profile',
        'href'   => $vars['grddl_profile'],
        'weight' => 4,
      ) : NULL,
  );

  cellular_build_head_tags($meta_tags);

// Add favicon & apple-touch-icons:
  $favicons = array(
    'favicon-16x16' => array(
      'rel'    => 'shortcut icon',
      'type'   => 'image/x-icon',
      'size'   => NULL,
      'href'   => theme_get_setting('favicon'),
      'weight' => 95,
    ),
    'favicon-32x32' => array(
      'rel'    => 'shortcut icon',
      'type'   => 'image/png',
      'size'   => '32x32',
      'href'   => theme_get_setting('favicon_32'),
      'weight' => 96,
    ),
    /* Older iOS devices don't understand the sizes attribute and use
     * whichever value is last, so 'default' is given more weight.
     */
    'apple-default' => array(
      'rel'    => 'apple-touch-icon',
      'size'   => NULL,
      'href'   => theme_get_setting('apple_icon_57'),
      'weight' => 100,
    ),
    'apple-72x72'   => array(
      'rel'    => 'apple-touch-icon',
      'size'   => '72x72',
      'href'   => theme_get_setting('apple_icon_72'),
      'weight' => 99,
    ),
    'apple-114x114' => array(
      'rel'    => 'apple-touch-icon',
      'size'   => '114x114',
      'href'   => theme_get_setting('apple_icon_114'),
      'weight' => 98,
    ),
    'apple-144x144' => array(
      'rel'    => 'apple-touch-icon',
      'size'   => '144x144',
      'href'   => theme_get_setting('apple_icon_144'),
      'weight' => 97,
    ),
  );

  foreach ($favicons as &$favicon) {
// Set tag type to <link>
    $favicon['tag'] = 'link';
// Set href relative to /assets/favicons/
    $favicon['href'] = $theme_path . '/assets/favicons/' . $favicon['href'];
  }

  cellular_build_head_tags($favicons);

// Add classes to <body>
  $body_classes_array = array();
// Sidebar class is generated if region is used on page.
  $body_classes_array[] = cellular_test_sidebar($vars);

  // Add URL alias based body classes.
  // i.e. http://host.com/content/widget
  // = <body class="content widget">
  $path = drupal_get_path_alias($_GET['q']);
  $aliases = explode('/', $path);

  foreach ($aliases as $alias) {
    $body_classes_array[] = $alias;
  }

  // Add other body conditional classes:
  $conditional_classes = array(
    'frontpage' => drupal_is_front_page() ? 'frontpage' : NULL,
    'user'      => user_is_logged_in() ? 'user' : NULL,
  );

  foreach ($conditional_classes as $key => $val) {
    $body_classes_array[] = $val;
  }

  $vars['body_classes'] = cellular_merge($body_classes_array);

  // Add conditional CSS for old IE.
  // Minimal support for deprecated breowsers is fine imo,
  // considering MS doesn't support it either...
  drupal_add_css($theme_path . '/css/ie.css', array(
    'group'      => CSS_THEME,
    'browsers'   => array('IE' => 'lt IE 10', '!IE' => FALSE),
    'weight'     => 999,
    'preprocess' => FALSE,
  ));

}

/**
 * template_preprocess_node()
 */
function cellular_preprocess_node(&$vars) {
  $vars['hook'] = 'node';
  $node = $vars['node'];

  $vars['title_attributes_array']['class'] = array('node-title');
  $vars['content_attributes_array']['class'] = array('node-content');

// Customize articles & blog posts:
  if ($node->type == 'article' || 'blog') {
// Get $author info:
    $uid = user_load($node->uid);
    $safe_value = "['LANGUAGE_NONE'][0]['safe_value']";
    $author = array(
      'name'        => l($node->name, 'user/' . $node->uid),
      'description' => isset($author->field_description[$safe_value]) ?
          '<div class="author-description">' . $uid->field_description[$safe_value] . '</div>' : NULL,
      'image'       => !empty($uid->picture->uri) ? theme('image_style', array(
          // 'style_name' => 'blog-author-image',
          'path'       => $node->picture->uri,
          'width'      => NULL,
          'height'     => NULL,
          'alt'        => t('User') . ' ' . $node->name,
          'title'      => t('User') . ' ' . $node->name,
          'attributes' => array('class' => 'author-image'),
        )) : NULL,
    );

// Return $author:
    $vars['author'] = $author['image'] . $author['name'] . $author['description'];
  }

}

/**
 * template_preprocess_page()
 */
function cellular_preprocess_page(&$vars) {
  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');

  // Set main_menu as full-tree or top-level as defined in settings:
  $vars['main_menu'] = cellular_main_menu($vars);

  switch (cellular_test_sidebar($vars)) {
    case "dual-sidebars":
      $vars['content_class'] = theme_get_setting('content_class_dual_sidebars');
      $vars['sidebar_class'] = theme_get_setting('sidebar_class_dual_sidebars');
      break;

    case "single-sidebar":
      $vars['content_class'] = theme_get_setting('content_class_single_sidebar');
      $vars['sidebar_class'] = theme_get_setting('sidebar_class_single_sidebar');
      break;

    case "no-sidebars":
      $vars['content_class'] = theme_get_setting('content_class_no_sidebars');
      break;
  }

  // Set Social Media links:
  $vars['social_media_share'] = cellular_social_media_share();
  $vars['social_media_follow'] = cellular_social_media_follow();

  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['copyright'] = isset($copyright) ? "&copy; " . date("Y") . " " . $copyright : NULL;

  // Set custom page templates for CCK Content (page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }

  // Set search block variable for addition to templates:
  $search_box = drupal_get_form('search_form');
  $vars['search_box'] = $search_box;

  // Set custom error template:
  $http_status = drupal_get_http_header("status");

  if (isset($http_status)) {

    switch ($http_status) {
      case

      "403 Forbidden":
      case "404 Not Found":
      case "500 Internal Server Error":
        $vars['theme_hook_suggestions'][] = 'page__error';
        $vars['http_status'] = "Error: " . $http_status;
        $vars['error_message'] = drupal_get_messages();
        $vars['classes_array'][] = 'page-error';

        cellular_merge($vars['classes_array']);
        break;
    }
  }

}

/**
 * template_preprocess_region()
 */
function cellular_preprocess_region(&$vars) {

}

/**
 * template_preprocess_block()
 */
function cellular_preprocess_block(&$vars) {
  $vars['hook'] = 'block';
  $block = $vars['block'];
  $vars['title'] = isset($block->subject) ? $block->subject : NULL;

  $vars['classes_array'] = array('block');
  $vars['title_attributes_array'] ['class'] = array('block-title');
  $vars['content_attributes_array']['class'] = array('block-content');

  // Hide block titles in the headers region:
  if (($block->region == 'header')
    // || ($block->region == 'header_top')
    // || ($block->region == 'header_bottom')
  ) {
    $vars['title_attributes_array']['class'] = array('hidden');
  }

}

/**
 * template_preprocess_comment()
 */
function cellular_preprocess_comment(&$vars) {
  $vars['hook'] = 'comment';

  $vars['title_attributes_array']['class'] = array('comment-title');
  $vars['content_attributes_array']['class'] = array('comment-content');

  $vars['submitted'] = t('Submitted by !username on !datetime', array(
    '!username' => $vars['author'],
    '!datetime' => $vars['created'],
  ));

  $vars['comment_wrapper'] = FALSE;

}

/**
 * template_ preprocess_username()
 */
function cellular_preprocess_username(&$vars) {
  if (isset($vars['link_path'])) {
    $vars['link_attributes']['rel'][] = 'author';
  }
  else {
    $vars['attributes_array']['rel'][] = 'author';
  }

}
