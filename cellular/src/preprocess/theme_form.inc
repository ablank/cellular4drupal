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
  // Chrome prevents form submission if a field is required & hidden-
  // Add novalidate to ignore browser & rely on js for client validation.
  $element['#attributes']['novalidate'] = 1;
  // $element['#attributes']['class'][] = 'cell';
  element_set_attributes($element, array('method', 'id'));
  if (!empty($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
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
  if (!empty($element['#array_parents'])) {
    // Add the 'form-wrapper' class.
    $element['#attributes']['class'][] = array('center');
    // Assign an html ID if not present.
    if (empty($element['#attributes']['id'])) {
      $element['#attributes']['id'] = $element['#id'];
    }
  }

  return $element['#children'];
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

  return "\n<input" . drupal_attributes($element['#attributes']) . " />\n";
}

/**
 * Implements theme_fieldset().
 */
function cellular_fieldset(&$vars) {
  $element = $vars['element'];
  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    $output .= '<legend>' . $element['#title'] . "</legend>\n";
  }
  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . t($element['#description']) . "</div>\n";
  }
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
  $attributes['placeholder'] = t($element['#default_value']);
  $attributes['cols'] = !empty($element['#cols']) ? $element['#cols'] : 60;
  $attributes['rows'] = !empty($element['#rows']) ? $element['#rows'] : 5;

  return '<textarea' . drupal_attributes($attributes) . '></textarea>';
}
/**
 * Implements theme_webform_element().
function cellular_webform_element($vars) {
  // Ensure defaults.
  $vars['element'] += array(
    '#title_display' => 'before',
  );

  $element = $vars['element'];

  // All elements using this for display only are given the "display" type.
  if (isset($element['#format']) && $element['#format'] == 'html') {
    $type = 'display';
  }
  else {
    $type = (isset($element['#type']) && !in_array($element['#type'], array('markup', 'textfield', 'webform_email', 'webform_number')))
      ? $element['#type'] : $element['#webform_component']['type'];
  }

  // Convert the parents array into a string, excluding the "submitted" wrapper.
  $nested_level = $element['#parents'][0] == 'submitted' ? 1 : 0;
  $parents = str_replace('_', '-', implode('--', array_slice($element['#parents'], $nested_level)));

  // Get description
  $description = $element['#description'];
  if (!empty($description)) {
    if (theme_get_setting('ui_tooltips') == 1) {
      $element ['#attributes']['data-tooltip'] = $description;
      //$element['#description'] = NULL;
      //unset($element['#description']);
    }
    else {
      $description = "<div class=\"description\">$description</div>\n";
    }
  }

  $wrapper_classes = array();
  if (isset($element['#title_display']) && strcmp($element['#title_display'], 'inline') === 0) {
    $wrapper_classes[] = 'container-inline';
  }
  $output = '<div class="' . implode(' ', $wrapper_classes) . '" id="webform-component-' . $parents . '">' . "\n";

  // If #title_display is none, set it to invisible instead - none only used if
  // we have no title at all to use.
  if ($element['#title_display'] == 'none') {
    $vars['element']['#title_display'] = 'invisible';
    $element['#title_display'] = 'invisible';
  }
  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . _webform_filter_xss($element['#field_prefix']) . '</span> '
    : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . _webform_filter_xss($element['#field_suffix']) . '</span>'
    : '';

  switch ($element['#title_display']) {
    case 'inline':
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
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  $output .= $description;
  $output .= "</div>\n";
  dpm($element);
  return $output;
}
 */
