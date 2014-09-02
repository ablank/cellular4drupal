<?php

/**
 * @file
 * Theme markup of form elements.
 */

/**
 * theme_container()
 */
function cellular_container(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  // Special handling for form elements.
  if (isset($element['#array_parents'])) {
    // Assign an html ID.
    if (!isset($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = array('cell center');
  }

  return $element['#children'];
}

/**
 * theme_form_element()
 */
function cellular_form_element(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  // $attributes['class'] = array();
  // isset($element['#name']) ?
  // $attributes['class'][] = 'form-' . strtr($element['#name'], array(
  //  ' ' => '-', '_' => '-', '[' => '-', ']' => ''))
  // : NULL;
  isset($element['#disabled']) ?
    $element['#attributes']['class'][] = 'disabled' : NULL;

  $element['#theme_wrappers'] = NULL;

  $output = '';
  $prefix = isset($element['#field_prefix']) ?
    '<span class="field-prefix">' . $element['#field_prefix'] . '</span> '
    : NULL;
  $suffix = isset($element['#field_suffix']) ?
    '<span class="field-suffix">' . $element['#field_suffix'] . '</span>'
    : NULL;

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

      case 'none':
      case 'attribute':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }

  isset($element['#description']) ?
    $output .= '<div class="description">' . $element['#description'] . "</div>\n"
    : NULL;

  return $output;
}

/**
 * Return array of attributes.
 */
function cellular_form_element_attributes(&$element) {
  // $element['#theme_wrappers'] = NULL;
  $attributes = array();
  !empty($element['#name']) ?
    $attributes['name'] = $element['#name'] : NULL;
  !empty($element['#id']) ?
    $attributes['id'] = $element['#id'] : NULL;
  !empty($element['#attributes']['class']) ?
    $attributes['class'] = cellular_merge($element['#attributes']['class'])
    : NULL;
  !empty($element['#title']) ?
    $attributes['title'] = $element['#title'] : NULL;
  !empty($element['#required']) ?
    $attributes['required'] = $element['#required'] : NULL;
  !empty($element['#checked']) ?
    $attributes['checked'] = 'checked' : NULL;
  !empty($element['#value']) ?
    $attributes['value'] = $element['#value'] : NULL;
  !empty($element['#size']) ?
    $attributes['size'] = $element['#size'] : NULL;
  !empty($element['#maxlength']) ?
    $attributes['maxlength'] = $element['#maxlength'] : NULL;

  return $attributes;
}

/**
 * theme_fieldset()
 */
function cellular_fieldset(&$vars) {
  $element = $vars['element'];
  $fieldset = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  !empty($element['#title']) ?
    $fieldset .= '<legend>' . $element['#title'] . "</legend>\n"
    : NULL;
  !empty($element['#description']) ?
    $fieldset .= '<div class="description">'
    $fieldset .= $element['#description'];
  $fieldset .= "</div>\n";
  :
  NULL;

  // Add form elements.
  $fieldset .= $element['#children'];

  !empty($element['#value']) ?
    $element['#value'] . "\n" : NULL;

  $fieldset .= "</fieldset>\n";

  return $fieldset;
}

/**
 * theme_select()
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
 * theme_checkboxes()
 */
function cellular_checkboxes(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ?
    $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * theme_checkbox()
 */
function cellular_checkbox(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'checkbox';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));

  return "<input" . drupal_attributes($attributes) . " />";
}

/**
 * theme_radios()
 */
function cellular_radios(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ?
    $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * theme_radio()
 */
function cellular_radio(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'radio';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));

  return "<input" . drupal_attributes($attributes) . " />";
}

/**
 * theme_textfield()
 */
function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'text';

  $output = '<input' . drupal_attributes($attributes) . ' />';

  return $output;
}

/**
 * theme_textarea()
 */
function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'textarea';

  $attributes[] = array(
    'cols' => isset($element['#cols']) ?
        $element['#cols'] : 60,
    'rows' => isset($element['#rows']) ?
        $element['#rows'] : 5,
  );

  $output = '<textarea' . drupal_attributes($attributes) . '>';
  $output .= check_plain($element['#value']);
  $output .= '</textarea>';

  return $output;
}
