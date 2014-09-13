<?php
/**
 * @file
 * Cellular process functions.
 */

/**
 * Cellular template_process_html().
 */
function cellular_process_html(&$vars) {
  // Push modified styles to page.
  $vars['styles'] = drupal_get_css();
}

/**
 * Cellular template_process_page().
 */
function cellular_process_page(&$vars){
  // Dev.
  cellular_dev($vars);
}
