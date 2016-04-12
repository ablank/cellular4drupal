<?php

/**
 * @file
 * Node preprocess functions.
 */

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
  // Set default template suggestions.
  //$vars['theme_hook_suggestions'][] = 'node__' . $vars['type'];
  // Set custom template suggestions.
  switch ($vars['node']->type) {
    case 'forum':
      $vars['theme_hook_suggestions'][] = 'forum_post';
      //$vars['theme_hook_suggestions'] = array('forum_post');
      //$vars['theme_hook_suggestion'] = 'forum_post';
      break;
  }
  /**/
}
