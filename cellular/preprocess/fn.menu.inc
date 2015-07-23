<?php
/**
 * @file
 * Cellular menu functions.
 */

/**
 *
 */
function cellular_links__system_main_menu($vars) {
  $output = "<ul id=\"nav\">\n";
  foreach ($vars['links'] as $key => $link) {
    $output .= "<li>" . l($link['title'], $link['href']) . "</li>";
  }
  $output .= "</ul>\n";

  return $output;
}

/**
 * Returns full Main Menu instead of top-level links.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from theme registry.
 */
function cellular_main_menu(&$vars) {
  if (theme_get_setting('full_menu') == 1) {
    // Render the full main menu tree, use css / js to show/hide sub-menus.
    $menu_data = menu_tree_output(menu_tree_all_data('main-menu'));
  }
  else {
    $menu_data = menu_tree('main-menu');
  }

  $vars['main_menu'] = $menu_data;
  //$vars['main_menu']['#theme_wrappers'] = array('cellular_menu_tree__main_menu');
  /*
    $vars['main_menu'] = theme('links__system_main_menu', array(
    'links' => $menu_data,
    'attributes' => array(
    'id' => 'nav',
    'class' => array(
    'primary'
    )
    ),
    // 'heading' => t('Main menu'),
    ));
   */
  // dpm($menu_data);
  // dpm($vars);
}
