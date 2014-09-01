<?php

/**
 * @file
 * Add/Update/Delete javascript.
 */

/**
 * hook_js_alter()
 */
function cellular_js_alter(&$javascript) {
// Pass a variable from drupal to js:
//  drupal_add_js(array('myVar' => array('key' => 'value')), 'setting');
  /* myVar will be available in Javascript as:
    <script>
    if (Drupal.settings.myVar.key == value){
    alert('Got it!');
    }
    </script>
   */

// Scripts to add, relative to /yourTheme/js/
  $scripts = array(
    'script' => array(
      'file'   => 'script.js',
      'weight' => 99,
    ),
  );
  cellular_add_js($scripts);

// Update jQuery & jQueryUI.
  if (theme_get_setting('jquery_update') == 1) {
    $jquery = cellular_jquery_info();
    $js_plugins = cellular_add_js_plugins();
    cellular_jquery_update($javascript, $js_plugins);
    cellular_jqueryui_js($javascript, $js_plugins);
    // Add jQuery.migrate to support older plugins if v >= 1.9
    if ($jquery['version'] !== '1.8.24' ) {
      $js_plugins['migrate'] = array(
        'version' => '1.2.1',
        'file'    => 'plugins/jquery.migrate.min.js',
        'weight'  => -96,
      );
    }
  }

// Add js after override.
  cellular_add_js($js_plugins, TRUE);

  if (theme_get_setting('modernizr') == 1) {
    cellular_modernizr();
  }
  // Dev.
  cellular_dev($javascript);
}
