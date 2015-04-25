<?php
/**
 * @file
 * Alter misc. hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 *
 * @param array $head_elements
 *   Associative array of variables to merge with defaults from theme registry.
 */
function cellular_html_head_alter(array &$head_elements) {
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
 * Implements hook_page_alter().
 *
 * @param array $page
 *   Associative array of variables to merge with defaults from theme registry.
 */
function cellular_page_alter(array &$page) {
  // cellular_dev($page);
}
