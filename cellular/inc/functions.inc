<?php

/*
 *  Get path to current || child theme
 */

function cellular_theme_path(&$theme_key = NULL) {
  $t_theme = isset($theme_key) ? $theme_key : $GLOBALS['theme'];
  $theme_path = drupal_get_path('theme', $t_theme);

  return $theme_path;
}

/*
 *  Merge attributes arrays
 */

function cellular_merge(&$arr) {
  $output = '';
  foreach ($arr as $a) {
    $output .= (is_array($a)) ? implode_r(' ', $a) : " " . $a;
  }

  return $output;
}

/* * ************
  Add <link> & <meta> tags from array
 * ************** */

function cellular_build_head_tags(&$array) {
  $base_weight = 0;

  foreach ($array as $meta => $val) {
    // Build tag
    $tag = array(
      '#type'       => 'html_tag',
      '#tag'        => $val['tag'],
      '#attributes' => array(),
      '#weight'     => isset($val['weight']) ? $val['weight'] : $base_weight
    );

    // Misc. attr/val
    isset($val['attr']) && isset($val['attr_val']) ? $tag['#attributes'][$val['attr']] = $val['attr_val'] : NULL;
    // General attributes
    isset($val['name']) ? $tag['#attributes']['name'] = $val['name'] : NULL;
    isset($val['rel']) ? $tag['#attributes']['rel'] = $val['rel'] : NULL;
    isset($val['content']) ? $tag['#attributes']['content'] = $val['content'] : NULL;
    isset($val['href']) ? $tag['#attributes']['href'] = $val['href'] : NULL;
    // Attributes for favicons
    isset($val['size']) ? $tag['#attributes']['sizes'] = $val['size'] : NULL;
    isset($val['type']) ? $tag['#attributes']['type'] = $val['type'] : NULL;

    drupal_add_html_head($tag, 'meta_' . $meta);
  }
}

function cellular_form_strip_access(&$form) {
  // Nuke text format options
  $form[LANGUAGE_NONE][0]['format']['#access'] = FALSE;

  // Remove individual text format options
  /*
    $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
    $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
   */

  return $form;
}

/*
 * Main Menu
 */

function cellular_main_menu(&$vars) {
  if (theme_get_setting('full_menu') == 1) {

    // Render the full main menu tree
    // Use css / js to show/hide sub-menus
    $main_menu_tree = menu_tree_all_data('main-menu');
  }
  else {
    $main_menu_tree = menu_main_menu();
  }

  return menu_tree_output($main_menu_tree);
}

/*
 * Sidebar Test
 */

function cellular_test_sidebar(&$vars) {
  $sidebar_left = !empty($vars['page']['sidebar_left']) ? 1 : NULL;
  $sidebar_right = !empty($vars['page']['sidebar_right']) ? 1 : NULL;

  // Check if sidebars are rendered & set classes accordingly
  if (isset($sidebar_left) && isset($sidebar_right)) {
    $sidebars = 'dual-sidebars';
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
    $sidebars = 'single-sidebar';
  }
  else {
    $sidebars = 'no-sidebars';
  }

  return $sidebars;
}
