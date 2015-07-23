<?php
/**
 * @file
 * Set element markup.
 */
/**
 * Implements hook_theme_registry_alter().
 */
/*
  function cellular_registry_alter(&$theme_registry) {
  // Override the default page.tpl.php.
  if (theme_get_setting('panelseverywhere') == 1 && isset($theme_registry['page'])) {
  $path = drupal_get_path('theme', 'cellular');
  $theme_registry['field_collection_item']['theme path'] = $path;
  $theme_registry['field_collection_item']['template'] = "$path/templates/page--panels";
  }
  }
 */

/**
 * Implements hook_theme().

  function cellular_theme($existing, $type, $theme, $path) {
  $theme['main_menu'] = array(
  'arguments' => array(
  // if NULL, function checks variable 'menu_primary_links_source'
  'menu_name' => NULL,

  )
  );
  $theme['panels_page'] = array(
  'base hook' => 'page',
  'render element' => 'page',
  'template' => 'templates/page--panels',
  );

  return $theme;
  }
 */

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
    $output = "<div class=\"" . $vars['classes'] . '"' . $vars['attributes'] . ">"
    . "\n $output \n</div>\n";
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
  //Use css classes to style output instead of <img>.
  $file = $vars['file'];
  $mime = check_plain($file->filemime);
  $generic_mime = (string) file_icon_map($file);

  // $dashed_mime = strtr($file->filemime, array('/' => '-'));
  // $icon_path = $icon_directory . '/' . $dashed_mime . '.png';
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
