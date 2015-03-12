<?php
/**
 * @file
 * Preprocess functions for Views.
 */

/**
 * Set hooks for view preprocess functions.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_views_view(array &$vars) {
  if (isset($vars['view']->name)) {
    $function = 'cellular_preprocess_views_view__' . $vars['view']->name;
    if (function_exists($function)) {
      $function($vars);
    }
  }
}
