<?php
/**
 * @file
 * Theme markup of form elements.
 */

/**
 * Return array of attributes.
 *
 * @param array $element
 *  Variable on which to set attributes.
 *
 * @return array
 *  Attributes to render.
 */
function cellular_form_element_attributes(&$element) {
  // $element['#theme_wrappers'] = NULL;
  $attributes = array();
  empty($element['#name']) ? NULL : $attributes['name'] = $element['#name'];
  empty($element['#id']) ? NULL : $attributes['id'] = $element['#id'];
  empty($element['#attributes']['class']) ? NULL : $attributes['class'] = implode(' ', $element['#attributes']['class']);
  empty($element['#title']) ? NULL : $attributes['title'] = $element['#title'];
  empty($element['#required']) ? NULL : $attributes['required'] = $element['#required'];
  empty($element['#checked']) ? NULL : $attributes['checked'] = 'checked';
  empty($element['#size']) ? NULL : $attributes['size'] = $element['#size'];
  empty($element['#maxlength']) ? NULL : $attributes['maxlength'] = $element['#maxlength'];

  return $attributes;
}

/**
 * Cellular theme_form().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
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
  $output = '<form' . drupal_attributes($element['#attributes']) . '>';
  $output .= $element['#children'] . '</form>';

  return $output;
}

/**
 * Cellular theme_container().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return array
 *  Render array of children.
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
 * Cellular theme_form_element().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_form_element(&$vars) {
  $element = $vars['element'];
  $output = '';
  /* May decide to include later:
    // $element['#theme_wrappers'] = NULL;
    // $attributes['class'] = array();
    // isset($element['#name']) ?
    // $attributes['class'][] = 'form-' . strtr($element['#name'], array(
    // ' ' => '-', '_' => '-', '[' => '-', ']' => ''))
    // : NULL;
    // $element['#theme_wrappers'] = NULL;
   */
  isset($element['#disabled']) ?
  $element['#attributes']['class'][] = 'disabled' : NULL;

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

      case 'none':
      case 'attribute':
        $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
        break;
    }
  }

  isset($element['#description']) ?
  $output .= '<div class="description">' . $element['#description'] . "</div>\n" : NULL;

  return $output;
}

/**
 * Cellular theme_button().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_button(&$vars) {
  $element = $vars['element'];
  $output = '';
  $element['#attributes']['type'] = 'submit';
  $element['#attributes']['class'][] = 'button';

  element_set_attributes($element, array('id', 'name', 'value'));

  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }
  $output .= '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output;
}

/**
 * Cellular theme_fieldset().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_fieldset(&$vars) {
  $element = $vars['element'];
  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';

  !empty($element['#title']) ?
  $output .= '<legend>' . $element['#title'] . "</legend>\n" : NULL;
  !empty($element['#description']) ?
  $output .= '<div class="description">' . $element['#description']
  . "</div>\n" : NULL;

  // Add form elements.
  $output .= $element['#children'];

  !empty($element['#value']) ?
  $element['#value'] . "\n" : NULL;

  $output .= "</fieldset>\n";

  return $output;
}

/**
 * Cellular theme_select().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_select(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'select';

  $output .= '<select' . drupal_attributes($attributes) . ">\n";
  $output .= form_select_options($element) . "\n";
  $output .= "</select>\n";

  return $output;
}

/**
 * Cellular theme_checkboxes().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_checkboxes(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);

  $output .= "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ?
  $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Cellular theme_checkbox().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_checkbox(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'checkbox';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));
  $output .= "<input" . drupal_attributes($attributes) . " />";

  return $output;
}

/**
 * Cellular theme_radios().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_radios(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);

  $output .= "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ? $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * Cellular theme_radio().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_radio(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'radio';

  element_set_attributes($element, array(
    '#return_value' => 'value',
  ));
  $output .= "<input" . drupal_attributes($attributes) . " />";

  return $output;
}

/**
 * Cellular theme_textfield().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'text';

  $value = empty($element['#value']) ? '' : ' value="'.$element['#value'].'"';

  $output .= '<input' . drupal_attributes($attributes) . $value . ' />';

  return $output;
}

/**
 * Cellular theme_textarea().
 *
 * @param array $vars
 * Associative array of variables to merge with defaults from the theme registry.
 *
 * @return string
 *  Formatted HTML.
 */
function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $output = '';
  $attributes = cellular_form_element_attributes($element);
  $attributes['type'] = 'textarea';

  $attributes['cols'] = isset($element['#cols']) ? $element['#cols'] : 60;
  $attributes['rows'] = isset($element['#rows']) ? $element['#rows'] : 5;

  $output .= '<textarea' . drupal_attributes($attributes) . '>';
  $output .= check_plain($element['#value']);
  $output .= '</textarea>';

  return $output;
}
