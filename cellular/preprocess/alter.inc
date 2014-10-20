<?php

/**
 * @file
 * Alter misc. hooks for templates.
 */

/**
 * Cellular hook_html_head_alter().
 */
function cellular_html_head_alter(&$head_elements) {
  // Remove unwanted meta tags.
  $exclude = array('metatag_generator');

  foreach ($exclude as $element) {
    if (isset($head_elements[$element])) {
      unset($head_elements[$element]);
    }
  }
  // cellular_dev($head_elements);
}

/**
 * Cellular hook_page_alter().
 */
function cellular_page_alter(&$page) {
  // cellular_dev($page);
}
