<?php

/**
 * @file
 * Cellular form utility functions.
 */

/**
 * Array of attributes to be rendered.
 *
 * @param array $element
 *   Variable on which to set attributes.
 *
 * @return array
 *   Attributes to render.
 */
function cellular_form_element_attributes(&$element) {
  // $element['#theme_wrappers'] = NULL;
  $attributes = array();
  // empty($element['#value']) ? NULL : $attributes['value'] = $element['#value'];.
  empty($element['#name']) ? NULL : $attributes['name'] = $element['#name'];
  empty($element['#id']) ? NULL : $attributes['id'] = $element['#id'];
  empty($element['#title']) ? NULL : $attributes['title'] = $element['#title'];
  empty($element['#required']) ? NULL : $attributes['required'] = $element['#required'];
  empty($element['#size']) ? NULL : $attributes['size'] = $element['#size'];
  empty($element['#maxlength']) ? NULL : $attributes['maxlength'] = $element['#maxlength'];
  empty($element['#checked']) ? NULL : $attributes['checked'] = TRUE;
  empty($element['#attributes']['class']) ? NULL : $attributes['class'] = implode(' ', $element['#attributes']['class']);
  empty($element['#default_value']) ? NULL : $attributes['value'] = $element['#default_value'];

  return $attributes;
}

/**
 * Generate markup for theme_radios() & theme_checkboxes().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinputs(&$element) {
  $attributes = cellular_form_element_attributes($element);

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= $element['#children'] ?? NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Generate markup for theme_radio() & theme_checkbox().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinput($element, $type) {
  if (empty($element['#title'])) {
    $element['#title'] = '';
  }
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = $type;
  $attributes['value'] = $element['#return_value'];

  return "<input" . drupal_attributes($attributes) . " />";
}
