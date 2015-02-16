<?php
/**
 * @file
 * Set global vars, load functions for templates, and hook_function overrides.
 * @author Adam Blankenship
 */

$inc_path = drupal_get_path('theme', 'singularity') . '/inc';
$include = array(
  'alter.css.inc',
  'alter.js.inc',
);

foreach ($include as $i) {
  require_once ($inc_path . '/' . $i);
}

/**
 * singularity template_preprocess_page().
 */
function singularity_preprocess_page(&$vars) {

  // Do something with content type.
  /*
    if (isset($vars['node']) && $vars['node']->type == 'page') {

    }
   */

  // Do something with specific node.
  /*
    if (isset($vars['node']) && $vars['node']->nid === '40') {
    // Do things:
    };
   */
}

/**
 * singularity template_preprocess_html().
 */
function singularity_preprocess_html(&$vars) {

}

/**
 * singularity template_preprocess_node().
 */
function singularity_preprocess_node(&$vars) {

}

/**
 * singularity template_preprocess_region().
 */
function singularity_preprocess_region(&$vars) {

}

/**
 * singularity template_preprocess_block().
 */
function singularity_preprocess_block(&$vars) {

}

/**
 * singularity template_preprocess_comment().
 */
function singularity_preprocess_comment(&$vars) {

}
