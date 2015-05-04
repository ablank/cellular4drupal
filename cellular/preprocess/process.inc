<?php
/**
 * @file
 * Cellular process functions.
 */

/**
 * Implements template_process_html().
 */
function cellular_process_html(&$vars) {
  // Push modified styles to page.
 // $vars['styles'] = drupal_get_css($vars['css'], FALSE);
}

/**
 * Implements template_process_page().
 */
function cellular_process_page(&$vars) {
  // Dev.
  cellular_dev($vars);
}
