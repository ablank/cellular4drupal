<?php
/**
 * @file
 * Preprocess functions for Views.
 */

/**
 * Set hooks for view preprocess functions.
 *
 * @param type $vars
 */
function cellular_preprocess_views_view(&$vars) {
  if (isset($vars['view']->name)) {
    $function = 'cellular_preprocess_views_view__'.$vars['view']->name;
    if (function_exists($function)) {
     $function($vars);
    }
  }
} 