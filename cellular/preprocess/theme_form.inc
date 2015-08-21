<?php
/**
 * @file
 * Theme markup of form elements.
 */

/**
 * Implements theme_form().
 */
function cellular_form($vars) {
  $element = $vars['element'];
  // $element['#attributes']['class'][] = 'cell';
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  // Generate markup.
  $output = "\n<form" . drupal_attributes($element['#attributes']) . ">\n";
  $output .= $element['#children'] . "\n</form>\n";

  return $output;
}

/**
 * Implements theme_container().
 */
function cellular_container(&$vars) {
  $element = $vars['element'];
  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = array('center');
    // Assign an html ID if not present.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
  }

  return $element['#children'];
}

/**
 * Implements theme_form_element().
 */
function cellular_form_element(&$vars) {
  $element = $vars['element'];
  $output = '';

  if (isset($element['#disabled'])) {
    $element['#attributes']['class'][] = 'disabled';
  }

  $prefix = isset($element['#field_prefix']) ?
  '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : NULL;
  $suffix = isset($element['#field_suffix']) ?
  '<span class="field-suffix">' . $element['#field_suffix'] . '</span>' : NULL;

  if (isset($element['#title_display'])) {
    switch ($element['#title_display']) {
      case 'before':
      case 'invisible':
        $output .= ' ' . theme('form_element_label', $vars);
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;

      case 'after':
        $output .= ' ' . $prefix . $element['#children'] . $suffix;
        $output .= ' ' . theme('form_element_label', $vars) . "\n";
        break;

      case 'attribute':
      case 'none':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }
  if (!empty($element['#description'])) {
    $output .= "\n<div class=\"description\">\n" . $element['#description'] . "\n</div>\n";
  }

  return $output;
}

/**
 * Implements theme_button().
 */
function cellular_button(&$vars) {
  $element = $vars['element'];
  $element['#attributes']['type'] = 'submit';
  $element['#attributes']['class'][] = 'button';
  $element['#attributes']['class'][] = $element['#parents'][0];

  element_set_attributes($element, array('id', 'name', 'value'));

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'disabled';
  }
  /* // May add this back if I can get css styling dialed in...
    switch ($element['#parents'][0]) {
    case 'preview':
    case 'submit':
    $element['#attributes']['class'][] = 'right';
    break;

    case 'delete':
    default:
    $element['#attributes']['class'][] = 'left';
    break;
    }
   */

  return "\n<input" . drupal_attributes($element['#attributes']) . " />\n";
}

/**
 * Implements theme_fieldset().
 */
function cellular_fieldset(&$vars) {
  $element = $vars['element'];
  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  !empty($element['#title']) ?
  $output .= '<legend>' . $element['#title'] . "</legend>\n" : NULL;
  !empty($element['#description']) ?
  $output .= '<div class="description">' . t($element['#description']) . "</div>\n" : NULL;
  // Add form elements.
  $output .= $element['#children'];
  $output .=!empty($element['#value']) ? $element['#value'] . "\n" : NULL;
  $output .= "</fieldset>\n";

  return $output;
}

/**
 * Implements theme_checkboxes().
 */
function cellular_checkboxes(&$vars) {

  return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_radios().
 */
function cellular_radios(&$vars) {

  return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_checkbox().
 */
function cellular_checkbox(&$vars) {

  return cellular_xinput($vars['element'], 'checkbox');
}

/**
 * Implements theme_radio().
 */
function cellular_radio(&$vars) {

  return cellular_xinput($vars['element'], 'radio');
}

/**
 * Implements theme_select().
 */
function cellular_select(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'select';

  $output = '<select' . drupal_attributes($attributes) . ">\n";
  $output .= form_select_options($element) . "\n";
  $output .= "</select>\n";

  return $output;
}

/**
 * Implements theme_textfield().
 */
function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'text';
  if (!empty($element['#default_value'])) {
    $attributes['placeholder'] = $element['#default_value'];
  }

  return '<input' . drupal_attributes($attributes) . '/>';
}

/**
 * Implements theme_textarea().
 */
function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'textarea';
  $attributes['placeholder'] = t($element['#default_value']);
  $attributes['cols'] = isset($element['#cols']) ? $element['#cols'] : 60;
  $attributes['rows'] = isset($element['#rows']) ? $element['#rows'] : 5;

  return '<textarea' . drupal_attributes($attributes) . '></textarea>';
}
