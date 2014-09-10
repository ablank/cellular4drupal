<?php
/**
 * @file
 * Set element markup.
 */

/**
 * Cellular theme_field().
 */
function cellular_field(&$vars) {
  $content = '';
// Render the label, if it's not hidden.
  if (!$vars['label_hidden']) {
    $content .= "<h5 class=\"field-label\"" . $vars['title_attributes'] . ">";
    $content .= $vars['label'] . '</h5>';
  }
  // Render the items.
  $content .= "<div class=\"field-items\"" . $vars['content_attributes'] . ">";
  foreach ($vars['items'] as $delta => $item) {
    // $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $content .= "\n<div" . $vars['item_attributes'][$delta] . ">\n";
    $content .= drupal_render($item) . "\n</div>";
  }
  $content .= "\n</div>\n";

  // Wrap the field & add content.
  $output = "<div class=\"" . $vars['classes'] . '"' . $vars['attributes'] . ">";
  $output .= "\n" . $content . "\n</div>\n";

  return $output;
}

/**
 * Cellular theme_breadcrumb().
 */
function cellular_breadcrumb(&$vars) {

  if (theme_get_setting('breadcrumb_display') == 1) {
    $breadcrumb = $vars['breadcrumb'];
    $separator = '&#187;';

    if (isset($breadcrumb)) {
      // Add the current page to breadcrumb trail.
      $breadcrumb[] = drupal_get_title();

      $output = "<ol id=\"breadcrumb\">\n";
      foreach ($breadcrumb as $key => $val) {
        if ($key == 0) {
          $output .= "<li class=\"icon home\">$val</li>\n";
        }
        else {
          $output .= "<li>$separator $val</li>\n";
        }
      }
      $output .= "</ol>\n";

      return $output;
    }
  }
}

/**
 * Cellular theme_file_icon()- Use css classes to style output instead of <img>.
 */
function cellular_file_icon(&$vars) {
  $file = $vars['file'];
  $mime = check_plain($file->filemime);
  $generic_mime = (string) file_icon_map($file);

  // $dashed_mime = strtr($file->filemime, array('/' => '-'));
  // $icon_path = $icon_directory . '/' . $dashed_mime . '.png';
  // Use generic icons for each category that provides such icons.
  foreach (array('audio', 'image', 'text', 'video') as $category) {
    if (strpos($file->filemime, $category . '/') === 0) {
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
 * Cellular theme_feed_icon().
 */
function cellular_feed_icon(&$vars) {
  $text = t('Subscribe to !feed-title', array(
    '!feed-title' => $vars['title'],
  ));

  return l($text, $vars['url'], array(
    'html' => TRUE,
    'attributes' => array(
      'class' => array(
        'icon',
        'rss',
      ),
      'title' => $text,
    ),
  ));
}
