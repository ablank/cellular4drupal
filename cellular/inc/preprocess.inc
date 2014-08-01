<?php

/* * ************
  Cellular:: preprocess.inc

  Preprocess variables for templates

 * ************** */

/* * ************
  preprocess_html()

  Add <link> and <meta> tags, html/body attributes, conditional css
 * ************** */

function cellular_preprocess_html(&$vars) {
    global $language, $base_url;

// Set <HTML> attributes     
    $html_attributes = array(
        'lang' => $language->language,
        'dir' => $language->dir,
    );
    $vars['html_attributes'] = drupal_attributes($html_attributes);

// Add meta elements to $head
    $meta_tags = array(
        // robots
        'robots' => array(
            'type' => 'name',
            'attr_val' => 'robots',
            'content' => 'index, follow',
            'weight' => -999
        ),
        // viewport
        'viewport' => array(
            'type' => 'name',
            'attr_val' => 'viewport',
            'content' => 'width=device-width, initial-scale=1',
            'weight' => -999.1
        ),
        // IE rendering mode- set to lowest weight
        'ie_render_engine' => array(
            'type' => 'http-equiv',
            'attr_val' => 'X-UA-Compatible',
            'content' => 'IE=7; IE=8; IE=9; IE=Edge,chrome=1',
            'weight' => -999.2
        ),
    );

    cellular_build_head_tags($meta_tags);


// Add favicon & apple-touch-icons
// href is relative to the Icons folder
    $icons = array(
        'favicon-16x16' => array(
            'rel' => 'shortcut icon',
            'size' => null,
            'type' => 'image/x-icon',
            'href' => theme_get_setting('favicon'),
            'weight' => 95,
        ),
        'favicon-32x32' => array(
            'rel' => 'shortcut icon',
            'size' => '32x32',
            'type' => 'image/png',
            'href' => theme_get_setting('favicon_32'),
            'weight' => 96,
        ),
        // Older iOS devices don't understand the sizes attribute and use whichever value is last, so 'default' is given more weight.
        'apple-default' => array(
            'rel' => 'apple-touch-icon',
            'size' => null,
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
    cellular_favicon($icons, $vars);

// Add body classes
    $body_classes_array = array();

// Add sidebar class
    $body_classes_array[] = cellular_test_sidebar($vars);

    // Add body class based on URL alias
    $path = drupal_get_path_alias($_GET['q']);
    $aliases = explode('/', $path);

    foreach ($aliases as $alias) {
        $body_classes_array[] = $alias;
    }

    // Add body conditional classes
    $conditional_classes = array(
        'frontpage' => drupal_is_front_page() ? 'frontpage' : null,
        'user' => user_is_logged_in() ? 'user' : null,
    );

    foreach ($conditional_classes as $key => $val) {
        $body_classes_array[] = $val;
    }

    $vars['body_classes'] = cellular_merge($body_classes_array);

    // Add conditional CSS for IE9 and below.
    drupal_add_css(cellular_theme_path() . '/css/ie.css', array(
        'group' => CSS_THEME,
        'browsers' => array(
            'IE' => 'lt IE 10',
            '!IE' => FALSE
        ),
        'weight' => 999,
        'preprocess' => FALSE,
            )
    );
}

/* * ************
  preprocess_node()
 * ************** */

function cellular_preprocess_node(&$vars) {
    $vars['hook'] = 'node';
    $node = $vars['node'];

    $vars['title_attributes_array']['class'] = array(
        'node-title',
    );
    $vars['content_attributes_array']['class'] = array(
        'node-content',
    );


// Customize articles & blog posts
    if ($node->type == 'article' || 'blog') {
// Get $author info
        $uid = user_load($node->uid);
        $author = array(
            'name' => l($node->name, 'user/' . $node->uid),
            'description' => isset($author->field_description['und'][0]['safe_value']) ?
                    '<div class="author-description">' . $uid->field_description['und'][0]['safe_value'] . '</div>' : null,
            'image' => !empty($uid->picture->uri) ?
                    theme_image_style(array(
                        //'style_name' => 'blog-author-image',
                        'path' => $node->picture->uri,
                        'width' => null,
                        'height' => null,
                        'alt' => t('User .') . $node->name,
                        'title' => t('User ') . $node->name,
                        'attributes' => array('class' => 'author-image'),
                    )) : null,
        );

// Return $author
        $vars['author'] = $author['image'] . $author['name'] . $author['description'];
    }
}

/* * ************
  preprocess_page()

  Set vars for page.tpl
 * ************** */

function cellular_preprocess_page(&$vars) {
    // Link site name to frontpage
    $vars['site_name'] = l($vars['site_name'], '<front>');

    // Set main_menu as full-tree or top-level as defined in settings
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

    // Set Social Media links
    $vars['social_media_share'] = cellular_social_media_share();
    $vars['social_media_follow'] = cellular_social_media_follow();

    // Set copyright if provided 
    $copyright = theme_get_setting('copyright');
    $vars['copyright'] = isset($copyright) ?
            "&copy; " . date("Y") . " " . $copyright : null;

    // Set custom page templates for CCK Content (page--content-type.tpl.php)
    if (isset($vars['node']->type)) {
        $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
    }

    // Set search block for addition to templates
    $search_box = drupal_get_form('search_form');
    $vars['search_box'] = $search_box;

    // Set custom error template
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

                cellular_merge($vars['classes_array']);
                break;
        }
    }
}

/* * ************
  preprocess_region()
 * ************** */

function cellular_preprocess_region(&$vars) {
    /*

     */
}

/* * ************
  preprocess_block()
 * ************** */

function cellular_preprocess_block(&$vars) {
    $vars['hook'] = 'block';
    $block = $vars['block'];
    $vars['title'] = isset($block->subject) ? $block->subject : null;

    $vars['classes_array'] = array(
        'block',
    );
    $vars['title_attributes_array']['class'] = array(
        'block-title',
    );
    $vars['content_attributes_array']['class'] = array(
        'block-content',
    );
    // 
    if ($block->module == 'menu') {
        $block->content = str_replace('class="menu"', 'class="menu myclass"', $block->content);
    }

    // Hide block titles in the headers region.
    if (($block->region == 'header')
    //|| ($block->region == 'header_top')
    //|| ($block->region == 'header_bottom')
    ) {
        $vars['title_attributes_array']['class'] = array('hidden');
    }
}

/* * ************
  preprocess_comment()
 * ************** */

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

/* * ************
  preprocess_username()
 * ************** */

function cellular_preprocess_username(&$vars) {
    if (isset($vars['link_path'])) {
        $vars['link_attributes']['rel'][] = 'author';
    } else {
        $vars['attributes_array']['rel'][] = 'author';
    }
}
