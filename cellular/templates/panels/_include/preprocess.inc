<?php
/**
 * @file
 * Preprocess functions for panels.
 */

/**
 *
 *
 * @param type $vars
 * @param int $left
 * @param int $right
 */
function cellular_panels_preprocess_split(&$vars, $left, $right) {

  $vars['region_attributes']['left']['class'][] = "cell-$left";
  $vars['region_attributes']['right']['class'][] = "cell-$right";

  foreach ($vars['content'] as $name => $region) {

    if (!empty($region)) {
      // Add a class to each active region.
      $vars['region_attributes'][$name]['class'][] = "content";
      $vars['region_attributes'][$name]['class'][] = $name;
    }
    elseif ($name === 'left' &&
    !empty($vars['content']['right'])) {
      $vars['region_attributes']['right']['class'][] = "offset-$left";
    }
  }
}

/**
 *
 *
 * @param type $vars
 * @param int $left
 * @param int $right
 */
function cellular_panels_preprocess_triptych(&$vars, $left, $center, $right) {

  $vars['region_attributes']['left']['class'][] = "cell-$left";
  $vars['region_attributes']['center']['class'][] = "cell-$center";
  $vars['region_attributes']['right']['class'][] = "cell-$right";

  foreach ($vars['content'] as $name => $region) {

    if (!empty($region)) {
      // Add a class to each active region.
      $vars['region_attributes'][$name]['class'][] = 'content';
      $vars['region_attributes'][$name]['class'][] = "pane-$name";
    }
    else {
      // Add offsets for empty elements.
      if (
      !empty($vars['content']['right']) &&
      empty($vars['content']['left']) &&
      empty($vars['content']['center'])
      ) {
        $vars['region_attributes']['right']['class'][] = "offset-" . $left + $center;
      }
      elseif (
      !empty($vars['content']['right']) &&
      !empty($vars['content']['left']) &&
      empty($vars['content']['center'])
      ) {
        $vars['region_attributes']['right']['class'][] = "offset-$center";
      }
      elseif (
      !empty($vars['content']['center']) &&
      empty($vars['content']['left'])
      ) {
        $vars['region_attributes']['center']['class'][] = "offset-$left";
      }
    }
  }
}

/**
 *
 *
 * @param type $vars
 * @param int $left
 * @param int $right
 */
function cellular_panels_preprocess_quarters(&$vars, $left, $midleft, $midright, $right) {

  $vars['region_attributes']['left']['class'][] = "cell-$left";
  $vars['region_attributes']['midleft']['class'][] = "cell-$midleft";
  $vars['region_attributes']['midright']['class'][] = "cell-$midright";
  $vars['region_attributes']['right']['class'][] = "cell-$right";

  foreach ($vars['content'] as $name => $region) {

    if (!empty($region)) {
      // Add a class to each active region.
      $vars['region_attributes'][$name]['class'][] = "content";
      $vars['region_attributes'][$name]['class'][] = "pane-$name";
    }
    else {

      if (
      empty($vars['content']['left']) &&
      !empty($vars['content']['midleft'])
      ) {
        $vars['region_attributes']['midleft']['class'][] = "offset-$left";
      }
      elseif (
      empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      !empty($vars['content']['midright'])
      ) {
        $vars['region_attributes']['midright']['class'][] = 'offset-' . $left + $midleft;
      }
      elseif (
      !empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      !empty($vars['content']['midright'])
      ) {
        $vars['region_attributes']['midright']['class'][] = "offset-" . $midleft;
      }
      elseif (
      empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        $vars['region_attributes']['right']['class'][] = "offset-" . $left + $midleft + $midright;
      }
      elseif (
      !empty($vars['content'] ['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        $vars['region_attributes']['right']['class'][] = 'offset-' . $midleft + $midright;
      }
      elseif (
      !empty($vars['content']['midleft']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        $vars['region_attributes']['right']['class'][] = "offset-$midright";
      }
    }
  }
}

/**
 *
 *
 * @param type $vars
 * @param int $left
 * @param int $right
 */
function cellular_panels_preprocess_quintet(&$vars, $left, $midleft, $center, $midright, $right) {

  $vars['region_attributes']['left']['class'][] = "cell-$left";
  $vars['region_attributes']['midleft']['class'][] = "cell-$midleft";
  $vars['region_attributes']['center']['class'][] = "cell-$center";
  $vars['region_attributes']['midright']['class'][] = "cell-$midright";
  $vars['region_attributes']['right']['class'][] = "cell-$right";

  foreach ($vars['content'] as $name => $region) {
    if (!empty($region)) {
      // Add a class to each active region.
      $vars['region_attributes'][$name]['class'][] = "content";
      $vars['region_attributes'][$name]['class'][] = "pane-$name";
    }
    else {
      /*
        $content = $vars['content'];

        switch($region){
        case 'left':
        if(empty($content['left'])) {

        }
        break;

        case 'midleft':
        if(empty($content)) {

        }
        break;

        case 'center':
        break;

        case 'midright':
        break;

        case 'right':
        break;
        }
       */

      if (
      empty($vars['content']['left']) &&
      !empty($vars['content']['midleft'])
      ) {
        $vars['region_attributes']['midleft']['class'][] = "offset-$left";
      }
      elseif (
      empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      !empty($vars['content']['center'])
      ) {
        (string) $offset = (int) $left + (int) $midleft;
        $vars['region_attributes']['center']['class'][] = 'offset-' . $offset;
      }
      elseif (
      !empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      !empty($vars['content']['center'])
      ) {
        $vars['region_attributes']['center']['class'][] = 'offset-' . $midleft;
      }
      elseif (
      empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      !empty($vars['content']['midright'])
      ) {
        (string) $offset = (int) $left + (int) $midleft + (int) $center;
        $vars['region_attributes']['midright']['class'][] = "offset-" . $offset;
      }
      elseif (
      !empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      !empty($vars['content']['midright'])
      ) {
        (string) $offset = (int) $midleft + (int) $center;
        $vars['region_attributes']['midright']['class'][] = "offset-" . $offset;
      }
      elseif (
      !empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      !empty($vars['content']['midright'])
      ) {
        //drupal_set_message('no center');
        $vars['region_attributes']['midright']['class'][] = "offset-" . $center;
      }
      elseif (
      empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        (string) $offset = (int) $left + (int) $midleft + (int) $center + (int) $midright;
        $vars['region_attributes']['right']['class'][] = "offset-" . $offset;
      }
      elseif (
      !empty($vars['content']['left']) &&
      empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        (string) $offset = (int) $midleft + (int) $center + (int) $midright;
        $vars['region_attributes']['right']['class'][] = "offset-" . $offset;
      }
      elseif (
      !empty($vars['content']['midleft']) &&
      empty($vars['content']['center']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        (string) $offset = (int) $center + (int) $midright;
        $vars['region_attributes']['right']['class'][] = "offset-" . $offset;
      }
      elseif (
      !empty($vars['content']['center']) &&
      empty($vars['content']['midright']) &&
      !empty($vars['content']['right'])
      ) {
        $vars['region_attributes']['right']['class'][] = "offset-" . $midright;
      }
    }
  }
  // dpm($vars);
}
