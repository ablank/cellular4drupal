<?php
/**
 * @file
 * Theme markup of form elements.
 */

/**
 *  theme_container()
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
  // isset($element['#name']) ? $attributes['class'][] = 'form-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => '')) : '';
  isset($element['#disabled']) ? $element['#attributes']['class'][] = 'disabled' : NULL;

  $element['#theme_wrappers'] = NULL;
  // $output = '<div' . drupal_attributes($attributes) . '>' . "\n";
  $output = '';
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

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

  isset($element['#description']) ? $output .= '<div class="description">' . $element['#description'] . "</div>\n" : NULL;

  return $output;
}

/**
 * theme_fieldset()
 */

function cellular_fieldset(&$vars) {
  $element = $vars['element'];

  $element['#theme_wrappers'] = NULL;

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . ">\n";
  if (isset($element['#title'])) {
    $output .= '<legend>' . $element['#title'] . "</legend>\n";
  }
  if (isset($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'] . "\n";
  }
  $output .= "</fieldset>\n";

  return $output;
}

/**
 *  theme_select()
 */

function cellular_select(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $output = '<select' . drupal_attributes($element['#attributes']) . ">\n";
  $output .= form_select_options($element) . "\n";
  $output .= "</select>\n";

  return $output;
}

/**
 * theme_checkboxes()
 */

function cellular_checkboxes(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $attributes = array();
  isset($element['#id']) ? $attributes['id'] = $element['#id'] : '';
  isset($element['#attributes']['class']) ? $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']) : '';
  isset($element['#attributes']['title']) ? $attributes['title'] = $element['#attributes']['title'] : '';

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ? $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 * theme_radios()
 */

function cellular_radios(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $attributes = array();
  isset($element['#id']) ? $attributes['id'] = $element['#id'] : '';
  isset($element['#attributes']['class']) ? $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']) : '';
  isset($element['#attributes']['title']) ? $attributes['title'] = $element['#attributes']['title'] : '';

  $output = "<div" . drupal_attributes($attributes) . ">\n";
  $output .= isset($element['#children']) ? $element['#children'] : NULL;
  $output .= "\n</div>\n";

  return $output;
}

/**
 *  theme_checkbox()
 */

function cellular_checkbox(&$vars) {
  $element = $vars['element'];
  //$element['#theme_wrappers'] = null;
  $element['#attributes']['type'] = 'checkbox';
  if (!empty($element['#checked'])) {
    $element['#attributes']['checked'] = 'checked';
  }
  element_set_attributes($element, array(
    'name',
    'id',
    '#return_value' => 'value',
    'class',
  ));

  return "<input" . drupal_attributes($element['#attributes']) . " />";
}

/**
 * theme_radio()
 */

function cellular_radio(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $element['#attributes']['type'] = 'radio';
  if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
    $element['#attributes']['checked'] = 'checked';
  }
  /*
    empty($element['#checked']) ?
    null : $element['#attributes']['checked'] = 'checked';
   */
  element_set_attributes($element, array(
    'name',
    'id',
    '#return_value' => 'value',
    'class'
  ));

  return "<input" . drupal_attributes($element['#attributes']) . " />";
}

/**
 * theme_textfield()
 */

function cellular_textfield(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $element['#attributes'] = array(
    'name'      => isset($element['#name']) ? $element['#name'] : '',
    'id'        => isset($element['#id']) ? $element['#id'] : '',
    'value'     => isset($element['#value']) ? $element['#value'] : NULL,
    'type'      => 'text',
    'size'      => isset($element['#size']) ? $element['#size'] : 32,
    'maxlength' => isset($element['#maxlength']) ? $element['#maxlength'] : 64,
    // 'class' => array(/* 'class1', 'class2', 'etc' */),
  );

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output;
}

/**
 * theme_textarea()
 */

function cellular_textarea(&$vars) {
  $element = $vars['element'];
  $element['#theme_wrappers'] = NULL;

  $element['#attributes'] = array(
    'name'  => isset($element['#name']) ? $element['#name'] : '',
    'id'    => isset($element['#id']) ? $element['#id'] : '',
    'value' => isset($element['#value']) ? $element['#value'] : '',
    'cols'  => isset($element['#cols']) ? $element['#cols'] : 60,
    'rows'  => isset($element['#rows']) ? $element['#rows'] : 5,
    // 'class' => array(/* 'class1', 'class2', 'etc' */),
  );

  $output = '<textarea' . drupal_attributes($element['#attributes']) . '>';
  $output .= check_plain($element['#value']);
  $output .= '</textarea>';

  return $output;
}
