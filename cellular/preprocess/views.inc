<?php
/**
 * @file
 * Preprocess functions for Views.
 */

/**
 * Implements template_preprocess_views_view().
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_views_view(&$vars) {
  // Set hooks for view preprocess functions.
  if (isset($vars['view']->name)) {
    $function = 'cellular_preprocess_views_view__' . $vars['view']->name;
    if (function_exists($function)) {
      $function($vars);
    }
  }
}
