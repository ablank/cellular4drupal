<?php

/**
 * @file
 * Alter miscellaneous hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 * Remove unwanted meta tags.
 */
function cellular_html_head_alter(&$head_elements) {
  unset($head_elements['system_meta_generator']);
}
