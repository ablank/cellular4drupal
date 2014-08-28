<?php

/*
 * @file
 * Alter misc. hooks for templates
 */

/*
 *  hook_html_head_alter()
 */

function cellular_html_head_alter(&$head_elements) {
  // Remove unwanted meta tags
  $exclude = array('metatag_generator', 'metatag_generator_0');

  foreach ($exclude as $element) {
    if (isset($head_elements[$element])) {
      unset($head_elements[$element]);
    }
  }
  //dsm($head_elements);
}

/*
 *  hook_page_alter()
 */

function cellular_page_alter(&$page) {
  //dsm($page);
}
