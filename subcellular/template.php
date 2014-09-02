<?php

/**
 * @file
 * Set global vars, load functions for templates, and hook_function overrides.
 * @author Adam Blankenship
 */

/**/
global $theme_path;
$include = array(
  // 'dev-functions.inc',
  'css_alter.inc',
  'js_alter.inc',
);

$inc_path = $theme_path . '/inc';
foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

/**
 * template_preprocess_page()
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
 * template_preprocess_html()
 */
function subcellular_preprocess_html(&$vars) {

}

/**
 * template_preprocess_node()
 */
function subcellular_preprocess_node(&$vars) {

}

/**
 * template_preprocess_region()
 */
function subcellular_preprocess_region(&$vars) {

}

/**
 * template_preprocess_block()
 */
function subcellular_preprocess_block(&$vars) {

}

/**
 * template_preprocess_comment()
 */
function subcellular_preprocess_comment(&$vars) {

}
