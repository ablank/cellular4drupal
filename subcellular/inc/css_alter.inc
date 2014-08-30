<?php
/**
 * @file
 * Add/Update/Delete stylesheets from theme. *
 */

/*
 * hook_css_alter()
 *
 */
function subcellular_css_alter(&$css) {
  /*
    $add_css = array(
      'styleName'  => array( //  default params
        'file'       => 'my.awesome.css',
        'preprocess' => TRUE,
        'media'      => 'all',
        'every_page' => TRUE,
        'group'      => CSS_THEME,
        'weight'     => 10
      ),
      'otherStyle' => array( // minimum setup
        'file' => 'moar.css',
      ),
    );

    cellular_add_css($css, $add_css);

    */


  /*
   * Remove stylesheets set by modules.
   * Array $key = module name.
   * Array $value = Path relative to each module's directory.
    //  Remove a single stylesheet set by a module:
   * 'stupidModule' => 'path/to/stupid.css'
    // Remove multiple stylesheets set by a module:
   * 'stupidModule' => array('path/to/stupid.css', 'other/path/to/more/stupid.css');
   */
  /*
    $exclude = array(
    'calendar' => 'css/calendar_multiday.css',
    'ctools' => 'css/ctools.css',
    'views' => 'css/views.css',
    'logintoboggan' => 'logintoboggan.css',
    'panels' => array(
    'css/panels.css',
    'plugins/layouts/flexible/flexible.css'
    ),
    );

    cellular_remove_css($css, $exclude);
   */
}
