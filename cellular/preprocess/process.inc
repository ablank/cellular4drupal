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
  //$vars['styles'] = drupal_get_css();
  $vars['critical_js'] = drupal_get_js('critical');
   //dpm($vars);
}

/**
 * Implements template_process_page().
 */
function cellular_process_page(&$vars) {
   //dpm($vars);
}
