<?php
/* * ************* *
  theme_file_icon()
 * ************** */

function cellular_field($vars) {
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

    /* * ************* *
      theme_file_icon()
     * ************** */

    function cellular_file_icon(&$vars) {
    $file = $vars['file'];
    $mime = check_plain($file->filemime);
    $generic_mime = (string) file_icon_map($file);

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

/* * ************
  theme_breadcrumb()
 * ************* */

function cellular_breadcrumb(&$vars) {

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

/* * ************
  theme_container()
 * ************** */

function cellular_container(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

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

/* * ************
  theme_form_element()
 * ************** */

function cellular_form_element(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    // Set attributes
    isset($element['#title']) ? $attributes['title'] = ($element['#title']) : null;
    //$attributes['class'] = array();
    //isset($element['#name']) ? $attributes['class'][] = 'form-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => '')) : '';
    isset($element['#disabled']) ? $element['#attributes']['class'][] = 'disabled' : null;

    $element['#theme_wrappers'] = null;
    //$output = '<div' . drupal_attributes($attributes) . '>' . "\n";
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

    isset($element['#description']) ?
                    $output .= '<div class="description">' . $element['#description'] . "</div>\n" : null;

    //$output .= "</div>\n";

    return $output;
}

/* * ************
  theme_fieldset()
 * ************** */

function cellular_fieldset(&$vars) {
    $element = $vars['element'];

    $element['#theme_wrappers'] = null;

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

/* * ************
  theme_select()
 * ************* */

function cellular_select(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $output = '<select' . drupal_attributes($element['#attributes']) . ">\n";
    $output .= form_select_options($element) . "\n";
    $output .= "</select>\n";

    return $output;
}

/* * ************
  theme_checkboxes()
 * ************* */

function cellular_checkboxes(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $attributes = array();
    isset($element['#id']) ?
                    $attributes['id'] = $element['#id'] : '';
    isset($element['#attributes']['class']) ?
                    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']) : '';
    isset($element['#attributes']['title']) ?
                    $attributes['title'] = $element['#attributes']['title'] : '';

    $output = "<div" . drupal_attributes($attributes) . ">\n";
    $output .= isset($element['#children']) ? $element['#children'] : null;
    $output .= "\n</div>\n";

    return $output;
}

/* * ************
  theme_radios()
 * ************* */

function cellular_radios(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $attributes = array();
    isset($element['#id']) ?
                    $attributes['id'] = $element['#id'] : '';
    isset($element['#attributes']['class']) ?
                    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']) : '';
    isset($element['#attributes']['title']) ?
                    $attributes['title'] = $element['#attributes']['title'] : '';

    $output = "<div" . drupal_attributes($attributes) . ">\n";
    $output .= isset($element['#children']) ? $element['#children'] : null;
    $output .= "\n</div>\n";

    return $output;
}

/* * ************
  theme_checkbox()
 * ************* */

function cellular_checkbox(&$vars) {
    $element = $vars['element'];
    //$element['#theme_wrappers'] = null;

    $element['#attributes']['type'] = 'checkbox';
    if (!empty($element['#checked'])) {
        $element['#attributes']['checked'] = 'checked';
    }
    element_set_attributes($element, array('name', 'id', '#return_value' => 'value', 'class'));

    return "<input" . drupal_attributes($element['#attributes']) . " />";
}

/* * ************
  theme_radio()
 * ************* */

function cellular_radio(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $element['#attributes']['type'] = 'radio';
    if (isset($element['#return_value']) && $element['#value'] !== FALSE && $element['#value'] == $element['#return_value']) {
        $element['#attributes']['checked'] = 'checked';
    }
    /*
      empty($element['#checked']) ?
      null : $element['#attributes']['checked'] = 'checked';
     */
    element_set_attributes($element, array('name', 'id', '#return_value' => 'value', 'class'));

    return "<input" . drupal_attributes($element['#attributes']) . " />";
}

/* * ************
  theme_textfield()
 * ************* */

function cellular_textfield(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $element['#attributes'] = array(
        'name' => isset($element['#name']) ? $element['#name'] : '',
        'id' => isset($element['#id']) ? $element['#id'] : '',
        'value' => isset($element['#value']) ? $element['#value'] : null,
        'type' => 'text',
        'size' => isset($element['#size']) ? $element['#size'] : 32,
        'maxlength' => isset($element['#maxlength']) ? $element['#maxlength'] : 64,
            //'class' => array(/* 'class1', 'class2', 'etc' */),
    );

    $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

    return $output;
}

/* * ************
  theme_textarea()
 * ************* */

function cellular_textarea(&$vars) {
    $element = $vars['element'];
    $element['#theme_wrappers'] = null;

    $element['#attributes'] = array(
        'name' => isset($element['#name']) ? $element['#name'] : '',
        'id' => isset($element['#id']) ? $element['#id'] : '',
        'value' => isset($element['#value']) ? $element['#value'] : '',
        'cols' => isset($element['#cols']) ? $element['#cols'] : 60,
        'rows' => isset($element['#rows']) ? $element['#rows'] : 5,
            //'class' => array(/* 'class1', 'class2', 'etc' */),
    );

    $output = '<textarea' . drupal_attributes($element['#attributes']) . '>';
    $output .= check_plain($element['#value']);
    $output .= '</textarea>';

    return $output;
}

/* * ************
  theme_feed_icon()
 * ************* */

function cellular_feed_icon($vars) {
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

/* * ************
  theme_pager()
 * ************* */

function cellular_pager($vars) {
    $tags = $vars['tags'];
    $element = $vars['element'];
    $parameters = $vars['parameters'];
    $quantity = $vars['quantity'];
    global $pager_page_array, $pager_total;

    // Calculate various markers within this pager piece:
    // Middle is used to "center" pages around the current page.
    $pager_middle = ceil($quantity / 2);
    // current is the page we are currently paged to
    $pager_current = $pager_page_array[$element] + 1;
    // first is the first page listed by this pager piece (re quantity)
    $pager_first = $pager_current - $pager_middle + 1;
    // last is the last page listed by this pager piece (re quantity)
    $pager_last = $pager_current + $quantity - $pager_middle;
    // max is the maximum page number
    $pager_max = $pager_total[$element];
    // End of marker calculations.
    // Prepare for generation loop.
    $i = $pager_first;
    if ($pager_last > $pager_max) {
        // Adjust "center" if at end of query.
        $i = $i + ($pager_max - $pager_last);
        $pager_last = $pager_max;
    }
    if ($i <= 0) {
        // Adjust "center" if at start of query.
        $pager_last = $pager_last + (1 - $i);
        $i = 1;
    }
    // End of generation loop preparation.

    $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
    $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
    $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
    $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

    if ($pager_total[$element] > 1) {
        if ($li_first) {
            $items[] = array(
                'class' => array('pager-first'),
                'data' => $li_first,
            );
        }
        if ($li_previous) {
            $items[] = array(
                'class' => array('pager-previous'),
                'data' => $li_previous,
            );
        }

        // When there is more than one page, create the pager list.
        if ($i != $pager_max) {
            if ($i > 1) {
                $items[] = array(
                    'class' => array('pager-ellipsis'),
                    'data' => '…',
                );
            }
            // Now generate the actual pager piece.
            for (; $i <= $pager_last && $i <= $pager_max; $i++) {
                if ($i < $pager_current) {
                    $items[] = array(
                        'class' => array('pager-item'),
                        'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
                    );
                }
                if ($i == $pager_current) {
                    $items[] = array(
                        'class' => array('pager-current'),
                        'data' => $i,
                    );
                }
                if ($i > $pager_current) {
                    $items[] = array(
                        'class' => array('pager-item'),
                        'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
                    );
                }
            }
            if ($i < $pager_max) {
                $items[] = array(
                    'class' => array('pager-ellipsis'),
                    'data' => '…',
                );
            }
        }
        // End generation.
        if ($li_next) {
            $items[] = array(
                'class' => array('pager-next'),
                'data' => $li_next,
            );
        }
        if ($li_last) {
            $items[] = array(
                'class' => array('pager-last'),
                'data' => $li_last,
            );
        }
        return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
                    'items' => $items,
                    'attributes' => array('class' => array('pager', 'center')),
        ));
    }
}
