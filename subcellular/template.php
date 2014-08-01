<?php

/* * ************
subcellular :: template.php
 * ************** */


$include = array(
    //'dev-functions.inc',
    'css_alter.inc',
    'js_alter.inc',
);
$inc_path = drupal_get_path('theme', 'subcellular') . '/inc';
foreach ($include as $i) {
    include_once($inc_path . '/' . $i);
}
/* * ************
Override & add hooks
 * ************** */

/*

function subcellular_preprocess_html(&$vars) {
    //global $language, $base_url;

}

function subcellular_preprocess_node(&$vars) {
   //$node = $vars['node'];

}

function subcellular_preprocess_page(&$vars) {
    
}

function subcellular_preprocess_region(&$vars) {
    
}

function subcellular_preprocess_block(&$vars) {
    
}

function subcellular_preprocess_comment(&$vars) {
    
}
 
 */