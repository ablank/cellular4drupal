<?php
/**
 * @file
 *
 */

/**
 * Cellular template_process_html().
 */
function cellular_process_html(&$vars) {
  // Push modified styles to page.
  $vars['styles'] = drupal_get_css();
}

/**
 *
 */
function cellular_process_page(&$vars){
  // Dev.
  //cellular_dev($vars);
}
