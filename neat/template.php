<?php
/**
 * @file
 * Set global vars, load functions for templates, and hook_function overrides.
 * @author Adam Blankenship
 */

$inc_path = drupal_get_path('theme', 'neat') . '/inc';
$include = array(
  'alter.css.inc',
  'alter.js.inc',
);

foreach ($include as $i) {
  require_once ($inc_path . '/' . $i);
}

/**
 * neat template_preprocess_page().
 */
function neat_preprocess_page(&$vars) {

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
 * neat template_preprocess_html().
 */
function neat_preprocess_html(&$vars) {

}

/**
 * neat template_preprocess_node().
 */
function neat_preprocess_node(&$vars) {

}

/**
 * neat template_preprocess_region().
 */
function neat_preprocess_region(&$vars) {

}

/**
 * neat template_preprocess_block().
 */
function neat_preprocess_block(&$vars) {

}

/**
 * neat template_preprocess_comment().
 */
function neat_preprocess_comment(&$vars) {

}
