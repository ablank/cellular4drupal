<?php

/**
 * @file
 *  Cellular comment preprocess functions.
 */

/**
 * Implements template_preprocess_comment_wrapper().
 */
function cellular_preprocess_comment_wrapper(&$vars) {

  $vars['theme_hook_suggestions'][] = 'comment_wrapper';
  $vars['theme_hook_suggestions'][] = 'comment_wrapper__' . $vars['node']->type;
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Implements template_preprocess_comment().
 */
function cellular_preprocess_comment(&$vars) {
  $comment = $vars ['elements']['#comment'];
  //dpm($comment);
  // Set the template used by comments.
  $vars['theme_hook_suggestions'][] = 'comment';
  $vars['theme_hook_suggestions'][] = 'comment__' . $vars['node']->type;
  $vars['title_attributes_array']['class'][] = 'comment-title';
  $vars['content_attributes_array']['class'][] = 'comment-content';

  switch ($vars['node']->type) {
    case 'forum':
      cellular_preprocess_forum_reply($vars);
      break;
  }

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

function cellular_preprocess_forum_reply(&$vars) {

}
