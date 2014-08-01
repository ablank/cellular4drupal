<?php 
function subcellular_js_alter() {
  /*
	$add_js = array(
        'scriptName' => array(
            'object' => 'domObject',// javascript object 
            'file' => 'scriptFile.js', // Path to file, relative to /yourTheme/js/
            'weight' => 1,
        ),
    );

    cellular_add_js($add_js);

*/

 /* 
  Pass variable from drupal to js
    myVar will be available in Javascript as:
      <script>
      if (Drupal.settings.myVar.key == value){
      alert('Got it!');
      }
      </script>
     */
//  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');

   
}