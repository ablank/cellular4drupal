<?php
/**
 * @file
 * SubCellular Starter Theme for Drupal 7.
 *
 * @author Adam Blankenship
 * 
 * @see http://live-cellular.gotpantheon.com
 * @see https://github.com/ablank/cellular
 */

/*
 * @see file: preprocess/_init.inc
 * Initialize constants & globals
 */


/**
 * Implements template_preprocess_page().
function subcellular_preprocess_page(&$vars) {
    if (isset($vars['node']) && $vars['node']-type == 'page') {
   // Do something with content type.
    }  
    if (isset($vars['node']) && $vars['node']-nid === '40') {
   // Do something with specific node.
    }
}
 */ 

/**
 * Implements template_preprocess_html().
function subcellular_preprocess_html(&$vars) {
  
}
 */ 

/**
 * Implements template_preprocess_node().
function subcellular_preprocess_node(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_region().
function subcellular_preprocess_region(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_block().
function subcellular_preprocess_block(&$vars) {
  
}
 */

/**
 * Implements template_preprocess_comment().
function subcellular_preprocess_comment(&$vars) {
  
}
 */ 