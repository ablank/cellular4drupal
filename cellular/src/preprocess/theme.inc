<?php

/**
 * @file
 * Set element markup.
 */

/**
 * Implements hook_theme().
 */
/*
function cellular_theme($existing, $type, $theme, $path) {
$theme = array();
$theme['node__forum'] = array(
'render element' => 'content',
'base hook' => 'node',
'template' => 'node--forum',
'path' => drupal_get_path('theme', 'cellular') . '/templates',
);

return $theme;
}
 */

/**
 * Implements theme_links().
 */
function cellular_links($vars) {
  global $language_url;
  $links = $vars['links'];
  $attributes = $vars['attributes'];
  $heading = $vars['heading'];
  $output = '';

  if (count($links) > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l(ucfirst($link['title']), $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain(ucfirst($link['title']));
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Implements theme_field().
 */
function cellular_field(&$vars) {
  $output = '';
  $wrap = theme_get_setting('field_wrappers');
  // Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $output .= "<h5 class=\"field-label\"" . $vars['title_attributes'] . ">";
    $output .= $vars['label'] . '</h5>';
  }
  // Render the field.
  foreach ($vars['items'] as $delta => $item) {
    $output .= drupal_render($item);
    // Add attributes for each item.
    if (!empty($wrap) && !empty($output)) {
      $output = "\n<div" . $vars['item_attributes'][$delta] . ">\n $output \n</div>";
    }
  }
  // Wrap field if set.
  if ($wrap == 1) {
    $prefix = "<div class=\"" . $vars['classes'] . '"' . $vars['attributes'] . ">\n";
    $output = $prefix . $output . "\n</div>\n";
  }

  return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function cellular_breadcrumb(&$vars) {
  $output = NULL;
  if (theme_get_setting('breadcrumb_display') == 1) {
    if (!empty($vars['breadcrumb'])) {
      $vars['breadcrumb'][] = '<span class="active">' . drupal_get_title() . '</span>';
      $breadcrumb = $vars['breadcrumb'];
      // Provide a navigational heading to give context for breadcrumb links to
      // screen-reader users. Make the heading invisible with .element-invisible.
      $output .= '<h2 class="element-invisible">' . t('You are here') . '</h2>';
      $output .= theme('item_list', array(
        'items' => $breadcrumb,
        'type' => 'ul',
        'attributes' => array('id' => 'breadcrumb'),
      ));
    }
  }

  return $output;
}

/**
 * Implements theme_file_icon().
 */
function cellular_file_icon(&$vars) {
  // Use css classes to style output instead of <img>.
  $file = $vars['file'];
  $mime = check_plain($file->filemime);
  $generic_mime = (string) file_icon_map($file);

  // Use generic icons for each category that provides such icons.
  foreach (array('audio', 'image', 'text', 'video') as $category) {
    if (strpos($file->filemime, $category . '/') == 0) {
      $cname = $category;
    }
  }
  if ($generic_mime) {
    $xmime = explode('/', $mime);
    $cname = $xmime[1];
  }
  isset($cname) ? $cname = $cname : '';

  return '<span class="icon ' . $cname . '"></span>' . "\n";
}

/**
 * Implements theme_feed_icon().
 */
function cellular_feed_icon(&$vars) {
  $text = t('Subscribe to !feed-title', array(
    '!feed-title' => $vars['title'],
  ));

  $icon = l($text, $vars['url'], array(
    'html' => TRUE,
    'attributes' => array(
      'class' => array(
        'icon',
        'rss',
      ),
      'title' => $text,
    ),
  ));

  return $icon;
}
