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
function subcellular_preprocess_page(&$vars) {

	// Styling & scripting for specific Nodes Content Types 

$add_css = array();
$add_js = array();

	// Add css & js to content type
 if (isset($vars['node']) && $vars['node']->type == 'page') {
    $content_type_css = array(
        'styleName' => array(
            'file' => cellular_theme_path() . '/css/contentTypeStyle.css',
            'weight' => 1
        ),
   		);

    $content_type_js = array(
      'scriptName' => array( // Name of script
      'file' => 'contentTypeScript.js', // Path to file, relative to /yourTheme/js/
      'every_page' => FALSE,
      ),
      );
    $add_css[] = $content_type_css; 
    $add_js[] = $content_type_js;
  }



   if (isset($vars['node']) && $vars['node']->nid == '40') {
   	$node_css = array(
        'styleName' => array(
            'file' => cellular_theme_path() . '/css/nodeStyle.css',
            'weight' => 1
        ),
   		);

	 $node_js = array(
		'scriptName' => array( // Name of script
      'file' => 'nodeScript.js', // Path to file, relative to /yourTheme/js/
      'every_page' => FALSE,
      ),
	 	);
$add_css[] = $node_css;
    $add_js[] = $node_js;
  }
  cellular_add_css($add_css);
      cellular_add_js($add_js);
}
/*

function subcellular_preprocess_html(&$vars) {
    //global $language, $base_url;

}

function subcellular_preprocess_node(&$vars) {

}


function subcellular_preprocess_region(&$vars) {
    
}

function subcellular_preprocess_block(&$vars) {
    
}

function subcellular_preprocess_comment(&$vars) {
    
}
 
 */