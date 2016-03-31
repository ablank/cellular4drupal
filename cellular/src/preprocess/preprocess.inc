<?php
/**
 * @file
 * Template preprocess functions.
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

/*
    $cookie = variable_get('site_name', "Just another Drupal Site");
    $cookie .='-visited';
    $cookie = trim($cookie, '=,; \t\r\n\013\014');
    setcookie($cookie, 'TRUE', time() + (86400 * 30), '/');

    if (isset($_COOKIE[$cookie])) {
    drupal_set_message("OK, Cookie: ' " . $_COOKIE[$cookie] . " ' set!");
    }
 */
  //dpm($vars);
}

/**
 * Implements template_preprocess_node().
 */
function cellular_preprocess_node(&$vars) {
  $node = $vars['elements']['#node'];
  // Set attributes.
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

  // dpm($node);
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
    $submitted .= '<div>' . t('Posted by !username', array(
      '!username' => $vars['author'],
    )) . '</div>';
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
