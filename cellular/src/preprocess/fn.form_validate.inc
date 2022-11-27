<?php

/**
 * @file
 * Cellular form validation.
function cellular_form_validate($form, &$form_state) {
 // dpm($form);
}
 */

/*
 *
function webform_client_form_validate($form, &$form_state) {
  $node = node_load($form_state['values']['details']['nid']);
  $finished = $form_state['values']['details']['finished'];

  // Check that the submissions have not exceeded the total submission limit.
  if ($node->webform['total_submit_limit'] != -1) {
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    // Check if the total number of entries was reached before the user submitted
    // the form.
    if (!$finished && $total_limit_exceeded = _webform_submission_total_limit_check($node)) {
      // Show the user the limit has exceeded.
      theme('webform_view_messages', array('node' => $node, 'teaser' => 0, 'page' => 1, 'submission_count' => 0, 'total_limit_exceeded' => $total_limit_exceeded, 'allowed_roles' => array_keys(user_roles()), 'closed' => FALSE, 'cached' => FALSE));
      form_set_error('', NULL);
      return;
    }
  }

  // Check that the user has not exceeded the submission limit.
  // This usually will only apply to anonymous users when the page cache is
  // enabled, because they may submit the form even if they do not have access.
  if ($node->webform['submit_limit'] != -1) { // -1: Submissions are never throttled.
    module_load_include('inc', 'webform', 'includes/webform.submissions');

    if (!$finished && $user_limit_exceeded = _webform_submission_user_limit_check($node)) {
      // Assume that webform_view_messages will print out the necessary message,
      // then stop the processing of the form with an empty form error.
      theme('webform_view_messages', array('node' => $node, 'teaser' => 0, 'page' => 1, 'submission_count' => 0, 'user_limit_exceeded' => $user_limit_exceeded, 'allowed_roles' => array_keys(user_roles()), 'closed' => FALSE, 'cached' => FALSE));
      form_set_error('', NULL);
      return;
    }
  }

  // Run all #element_validate and #required checks. These are skipped initially
  // by setting #validated = TRUE on all components when they are added.
  _webform_client_form_validate($form, $form_state);
}

 */