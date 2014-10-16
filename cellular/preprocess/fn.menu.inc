<?php
/**
 * @file
 * Cellular menu functions.
 */

/**
 * Returns full Main Menu instead of top-level links.
 */
function cellular_main_menu(&$vars) {
  if (theme_get_setting('full_menu') == 1) {
    // Render the full main menu tree, use css / js to show/hide sub-menus.
    $main_menu_tree = menu_tree_all_data('main-menu');
  }
  else {
    $main_menu_tree = menu_main_menu();
  }

  $main_menu = menu_tree_output($main_menu_tree);
  $vars['main_menu'] = $main_menu;

  return $vars;
  dsm($vars['main_menu']);
}
