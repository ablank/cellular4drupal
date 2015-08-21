<?php
/**
 * @file
 * Template preprocess variables.
 */

/**
 * Implements template_preprocess_html().
 */
function cellular_preprocess_html(&$vars) {
  cellular_http_headers();
  cellular_html_attributes($vars);
  cellular_rdf($vars);
  cellular_metatags($vars);
  cellular_favicons();
  cellular_body_attributes($vars);
}

/**
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars) {
  // Add critical css inline if set.
  cellular_critical_css($vars);
  // Set main_menu as full-tree or top-level as defined in settings.
  cellular_main_menu($vars);
  // Set classes for content & sidebar regions.
  cellular_test_sidebar($vars);
  // Link site name to frontpage.
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set Social Media links.
  $vars['page']['social_media_share'] = cellular_social_media_share();
  $vars['page']['social_media_follow'] = cellular_social_media_follow();
  // Set search block variable for addition to page templates.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright info if provided.
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ?
  "&copy; " . date("Y") . " $copyright" : '';
  // Automate error pages.
  cellular_error_page($vars);

  /* Work in progress... */
  // Add template suggestion for custom content types(page--content-type.tpl.php)
  if (isset($vars['node']->type)) {
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }
  // Panels everywhere page template suggestion.
  if (!empty(variable_get('panels_everywhere_site_template'))) {
    $vars['theme_hook_suggestions'][] = 'page__panels_everywhere';
  }
}

/**
 * Implements template_preprocess_node().
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];
  // Set attributes
  $vars['title_attributes_array']['class'][] = 'node-title';
  $vars['content_attributes_array']['class'][] = 'node-content';
  /* Set additional template variables. */
  // Date node was created.
  $date = "\n<span class=\"day\">" . date("j", $node->created) . "</span>\n";
  $date .= "<span class=\"month\">" . date("M", $node->created) . "</span>\n";
  $date .= "<span class=\"year\">" . date("Y", $node->created) . "</span>\n";
  // Author info
  $aid = user_load($vars['uid']);
  $author = theme('user_picture', array('account' => $aid));
  $author .= $aid->name;

  // Push variables to the node array.
  $vars['post_date'] = $date;
  $vars['author'] = $author;
}

/**
 * Implements template_preprocess_block().
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  // Hide block titles in the header regions.
  switch ($block->region) {
    case 'header':
    case 'header-top':
    case 'header-bottom':
      $vars['title_attributes']['class'][] = 'element-invisible';

      break;
  }
}

/**
 * Implements template_preprocess_comment().
 */
function cellular_preprocess_comment(&$vars) {
  $comment = $vars ['elements']['#comment'];
  //dpm($comment);
  // Set the template used by comments.
  $vars['theme_hook_suggestions'][] = 'comment';
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';
  $vars['content_attributes_array']['class'][] = 'clearfix';

  if (!empty($vars['new'])) {
    $vars['classes_array'][] = 'new';
  }
  $submitted = '';
  if (!empty($vars['author'])) {
    $submitted .= '<span class="comment-author">';
    $submitted .= $vars['picture'];
    $submitted .= '<div>'.t('Posted by !username', array(
      '!username' => $vars['author'],
    )).'</div>';
    $submitted .= '</span>';
  }

  $submitted .= '<span class="comment-date">' . $vars['created'] . '</span>';

  // No need to link comments...
  $vars['title'] = $comment->subject;

  $vars['submitted'] = $submitted;
}

/**
 * Implements template_preprocess_comment_wrapper.
 */
function cellular_preprocess_comment_wrapper(&$vars) {
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Implements template_preprocess_maintenance_page().
 *
 * Duplicate page variables for the maintenance page.
 */
function cellular_preprocess_maintenance_page(&$vars) {
  // Set main_menu as full-tree or top-level as defined in settings:
  cellular_main_menu($vars);
  // Set classes for content & sidebars.
  cellular_test_sidebar($vars);
  // Use page--error.tpl if http error status is returned.
  cellular_error_page($vars);

  // Link site name to frontpage:
  $vars['site_name'] = l($vars['site_name'], '<front>');
  // Set search block variable for addition to template.
  $vars['page']['search_box'] = drupal_get_form('search_form');
  // Set copyright if provided:
  $copyright = theme_get_setting('copyright');
  $vars['page']['copyright'] = !empty($copyright) ? "&copy; " . date("Y") . " $copyright" : '';
}
