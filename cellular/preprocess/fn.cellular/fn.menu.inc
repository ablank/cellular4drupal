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

  // $main_menu['#theme_wrappers'] = 'cellular_menu_tree__main_menu';
  $main_menu = menu_tree_output($main_menu_tree);

  $vars['main_menu'] = $main_menu;
  // $vars['main_menu']['#attributes']['class'] = '1';
  // $vars['main_menu']['#theme_wrappers'] = 'cellular__main_menu';
  return $vars;
}

/**
 * Theme wrapper function for the primary menu links.
 */
function cellular__main_menu(&$vars) {
  $attr = array(
    'id' => 'nav',
    // 'class' => 'zzzz',
  );
  return '<ul' . drupal_attributes($attr) . '>' . $vars['tree'] . '</ul>';
}

function cellular__main_menu_link(&$vars) {

}
