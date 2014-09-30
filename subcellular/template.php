<?php
/**
 * @file
 * Set global vars, load functions for templates, and hook_function overrides.
 * @author Adam Blankenship
 */

$inc_path = drupal_get_path('theme', 'subcellular') . '/inc';
$include = array(
  'alter.css.inc',
  'alter.js.inc',
);

foreach ($include as $i) {
  require_once ($inc_path . '/' . $i);
}

/**
 * Subcellular template_preprocess_page().
 */
function subcellular_preprocess_page(&$vars) {

  // Do something with content type.
  if (isset($vars['node']) && $vars['node']->type == 'page') {

  }

  // Do something with specific node.
  if (isset($vars['node']) && $vars['node']->nid === '40') {
    // Do things:
  };
}

/**
 * Subcellular template_preprocess_html().
 */
function subcellular_preprocess_html(&$vars) {

}

/**
 * Subcellular template_preprocess_node().
 */
function subcellular_preprocess_node(&$vars) {

}

/**
 * Subcellular template_preprocess_region().
 */
function subcellular_preprocess_region(&$vars) {

}

/**
 * Subcellular template_preprocess_block().
 */
function subcellular_preprocess_block(&$vars) {

}

/**
 * Subcellular template_preprocess_comment().
 */
function subcellular_preprocess_comment(&$vars) {

}
