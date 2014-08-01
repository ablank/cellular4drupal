<?php

/* * ************
  Cellular:: alter.inc

  Alter variables for templates

 * ************** */

/* * ************
  html_head_alter()
 * ************* */

function cellular_html_head_alter(&$head_elements) {
    // Remove unwanted meta tags
    $exclude = array(
        //'metatag_shortlink',
        'metatag_generator',
    );

    foreach ($exclude as $element) {
        if (isset($head_elements[$element])) {
            unset($head_elements[$element]);
        }
    }

    //dsm($head_elements);
}

/* * ************
  page_alter()
 * ************** */

function cellular_page_alter(&$page) {
    //dsm($page);
}
