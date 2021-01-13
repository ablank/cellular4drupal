<?php
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