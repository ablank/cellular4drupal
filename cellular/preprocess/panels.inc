<?php
/**
 * @file
 * Alter specific forms.
 */

/**
 * Alter the default Panels markup.
 */
function cellular_panels_default_style_render_region($vars) {
  // dpm($vars);
  $output = '';
  // $output .= implode('<div class="panel-separator"></div>', $vars['panes']);
  // Remove the panel separator.
  return implode($output, $vars['panes']);
}

/**
 * Alter the panelseverywhere header markup.
 */
function cellular_preprocess_pane_header(&$vars) {
  /*
    //function template_preprocess_pane_header(&$vars) {
    $vars['site_name'] = (theme_get_setting('toggle_name') ? filter_xss_admin(variable_get('site_name', 'Drupal')) : '');

    $vars['site_slogan'] = (theme_get_setting('toggle_slogan') ? filter_xss_admin(variable_get('site_slogan', '')) : '');
    $vars['main_menu'] = cellular_main_menu($vars);
    // dpm($vars);
   */
}
