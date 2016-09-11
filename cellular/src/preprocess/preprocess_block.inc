<?php
/**
 * @file
 * Block preprocess functions.
 */

/**
 * Implements template_preprocess_block().
 */
function cellular_preprocess_block(&$vars) {
  $block = $vars['elements']['#block'];
  // Hide block titles in the header regions.
  switch ($block->region) {
    case 'header':
    case 'header-top':
    case 'header-bottom':
      $vars['title_attributes']['class'][] = 'element-invisible';

      break;
  }
}
