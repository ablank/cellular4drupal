<?php
/**
 * @file
 * Override drupal misc. 'theme_' functions
 * Prevents need for .tpl files
 */

/**
 * theme_field()
 */
function cellular_field($vars)
{
    $output = '';

    // Render the label, if it's not hidden.
    if (!$vars['label_hidden']) {
        $output .= '<h3 class="field-label"' . $vars['title_attributes'] . '>' . $vars['label'] . '</h3>';
    }

    // Render the items.
    $output .= '<div class="field-items"' . $vars['content_attributes'] . '>';
    $output .= '<div class="' . $classes . '"' . $vars['item_attributes'][$delta] . '>';
    $output .= drupal_render($item);
    $output .= "</div>\n</div>\n";

    return $output;
}

/**
 * theme_file_icon()
 */
function cellular_file_icon(&$vars)
{
    $file = $vars['file'];
    $mime = check_plain($file->filemime);
    $generic_mime = (string)file_icon_map($file);

    //$dashed_mime = strtr($file->filemime, array('/' => '-'));
    //$icon_path = $icon_directory . '/' . $dashed_mime . '.png';
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
 * theme_breadcrumb()
 */
function cellular_breadcrumb(&$vars)
{

    if (theme_get_setting('breadcrumb_display') == 1) {
        $breadcrumb = $vars['breadcrumb'];
        $separator = '&#187;';

        if (isset($breadcrumb)) {
            // Add the current page to breadcrumb trail
            $breadcrumb[] = drupal_get_title();

            $output = '<ol id="breadcrumb">' . "\n";
            foreach ($breadcrumb as $key => $val) {
                if ($key == 0) {
                    $output .= '<li class="icon home">' . $val . "</li>\n";
                } else {
                    $output .= '<li>' . $separator . $val . "</li>\n";
                }
            }
            $output .= "</ol>\n";

            return $output;
        }
    }
}

/**
 * theme_container()
 */

function cellular_container(&$vars)
{
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    // Special handling for form elements.
    if (isset($element['#array_parents'])) {
        // Assign an html ID.
        if (!isset($element['#attributes']['id'])) {
            $element['#attributes']['id'] = $element['#id'];
        }
        // Add the 'form-wrapper' class.
        $element['#attributes']['class'][] = array('cell', 'center');
    }

    return $element['#children'];
}

/**
 * theme_feed_icon()
 */
function cellular_feed_icon($vars)
{
    $text = t('Subscribe to !feed-title', array(
        '!feed-title' => $vars['title']
    ));

    return l('', $vars['url'], array(
        'html' => TRUE,
        'attributes' => array(
            'class' => array('icon', 'rss'),
            'title' => $text
        )
    ));
}
