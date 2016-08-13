<?php
/**
 * @file
 * Vars & regions for stacked panel layout.
 */
// Customize the number of stacked regions to best suit your needs.
$stacks = 3;

/**
 *
 * @param type $stack
 * @return type
 */
function _layout_stacked_layout_stacks($stack = NULL) {
  $stacks = array(
    'single' => array('cell' => t('Cell')),
    'split' => array(
      'split_left' => t('Split Left Content'),
      'split_right' => t('Split Right Content'),
    ),
    'triptych' => array(
      'triptych_left' => t('Triptych Left Content'),
      'triptych_center' => t('Triptych Center Content'),
      'triptych_right' => t('Triptych Right Content'),
    ),
    'quarters' => array(
      'quarter_left' => t('Quarter Left Content'),
      'quarter_midleft' => t('Quarter Mid-Left Content'),
      'quarter_midright' => t('Quarter Mid-Right Content'),
      'quarter_right' => t('Quarter Right Content'),
    ),
  );

  return $stack === NULL ? drupal_array_merge_deep_array($stacks) : $stacks[$stack];
}

/**
 * Generate the regions variable based on # of stacks.
 *
 * @param type $stacks
 * @return type
 */
function _layout_stacked_generate_regions($stacks = 1) {
  $regions = array(
    'header' => t('Header'),
    'footer' => t('Footer'),
  );
  $stack_regions = _layout_stacked_layout_stacks();

  for ($i = 0; $i < $stacks; $i += 1) {
    foreach ($stack_regions as $region => $title) {
      $regions[$region . '_' . $i] = $title;
    }
  }

  return $regions;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_layout_stacked(&$variables) {
  $variables['stack'] = array();
  // Add a class to the panel
  //$variables['attributes_array']['class'][] = 'some-class';

  foreach ($variables['content'] as $name => $region) {
    // Get index from last character of $name
    $index = substr($name, -1);
    $match_name = preg_match('/[^_]*/', $name, $region_name);

    if (!empty($region)) {
      $classes = &$variables['region_attributes'][$name]['class'];
      $stack = &$variables['stack'][$index];
// Add a class to each active region.
      $classes[] = 'content';
      //$classes[] = $region_name[0];
// Group elements into stacks & add classes specific to each region.
      switch ($region_name[0]) {
        case 'header' :
        case 'footer' :
          $variables['region_attributes'][$name]['class'][] = 'cell';
          break;

        case 'cell':
          if (!empty($region)) {
            $stack['cell'][] = $region_name;
            $classes[] = 'cell';
          }
          break;

        case 'split':
          $stack['split'][] = $region_name;
          $classes[] = 'cell-50';
          break;

        case 'triptych':
          $stack['triptych'][] = $region_name;
          $classes[] = 'cell-33';
          break;

        case 'quarter':
          $stack['quarter'][] = $region_name;
          $classes[] = 'cell-25';
          break;
      }
    }
    else {
      // Handle empty regions.
      $content = $variables['content'];
      $attr = &$variables['region_attributes'];

      //drupal_set_message(print_r($attr[$name]['class']));
      switch ($region_name[0]) {
        case 'split':
          //$c1 = $variables['content']['split_left_' . $index];
          $c2 = $variables['content']['split_right_' . $index];
          if (
          isset($c2) &&
          empty($attr['split_right_' . $index]['class']['offset'])
          ) {
            $attr['split_right_' . $index]['class']['offset'] = 'offset-50';
          }
          break;

        case 'triptych':
          $c1 = $content['triptych_left_' . $index];
          $c2 = $content['triptych_center_' . $index];
          $c3 = $content['triptych_right_' . $index];
          // Add offsets for empty elements.
          if (empty($c3)) {
            // Don't need to do anything if last col is empty.
          }
          elseif (empty($c2)) {

            if (!empty($c3)) {
              // If 1st & 3rd col are set.
              $attr['triptych_center_' . $index]['class'][] = 'offset-33';
              /*
                if (
                !$attr['triptych_center_' . $index]['class']['offset-33']
                ) {
                $attr['triptych_center_' . $index]['class'][] = 'extra-offset-33';
                }
               */
            }
          }
          elseif (empty($c1)) {

            if (!empty($c2)) {
              // If only 2nd col is set.
              $attr['triptych_center_' . $index]['class'][] = 'offset-33';
            }
            elseif (!empty($c3)) {
              // If only 3rd col is set.
              $attr['triptych_right_' . $index]['class'][] = 'offset-66';
            }
          }
          break;

        case 'quarter':
          $c1 = $content['quarter_left_' . $index];
          $c2 = $content['quarter_midleft_' . $index];
          $c3 = $content['quarter_midright_' . $index];
          $c4 = $content['quarter_right_' . $index];
          // Add offset classes for empty elements.
          if (empty($c4)) {
            // Don't need to do anything if last col is empty.
          }
          elseif (empty($c2)) {

            if (!empty($c3)) {
              $attr['quarter_midright_' . $index]['class'][] = 'offset-25';
            }
            else {
              if (!empty($c4)) {
                $attr['quarter_right_' . $index]['class'][] = 'offset-50';
              }
            }
          }
          elseif (empty($c1)) {
            if (!empty($c2)) {
              $attr['quarter_midleft_' . $index]['class'][] = 'offset-25';
            }
            else {
              if (!empty($c3)) {
                $attr['quarter_midright_' . $index]['class'][] = 'offset-50';
              }
              else {
                $attr['quarter_right_' . $index]['class'][] = 'offset-75';
              }
            }
          }
          else {
            $attr['quarter_right_' . $index]['class'][] = 'offset-75';
          }
          break;
      }
    }
  }
  //dpm($variables['region_attributes']);
  //dpm($variables['stack']);
  //dpm($variables['content']);
}
/**
 * Panels layout settings.
 */
$plugin = array(
  'category' => t('Cellular | Layouts'),
  'title' => t('Stacked'),
  'icon' => 'layout_stacked.png',
  'theme' => 'layout_stacked',
  'theme arguments' => array('id', 'content'),
  'admin css' => 'admin.css',
  'regions' => _layout_stacked_generate_regions($stacks),
);
