<?php

/**
 * @file
 * Custom Panels functions.
 */

/**
 * Implements theme_panels_default_style_render_region().
 */
function cellular_panels_default_style_render_region($vars) {
  // Remove the panel separator.
  return implode('', $vars['panes']);
}

/**
 * Implements template_preprocess_panels_pane().
 *
 * @param array $vars
 */
function cellular_preprocess_panels_pane(&$vars) {
  $content = &$vars['content'];

  $vars['contextual_links'] = array();
  $vars['classes_array'] = array();
  $vars['admin_links'] = '';

  if (module_exists('contextual') && user_access('access contextual links')) {
    $links = array();
    // These are specified by the content.
    if (!empty($content->admin_links)) {
      $links += $content->admin_links;
    }

    // Take any that may have been in the render array we were given and
    // move them up so they appear outside the pane properly.
    if (is_array($content->content) && isset($content->content['#contextual_links'])) {
      $element = array(
        '#type' => 'contextual_links',
        '#contextual_links' => $content->content['#contextual_links'],
      );
      unset($content->content['#contextual_links']);

      // Add content to $element array.
      if (is_array($content->content)) {
        $element['#element'] = $content->content;
      }

      $element = contextual_pre_render_links($element);
      if (!empty($element['#links'])) {
        $links += $element['#links'];
      }
    }

    if ($links) {
      $build = array(
        '#prefix' => '<div class="contextual-links-wrapper">',
        '#suffix' => '</div>',
        '#theme' => 'links__contextual',
        '#links' => $links,
        '#attributes' => array('class' => array('contextual-links')),
        '#attached' => array(
          'library' => array(array('contextual', 'contextual-links')),
        ),
      );
      $vars['classes_array'][] = 'contextual-links-region';
      $vars['admin_links'] = drupal_render($build);
    }
  }

  // Basic classes.
  $vars['classes_array'][] = 'panel-pane';
  $vars['id'] = '';

  // Add some usable classes based on type/subtype.
  ctools_include('cleanstring');
  $type_class = $content->type ? 'pane-' . ctools_cleanstring($content->type, array('lower case' => TRUE)) : '';
  $subtype_class = $content->subtype ? 'pane-' . ctools_cleanstring($content->subtype, array('lower case' => TRUE)) : '';

  // Sometimes type and subtype are the same. Avoid redundant classes.
  $vars['classes_array'][] = $type_class;
  if ($type_class != $subtype_class) {
    $vars['classes_array'][] = $subtype_class;
  }

  // Add id and custom class if sent in.
  if (!empty($content->content)) {
    if (!empty($content->css_id)) {
      $vars['id'] = ' id="' . $content->css_id . '"';
    }
    if (!empty($content->css_class)) {
      $vars['classes_array'][] = $content->css_class;
    }
  }

  // Set up some placeholders for constructing template file names.
  $base = 'panels_pane';
  $delimiter = '__';

  // Add template file suggestion for content type and sub-type.
  $vars['theme_hook_suggestions'][] = $base . $delimiter . $content->type;
  $vars['theme_hook_suggestions'][] = $base . $delimiter . strtr(ctools_cleanstring($content->type, array('lower case' => TRUE)), '-', '_') . $delimiter . strtr(ctools_cleanstring($content->subtype, array('lower case' => TRUE)), '-', '_');

  $vars['pane_prefix'] = !empty($content->pane_prefix) ? $content->pane_prefix : '';
  $vars['pane_suffix'] = !empty($content->pane_suffix) ? $content->pane_suffix : '';

  $vars['title'] = !empty($content->title) ? $content->title : '';
  $vars['title_heading'] = !empty($content->title_heading) ? $content->title_heading : 'h2';
  $vars['title_attributes_array']['class'][] = 'pane-title';

  $vars['feeds'] = !empty($content->feeds) ? implode(' ', $content->feeds) : '';

  $vars['links'] = !empty($content->links) ? theme('links', array('links' => $content->links)) : '';
  $vars['more'] = '';
  if (!empty($content->more)) {
    if (empty($content->more['title'])) {
      $content->more['title'] = t('More');
    }
    $vars['more'] = l($content->more['title'], $content->more['href'], $content->more);
  }

  $vars['content'] = !empty($content->content) ? $content->content : '';
}
