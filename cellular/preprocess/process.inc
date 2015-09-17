<?php
/**
 * @file
 * Cellular process functions.
 */

/**
 * Implements template_process_html().
 */
function cellular_process_html(&$vars) {
  // Add vars for critical scoped js
  $vars['critical_js'] = drupal_get_js('critical');
  // Get updated styles.
  $vars['styles'] = drupal_get_css();
   //dpm($vars);
}

/**
 * Implements template_process_page().
function cellular_process_page(&$vars) {
   //dpm($vars);
}
 */
