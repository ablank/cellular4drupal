<?php
/**
 * @file
 * Cellular Base Theme for Drupal 7.
 *
 * @author Adam Blankenship
 *
 * @see http://live-cellular.gotpantheon.com
 * @see https://github.com/ablank/cellular
 */

/*
 * @see file: src/preprocess/_init.inc
 * Initialize constants & global variables.
 */
define('CURRENT_THEME_PATH', cellular_theme_path());
define('CELLULAR_CSS_EXT', cellular_ext('css'));
define('CELLULAR_JS_EXT', cellular_ext('js'));
define('CELLULAR_INPUT_SIZE', 20);

// May convert to use Libraries module at some point...
define('CELLULAR_LIB', theme_get_setting('libpath'));

/*
 * @see file: src/preprocess/fn.inc
 * Cellular utility functions.
 */

/**
 * Get path to the active theme.
 *
 * @param type $theme_key
 *   The name of the theme to get path to, defaults to active theme.
 *
 * @return string
 *   Path to active theme.
 */
function cellular_theme_path(&$theme_key = null)
{
    $theme = isset($theme_key) ? $theme_key : $GLOBALS['theme_key'];

    return drupal_get_path('theme', $theme);
}

/**
 * Get media query breakpoints from theme settings.
 *
 * @return array
 *   Media queries settings.
 */
function cellular_mq()
{
    $mq = [
        'mobile' => theme_get_setting('mq_mobile'),
        'normal' => theme_get_setting('mq_normal'),
        'large' => theme_get_setting('mq_large'),
    ];

    return $mq;
}

/**
 * Get file extensions as .min based on theme settings.
 *
 * @param $type string
 *  Type of file to test settings for, either css or js.
 *
 * @return array
 *  Extension string for each file type.
 */
function cellular_ext($type)
{
    $settings = [
        'css' => '.css',
        'js' => '.js',
    ];

    return $settings[$type];
}

/**
 * Add <link> & <meta> tags from an array.
 *
 * @param array $array
 *   Array of tags to add to document <head>.
 */
function cellular_build_head_tags($array)
{
    foreach ($array as $meta => $val) {
        // Build tag:
        $tag = [
            '#type' => 'html_tag',
            '#tag' => $val['tag'],
            '#attributes' => [],
            '#weight' => isset($val['weight']) ? $val['weight'] : 0,
        ];
        // Misc. attr/val:
        empty($val['attr']) || empty($val['attr_val'])
            ? null
            : ($tag['#attributes'][$val['attr']] = $val['attr_val']);
        empty($val['profile'])
            ? null
            : ($tag['#attributes']['profile'] = $val['profile']);
        // General attributes:
        empty($val['name'])
            ? null
            : ($tag['#attributes']['name'] = $val['name']);
        empty($val['rel']) ? null : ($tag['#attributes']['rel'] = $val['rel']);
        empty($val['content'])
            ? null
            : ($tag['#attributes']['content'] = $val['content']);
        empty($val['href'])
            ? null
            : ($tag['#attributes']['href'] = $val['href']);
        // Attributes for favicons:
        empty($val['size'])
            ? null
            : ($tag['#attributes']['sizes'] = $val['size']);
        empty($val['type'])
            ? null
            : ($tag['#attributes']['type'] = $val['type']);

        drupal_add_html_head($tag, 'meta_' . $meta);
    }
}

/**
 * Removes text formatting options from user input.
 *
 * @param array $form
 *   Form element to set.
 * @param array $form_state
 *   Form element's state.
 */
function cellular_form_format_opt(&$form, $form_state)
{
    // Remove individual text format options:
    // $form[LANGUAGE_NONE][0]['format']['guidelines']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['format']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['help']['#access'] = FALSE;
    // $form[LANGUAGE_NONE][0]['format']['#theme_wrappers'] = NULL;
    // Or Nuke text format options:
    $form[LANGUAGE_NONE][0]['format']['#access'] = false;
    $form[LANGUAGE_NONE][0]['format']['#default_value'] = 'filtered';

    return $form;
}

/**
 * Print variables for development as message, useful if devel isn't active.
 *
 * @param array $element
 *   Element to test and return variables of.
  function cellular_dev($element) {
  if (theme_get_setting('dev') == 1) {
  if (module_exists('devel')) {
  dpm($element);
  }
  else {
  drupal_set_message('<pre>' . print_r($element, TRUE) . '</pre>');
  }
  }
  }
 */

function cellular_proccess_asset(&$asset, $cellular = null)
{
    // Set data source as CDN or local host.
    if (isset($asset['data'])) {
        $data = $asset['data'];
    } elseif (isset($asset['cdn'])) {
        $data = $asset['cdn'];
    } elseif (isset($asset['file'])) {
        $data = $cellular == true ? CELLULAR_LIB : CURRENT_THEME_PATH;
        //$data .= '/css/' . $asset['file'];
    }
    if (!empty($data)) {
        // Set stylesheet properties.
        $asset['data'] = $data;
        $asset['preprocess'] = isset($asset['preprocess'])
            ? $asset['preprocess']
            : true;
        $asset['every_page'] = isset($asset['every_page'])
            ? $asset['every_page']
            : true;
        $asset['weight'] = isset($asset['weight']) ? $asset['weight'] : 1;
        $asset['type'] = isset($asset['cdn']) ? 'external' : 'file';
    }
}

/*
 * @see file: src/preprocess/fn.css.inc
 * Cellular stylesheet functions.
 */

/**
 * Attach scripts to a render array, using a CDN if provided.
 *
 * @param array $css
 *   Default array of stylesheets.
 * @param array $array
 *   Associative array of stylesheet data to add.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_attach_css(&$vars, $array, $cellular = false)
{
    foreach ($array as $style) {
        // Set data source as CDN or local host.
        if (isset($style['cdn'])) {
            $data = $style['cdn'];
        } elseif (isset($style['file'])) {
            $data =
                $cellular === true
                    ? CELLULAR_LIB
                    : CURRENT_THEME_PATH . '/dist/css/';
            $data .= $style['file'];
        }
        if (!empty($data)) {
            // Set stylesheet properties.
            $style['data'] = $data;
            $style['preprocess'] = isset($style['preprocess'])
                ? $style['preprocess']
                : true;
            $style['every_page'] = isset($style['every_page'])
                ? $style['every_page']
                : true;
            $style['group'] = isset($style['group'])
                ? $style['group']
                : CSS_THEME;
            $style['weight'] = isset($style['weight']) ? $style['weight'] : 1;
            $style['type'] = isset($style['cdn']) ? 'external' : 'file';
            $style['media'] = isset($style['media']) ? $style['media'] : 'all';
            $style['browsers'] = isset($style['browsers'])
                ? $style['browsers']
                : ['IE' => true, '!IE' => true];
            // Add stylesheet to $css.
            $vars['#attached']['css'][$data] = $style;
        }
    }
}

/**
 * Add array of stylesheets to $css, using a CDN if provided.
 *
 * @param array $css
 *   Default array of stylesheets.
 * @param array $array
 *   Associative array of stylesheet data to add.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_css($array, $cellular = false)
{
    $type = 'file';
    foreach ($array as $style) {
        // Set data source as CDN or local host.
        if (!empty($style['cdn'])) {
            $data = $style['cdn'];
        } elseif (!empty($style['file'])) {
            $data =
                $cellular === true
                    ? CELLULAR_LIB
                    : CURRENT_THEME_PATH . '/dist/css/';
            $data .= $style['file'];
        } else {
            $data = $style['data'];
        }
        // Set style attributes.
        if (!empty($style['type'])) {
            $type = $style['type'];
        } else {
            if (!empty($style['cdn'])) {
                $type = 'external';
            } elseif (!empty($style['file'])) {
                $type = 'file';
            }
        }
        if (!empty($data)) {
            // Set stylesheet properties.
            $style['type'] = $type;
            $style['group'] = !empty($style['group'])
                ? $style['group']
                : CSS_THEME;
            $style['weight'] = !empty($style['weight']) ? $style['weight'] : 1;
            $style['every_page'] = !empty($style['every_page'])
                ? $style['every_page']
                : true;
            $style['preprocess'] = !empty($style['preprocess'])
                ? $style['preprocess']
                : true;
            $style['media'] = isset($style['media']) ? $style['media'] : 'all';
            $style['browsers'] = isset($style['browsers'])
                ? $style['browsers']
                : ['IE' => true, '!IE' => true];

            drupal_add_css($data, $style);
        }
    }
}

/**
 * Overrides default css values.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $style
 *   Array of stylesheet data used to override default.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_override_css(&$css, $style, $cellular = false)
{
    $ocss = $style['default'];
    // Only override if style is being called.
    if (isset($css[$ocss])) {
        if (isset($style['cdn'])) {
            // If cdn is provided, set data to external source.
            $data = $style['cdn'];
            // Set key to data to prevent multiple calls to same source.
            $ocss = $data;
        } else {
            $data = $cellular === true ? CELLULAR_LIB : '';
            // Or set data to local file.
            $data .= $style['file'];
        }
        // Set stylesheet properties.
        $css[$ocss]['data'] = $data;
        $css[$ocss]['preprocess'] = isset($style['preprocess'])
            ? $style['preprocess']
            : true;
        $css[$ocss]['every_page'] = isset($style['every_page'])
            ? $style['every_page']
            : true;
        $css[$ocss]['group'] = isset($style['group'])
            ? $style['group']
            : CSS_DEFAULT;
        $css[$ocss]['weight'] = isset($style['weight']) ? $style['weight'] : 0;
        $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
        $css[$ocss]['media'] = isset($style['media']) ? $style['media'] : 'all';
        $css[$ocss]['browsers'] = isset($style['browsers'])
            ? $style['browsers']
            : ['IE' => true, '!IE' => true];
    }
}

/**
 * Removes array of stylesheets from $css.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $exclude
 *   Array of stylesheets to remove.
 */
function cellular_remove_css(&$css, $exclude)
{
    foreach ($exclude as $module => $stylesheet) {
        // Remove multiple stylesheets attached by module.
        if (is_array($stylesheet)) {
            foreach ($stylesheet as $style) {
                $index = drupal_get_path('module', $module) . '/' . $style;
                $css[$index] = null;
                unset($css[$index]);
            }
        }
        // Remove individual module stylesheet.
        else {
            $index = drupal_get_path('module', $module) . '/' . $stylesheet;
            $css[$index] = null;
            unset($css[$index]);
        }
    }
}

/**
 * Remove core stylesheets based on theme settings.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_remove_default_css(&$css)
{
    // Remove selected system & module css.
    if (theme_get_setting('remove_drupal_css') === 'select') {
        // Select module css to exclude.
        $exclude = [
            'system' => [
                'system.base.css',
                'system.messages.css',
                'system.theme.css',
                'system.menus.css',
            ],
            'block' => 'block.css',
            'comment' => 'comment.css',
            'field' => 'theme/field.css',
            'file' => 'file.css',
            'image' => 'image.css',
            'filter' => 'filter.css',
            'help' => 'help.css',
            'media' => 'css/media.css',
            'node' => 'node.css',
            'search' => 'search.css',
            'shortcut' => 'shorcut.css',
            'user' => 'user.css',
            // Contrib
            'admin_menu' => [
                'admin_menu.css',
                'admin_menu_toolbar/admin_menu_toolbar.css',
            ],
            'calendar' => ['css/calendar.css', 'css/calendar_multiday.css'],
            'colorbox' => 'styles/default/colorbox_style.css',
            'panels' => 'css/panels.css',
            'views' => 'css/views.css',
            'webform' => 'css/webform.css',
        ];
        cellular_remove_css($css, $exclude);
    } else {
        $exclude = [];
        // Nuke CSS_SYSTEM.
        if (theme_get_setting('remove_drupal_css') === 'system') {
            foreach ($css as $key => $value) {
                if ($value['group'] === CSS_SYSTEM) {
                    $exclude[] = [$key => $value];
                }
            }
        }
        // Nuke SYSTEM_CSS.
        if (theme_get_setting('remove_drupal_css') === 'module') {
            foreach ($css as $key => $value) {
                if ($value['group'] === CSS_DEFAULT) {
                    $exclude[] = [$key => $value];
                }
            }
        }
        // Nuke all css not a member of group CSS_THEME:
        if (theme_get_setting('remove_drupal_css') === 'theme_only') {
            foreach ($css as $key => $value) {
                if ($value['group'] !== CSS_THEME) {
                    $exclude[] = [$key => $value];
                }
            }
        }
        $exclude = drupal_array_merge_deep_array($exclude);

        foreach ($exclude as $module => $data) {
            $css[$data['data']] = null;
            unset($css[$data['data']]);
        }
    }
}

/**
 * Add critical styles (above the fold) inline.
 * @see http://fourword.fourkitchens.com/article/use-grunt-and-advagg-inline-critical-css-drupal-7-theme
 */
function cellular_critical_css($vars)
{
    if (theme_get_setting('inline_critical_css') == 1) {
        $ext = CELLULAR_CSS_EXT;
        $critical_opts = [
            'type' => 'inline',
            'scope' => 'critical',
            'group' => CSS_SYSTEM,
            'weight' => -1000,
            'preprocess' => false,
        ];

        if ($vars['is_front'] == 1) {
            $critical_file = 'critical-front' . $ext;
        } else {
            $critical_file = 'critical' . $ext;
        }

        // Add the stylesheet inline.
        drupal_add_css(
            file_get_contents(
                CURRENT_THEME_PATH . '/dist/css/' . $critical_file
            ),
            $critical_opts
        );
    }
}

/*
 * @see file: src/preprocess/fn.form.inc
 * Cellular form utility functions.
 */

/**
 * Array of attributes to be rendered.
 *
 * @param array $element
 *   Variable on which to set attributes.
 *
 * @return array
 *   Attributes to render.
 */
function cellular_form_element_attributes(&$element)
{
    // $element['#theme_wrappers'] = NULL;
    $attributes = [];
    //empty($element['#value']) ? NULL : $attributes['value'] = $element['#value'];
    empty($element['#name']) ? null : ($attributes['name'] = $element['#name']);
    empty($element['#id']) ? null : ($attributes['id'] = $element['#id']);
    empty($element['#required'])
        ? null
        : ($attributes['required'] = $element['#required']);
    empty($element['#size']) ? null : ($attributes['size'] = $element['#size']);
    empty($element['#maxlength'])
        ? null
        : ($attributes['maxlength'] = $element['#maxlength']);
    empty($element['#checked']) ? null : ($attributes['checked'] = true);
    empty($element['#attributes']['class'])
        ? null
        : ($attributes['class'] = implode(
            ' ',
            $element['#attributes']['class']
        ));
    empty($element['#default_value'])
        ? null
        : ($attributes['value'] = $element['#default_value']);
    if (!empty($element['#title'])) {
        $attributes['title'] = $element['#title'];
        $attributes['aria-label'] = $element['#title'];
    }

    return $attributes;
}

/**
 * Generate markup for theme_radios() & theme_checkboxes().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinputs(&$element)
{
    $attributes = cellular_form_element_attributes($element);

    $output = '<div' . drupal_attributes($attributes) . ">\n";
    $output .= isset($element['#children']) ? $element['#children'] : null;
    $output .= "\n</div>\n";

    return $output;
}

/**
 * Generate markup for theme_radio() & theme_checkbox().
 *
 * @param array $element
 *   Element being styled.
 *
 * @return string
 *   Formatted markup.
 */
function cellular_xinput($element, $type)
{
    if (empty($element['#title'])) {
        // Set an empty string to guarantee <label> is provided, used for fancy styling.
        $element['#title'] = '';
    }
    $attributes = cellular_form_element_attributes($element);
    $attributes['type'] = $type;
    $attributes['value'] = $element['#return_value'];

    return '<input' . drupal_attributes($attributes) . ' />';
}

/*
 * @see file: src/preprocess/fn.form_validate.inc
 * Cellular form validation.
function cellular_form_validate($form, &$form_state) {
 // dpm($form);
}
 */

/*
 *
function webform_client_form_validate($form, &$form_state) {
  $node = node_load($form_state['values']['details']['nid']);
  $finished = $form_state['values']['details']['finished'];

  // Check that the submissions have not exceeded the total submission limit.
  if ($node->webform['total_submit_limit'] != -1) {
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    // Check if the total number of entries was reached before the user submitted
    // the form.
    if (!$finished && $total_limit_exceeded = _webform_submission_total_limit_check($node)) {
      // Show the user the limit has exceeded.
      theme('webform_view_messages', array('node' => $node, 'teaser' => 0, 'page' => 1, 'submission_count' => 0, 'total_limit_exceeded' => $total_limit_exceeded, 'allowed_roles' => array_keys(user_roles()), 'closed' => FALSE, 'cached' => FALSE));
      form_set_error('', NULL);
      return;
    }
  }

  // Check that the user has not exceeded the submission limit.
  // This usually will only apply to anonymous users when the page cache is
  // enabled, because they may submit the form even if they do not have access.
  if ($node->webform['submit_limit'] != -1) { // -1: Submissions are never throttled.
    module_load_include('inc', 'webform', 'includes/webform.submissions');

    if (!$finished && $user_limit_exceeded = _webform_submission_user_limit_check($node)) {
      // Assume that webform_view_messages will print out the necessary message,
      // then stop the processing of the form with an empty form error.
      theme('webform_view_messages', array('node' => $node, 'teaser' => 0, 'page' => 1, 'submission_count' => 0, 'user_limit_exceeded' => $user_limit_exceeded, 'allowed_roles' => array_keys(user_roles()), 'closed' => FALSE, 'cached' => FALSE));
      form_set_error('', NULL);
      return;
    }
  }

  // Run all #element_validate and #required checks. These are skipped initially
  // by setting #validated = TRUE on all components when they are added.
  _webform_client_form_validate($form, $form_state);
}

 */

/*
 * @see file: src/preprocess/fn.js.inc
 * Cellular javascript functions.
 */

/**
 * Attach scripts to a render array, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * an 'object' key value is provided.
 *
 * @param array $array
 *   Assosciative array of javascript data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_attach_js(&$vars, $array, $cellular = false)
{
    foreach ($array as $script) {
        // Test if local or external source is provided.
        if (!empty($script['cdn'])) {
            $data = $script['cdn'];
            $script['type'] = 'external';
            cellular_js_fallback($script, $cellular);
        } elseif (!empty($script['file'])) {
            $script['type'] = 'file';
            $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH . '/dist/js/';
            $data .= $script['file'];
        } else {
            $data = $script['data'];
            $script['type'] = $script['type'];
        }
        // Set script attributes.
        $script['data'] = $data;
        $script['scope'] = !empty($script['scope'])
            ? $script['scope']
            : 'header';
        $script['group'] = !empty($script['group'])
            ? $script['group']
            : JS_THEME;
        $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
        $script['preprocess'] = !empty($script['preprocess'])
            ? $script['preprocess']
            : true;
        $script['cache'] = !empty($script['cache']) ? $script['cache'] : true;
        $script['defer'] = !empty($script['defer']) ? $script['defer'] : false;
        $script['every_page'] = !empty($script['every_page'])
            ? $script['every_page']
            : true;
        empty($script['version'])
            ? null
            : ($script['version'] = $script['version']);

        $vars['#attached']['js'][$data] = $script;
    }
}

/**
 * Add scripts from an array, using a CDN if provided.
 *
 * A fallback link will be automatically generated if using CDN and
 * an 'object' key value is provided.
 *
 * @param array $array
 *   Assosciative array of javascript data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_js($array, $cellular = false)
{
    $type = 'file';
    foreach ($array as $script) {
        // Test if local or external source is provided.
        if (!empty($script['cdn'])) {
            $data = $script['cdn'];
            cellular_js_fallback($script, $cellular);
        } elseif (!empty($script['file'])) {
            $data = $cellular ? CELLULAR_LIB : CURRENT_THEME_PATH . '/dist/js/';
            $data .= $script['file'];
        } else {
            $data = $script['data'];
        }
        // Set script attributes.
        if (!empty($script['type'])) {
            $type = $script['type'];
        } else {
            if (!empty($script['cdn'])) {
                $type = 'external';
            } elseif (!empty($script['file'])) {
                $type = 'file';
            }
        }

        $script['type'] = $type;
        $script['scope'] = !empty($script['scope'])
            ? $script['scope']
            : 'header';
        $script['group'] = !empty($script['group'])
            ? $script['group']
            : JS_THEME;
        $script['weight'] = !empty($script['weight']) ? $script['weight'] : 0;
        $script['every_page'] = !empty($script['every_page'])
            ? $script['every_page']
            : true;
        $script['preprocess'] = !empty($script['preprocess'])
            ? $script['preprocess']
            : true;
        $script['cache'] = !empty($script['cache']) ? $script['cache'] : true;
        $script['defer'] = !empty($script['defer']) ? $script['defer'] : false;
        empty($script['version'])
            ? null
            : ($script['version'] = $script['version']);

        drupal_add_js($data, $script);
    }
}

/**
 * Javascript fallback to local source if CDN fails.
 *
 * @param array $script
 *   Array of script attributes used to generate fallback.
 * @param  $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_js_fallback($script, $cellular = false)
{
    // Only add the fallback if an object has been provided to test.
    if (!empty($script['object'])) {
        $attributes = [
            'type' => 'inline',
            'group' => !empty($script['group']) ? $script['group'] : JS_THEME,
            'weight' => !empty($script['weight']) ? $script['weight'] + 0.1 : 1,
            'every_page' => !empty($script['every_page'])
                ? $script['every_page']
                : true,
        ];
        // Construct the fallback script.
        $fallback =
            'window.' .
            $script['object'] .
            ' || document.write("<script src=\"';
        $fallback .= $cellular
            ? CELLULAR_LIB
            : CURRENT_THEME_PATH . '/dist/js/';
        $fallback .= $script['file'];
        $fallback .= '\">\x3C/script>")';

        drupal_add_js($fallback, $attributes);
    }
}

/**
 * Override existing $javascript sources.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 * @param array $script
 *   Array of attributes used to add javascript fallback.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_js_override(&$javascript, $script, $cellular = false)
{
    // Only override if js is being called.
    if (isset($javascript[$script['default']])) {
        $ojs = $script['default'];
        if (!empty($script['cdn'])) {
            // If cdn is provided, set data to external source & call local fallback.
            $data = $script['cdn'];
            cellular_js_fallback($script, $cellular);
        } else {
            // Use local source if no CDN is used.
            if (!empty($script['file'])) {
                $data = $cellular ? CELLULAR_LIB : null;
                $data .= $script['file'];
            }
        }
        // Set the script attributes.
        $javascript[$ojs]['data'] = $data;
        $javascript[$ojs]['type'] = !empty($script['cdn'])
            ? 'external'
            : 'file';
        $javascript[$ojs]['scope'] = !empty($script['scope'])
            ? $script['scope']
            : $javascript[$ojs]['scope'];
        $javascript[$ojs]['group'] = !empty($script['group'])
            ? $script['group']
            : $javascript[$ojs]['group'];
        $javascript[$ojs]['every_page'] = !empty($script['every_page'])
            ? $script['every_page']
            : $javascript[$ojs]['every_page'];
        $javascript[$ojs]['weight'] = !empty($script['weight'])
            ? $script['weight']
            : $javascript[$ojs]['weight'];
        $javascript[$ojs]['preprocess'] = !empty($script['preprocess'])
            ? $script['preprocess']
            : $javascript[$ojs]['preprocess'];
        $javascript[$ojs]['cache'] = !empty($script['cache'])
            ? $script['cache']
            : $javascript[$ojs]['cache'];
        $javascript[$ojs]['defer'] = !empty($script['defer'])
            ? $script['defer']
            : $javascript[$ojs]['defer'];
        empty($script['version'])
            ? null
            : ($javascript[$ojs]['version'] = $script['version']);
    }
}

/*
 * @see file: src/preprocess/fn.menu.inc
 * Cellular menu functions.
 */

/**
 * Returns full Main Menu tree instead of top-level only links.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from theme registry.
 */
function cellular_main_menu(&$vars)
{
    if (theme_get_setting('full_menu') == 1) {
        // Render the full main menu tree, use css / js to show/hide sub-menus.
        $menu_data = menu_tree_output(menu_tree_all_data('main-menu'));
    } else {
        $menu_data = menu_tree('main-menu');
    }

    $vars['main_menu'] = $menu_data;
}
/**
 * Implements links__system_main_menu.
function cellular_links__system_main_menu($vars) {
  $output = "<ul id=\"nav\">\n";
  foreach ($vars['links'] as $key => $link) {
    $output .= "<li>" . l($link['title'], $link['href']) . "</li>";
  }
  $output .= "</ul>\n";

  return $output;
}
*/

/*
 * @see file: src/preprocess/fn.preprocess.inc
 * Cellular functions to set content attributes.
 */
/**
 * Test if sidebar regions are used and return the appropriate class.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.

  function cellular_test_sidebar(&$vars) {
  empty($vars['page']['sidebar_left']) ? NULL : $sidebar_left = 1;
  empty($vars['page']['sidebar_right']) ? NULL : $sidebar_right = 1;

  if (!isset($sidebar_left) && !isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_no_sidebar');
  }
  elseif (isset($sidebar_left) && isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_dual_sidebars');
  $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_dual_sidebars');
  }
  elseif (isset($sidebar_left) || isset($sidebar_right)) {
  $vars['page']['content_class'] = theme_get_setting('content_class_single_sidebar');
  $vars['page']['sidebar_class'] = theme_get_setting('sidebar_class_single_sidebar');
  }
  } */

/**
 *
 */
function cellular_author_info(&$vars)
{
    // Author info
    $aid = user_load($vars['uid']);
    if (!empty($aid)) {
        dpm($vars);
        /* $author = theme('image_style', array(
         * 'style_name' => 'thumbnail',
         * 'path' => $user->picture->uri,
         * )); */
        $author = theme('user_picture', [
            'account' => $aid,
            'style_name' => 'thumbnail',
            '#attributes' => ['class' => ['author-image']],
        ]);
        $author .= $aid->name;
    }

    // Push formatted author block to $vars array.
    return $author;
}

function cellular_post_date($node)
{
    // Date node was created.
    $date = "\n<span class=\"day\">" . date('j', $node->created) . "</span>\n";
    $date .= "<span class=\"month\">" . date('M', $node->created) . "</span>\n";
    $date .= "<span class=\"year\">" . date('Y', $node->created) . "</span>\n";

    return $date;
}

/**
 * Set path to page-error.tpl if header error code is returned.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_error_page(&$vars)
{
    $http_status = drupal_get_http_header('status');
    // Set error page template if error.
    switch ($http_status) {
        case '403 Forbidden':
        case '404 Not Found':
        case '500 Internal Server Error':
            $vars['theme_hook_suggestions'][] = 'page__error';
            $vars['http_status'] = 'Error: ' . $http_status;
            $vars['classes_array'][] = 'page-error';
            $vars['error_message'] = drupal_get_messages();
            break;
    }
}

/*
 * @see file: src/preprocess/jquery.inc
 * Functions for updating jQuery & jQuery.ui.
 */

/**
 * Get info from theme settings.
 *
 * @return array
 *   Settings for jQuery & jQuery.ui
 */
function cellular_jquery_info()
{
    $jquery = [
        'default' => 'misc/jquery.js',
        'update' => theme_get_setting('jquery_update'),
        'version' => theme_get_setting('jquery_version'),
        'use_cdn' => theme_get_setting('jquery_cdn'),
        'cdn' => theme_get_setting('jquery_cdn_source'),
        'ui' => [
            'version' => theme_get_setting('jqueryui_version'),
            'theme' => theme_get_setting('jqueryui_theme'),
        ],
    ];
    $jquery['file'] = 'jquery-' . $jquery['version'] . CELLULAR_JS_EXT;

    return $jquery;
}

/**
 * Configure links to CDN sources.
 *
 * @return array
 *   CDN URLs used to update jQuery & jQuery.ui
 */
function cellular_cdn()
{
    $jq = cellular_jquery_info();
    $ui = $jq['ui'];
    /* Available cdns:
     * //ajax.googleapis.com/ajax/libs/jquery/1.10.4/jquery.min.js
     * //ajax.aspnetcdn.com/ajax/jquery.ui/1.10.4/jquery-ui.min.js
     * //cdnjs.cloudflare.com/ajax/libs/jqueryui/1.10.4/jquery-ui.min.js
     */
    $networks = [
        'jquery' => [
            'base_url' => 'code.jquery.com',
            'jquery' => 'jquery-' . $jq['version'] . CELLULAR_JS_EXT,
            'jqueryui' =>
                'ui/' . $ui['version'] . '/jquery-ui' . CELLULAR_JS_EXT,
            'theme' =>
                'ui/' .
                $ui['version'] .
                '/themes/' .
                $ui['theme'] .
                '/jquery-ui' .
                CELLULAR_CSS_EXT,
        ],
        'google' => [
            'base_url' => 'ajax.googleapis.com/ajax/libs',
            'jquery' =>
                'jquery/' . $jq['version'] . '/jquery' . CELLULAR_JS_EXT,
            'jqueryui' =>
                'jqueryui/' . $ui['version'] . '/jquery-ui' . CELLULAR_JS_EXT,
            'theme' =>
                'jqueryui/' .
                $ui['version'] .
                '/themes/' .
                $ui['theme'] .
                '/jquery-ui' .
                CELLULAR_CSS_EXT,
        ],
        'microsoft' => [
            'base_url' => 'ajax.aspnetcdn.com/ajax',
            'jquery' => 'jquery/jquery-' . $jq['version'] . CELLULAR_JS_EXT,
            'jqueryui' =>
                'jquery.ui/' . $ui['version'] . '/jquery-ui' . CELLULAR_JS_EXT,
            'theme' =>
                'jquery.ui/' .
                $ui['version'] .
                '/themes/' .
                $ui['theme'] .
                '/jquery-ui' .
                CELLULAR_CSS_EXT,
        ],
        'cloudflare' => [
            'base_url' => 'cdnjs.cloudflare.com/ajax/libs',
            'jquery' =>
                'jquery/' . $jq['version'] . '/jquery' . CELLULAR_JS_EXT,
            'jqueryui' =>
                'jqueryui/' . $ui['version'] . '/jquery-ui' . CELLULAR_JS_EXT,
            // Themes aren't provided by cdnjs.
            'theme' =>
                'jqueryui/' .
                $ui['version'] .
                '/css/jquery-ui' .
                CELLULAR_CSS_EXT,
        ],
    ];

    return $networks[$jq['cdn']];
}

/**
 * Update jQuery.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 */
function cellular_jquery_update(&$javascript)
{
    $jq = cellular_jquery_info();
    // Override jQuery.
    $jquery = [
        'default' => $jq['default'],
        'file' => '/jquery/' . $jq['file'],
        //'file' => 'jquery-' . $jq['version'] . '.min.js',
        'version' => $jq['version'],
        'every_page' => true,
        'group' => JS_LIBRARY,
        'weight' => -100,
    ];
    // Set CDN or local source.
    if ($jq['use_cdn'] == true) {
        $cdn = cellular_cdn();
        $jquery['object'] = 'jQuery';
        $jquery['cdn'] = 'https://' . $cdn['base_url'] . '/' . $cdn['jquery'];
    }
    // Override jQuery.
    cellular_js_override($javascript, $jquery, true);
    // Update the Drupal's default jQuery plugins.
    if (theme_get_setting('jquery_plugins_update') == 1) {
        cellular_update_plugins($javascript, $jquery);
    }
}

/**
 * Override jQueryUI javascript.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 */
function cellular_jqueryui_update_js(&$javascript)
{
    $jq = cellular_jquery_info();
    $ui_widgets = [
        'ui.core',
        'ui.accordion',
        'ui.autocomplete',
        'ui.button',
        'ui.datepicker',
        'ui.dialog',
        'ui.draggable',
        'ui.droppable',
        'ui.mouse',
        'ui.position',
        'ui.progressbar',
        'ui.resizable',
        'ui.selectable',
        'ui.slider',
        'ui.sortable',
        'ui.tabs',
        'ui.widget',
        'effects.blind',
        'effects.bounce',
        'effects.clip',
        'effects.drop',
        'effects.explode',
        'effects.fade',
        'effects.fold',
        'effects.highlight',
        'effects.pulsate',
        'effects.scale',
        'effects.shake',
        'effects.slide',
        'effects.transfer',
    ];

    foreach ($ui_widgets as $widget) {
        $default = 'misc/ui/jquery.' . $widget . '.min.js';
        if (isset($javascript[$default])) {
            $script = [
                'jqueryui' => [
                    'default' => $default,
                    'object' => 'jQuery.ui',
                    'version' => $jq['ui']['version'],
                    'group' => JS_LIBRARY,
                    'every_page' => false,
                    'weight' => isset($javascript[$default]['weight'])
                        ? $javascript[$default]['weight']
                        : -99,
                    'file' =>
                        '/jquery-ui/' .
                        $jq['ui']['version'] .
                        "/minified/jquery.$widget.min.js",
                    'preprocess' => true,
                    'browsers' => ['IE' => true, '!IE' => true],
                ],
            ];

            if (theme_get_setting('jquery_cdn') == 1) {
                $cdn = cellular_cdn();
                // If updating from cdn unset each widget so a single call is made for all widgets.
                unset($javascript[$default]);
                // Set cdn source.
                $script['jqueryui']['cdn'] =
                    'https://' . $cdn['base_url'] . '/' . $cdn['jqueryui'];
                // Set lower weight so cdn is delivered before fallbacks.
                $script['jqueryui']['weight'] = -10;
                // Add single link to cdn, with local fallback to each file.
                cellular_add_js($script, true);
            } else {
                // Use local source, only include only scripts that are needed.
                // Recommend AdvAgg, or use core aggregation in
                cellular_js_override($javascript, $script['jqueryui'], true);
            }
        }
    }
}

/**
 * Update jQuery.ui stylesheets.
 *
 * @param array $css
 *   Associative array of stylesheets.
 */
function cellular_jqueryui_update_css(&$css)
{
    $jq = cellular_jquery_info();
    $ui = $jq['ui'];
    $ui['path'] = '/jquery-ui/css/';
    $ui['widgets'] = [
        'core',
        'theme',
        'accordion',
        'autocomplete',
        'button',
        'datepicker',
        'dialog',
        'progressbar',
        'resizable',
        'selectable',
        'slider',
        'tabs',
    ];

    foreach ($ui['widgets'] as $widget) {
        $default = "misc/ui/jquery.ui.$widget.css";
        if (isset($css[$default])) {
            $style = [
                'ui' => [
                    'default' => $default,
                    'version' => $ui['version'],
                    'group' => CSS_SYSTEM,
                    'every_page' => false,
                    'weight' => !empty($css[$default]['weight'])
                        ? $css[$default]['weight']
                        : -9,
                    'file' => null,
                    'preprocess' => true,
                ],
            ];
            // Remove default after collecting style info.
            // unset($css[$default]);

            if ($ui['theme'] === 'custom') {
                // Set path to local custom file if selected.
                $v = $ui['version'] === '1.10.4' ? '1.10' : '1.9';
                $style['ui']['file'] =
                    'jquery-ui/jquery-ui-' . $v . CELLULAR_CSS_EXT;

                cellular_add_css($style);
            } else {
                $ui_path =
                    $ui['path'] . $ui['version'] . '/' . $ui['theme'] . '/';
                $style['ui']['file'] =
                    $ui_path . 'jquery-ui' . CELLULAR_CSS_EXT;

                cellular_add_css($style, true);
            }
        }
    }
}

/*
 * @see file: src/preprocess/plugin_js.inc
 * Functions to add javascript plugins.
 */

/**
 * Update Drupal's default jQuery plugins.
 *
 * @param array $javascript
 *   Associative array of javascripts.
 *
 * @param array $jquery
 *   jQuery version info.
 */
function cellular_update_plugins(&$javascript, $jquery)
{
    $plugin_path = '/drupal/'; // Relative to Cellular Lib
    $plugins = [
        'bbq' => [
            'default' => 'misc/jquery.ba-bbq.js',
            'version' => '1.3',
            'file' => 'jquery.ba-bbq',
        ],
        'cookie' => [
            'default' => 'misc/jquery.cookie.js',
            'version' => '1.4.1',
            'file' => 'jquery.cookie',
        ],
        'form' => [
            'default' => 'misc/jquery.form.js',
            'version' => '3.48',
            'file' => 'jquery.form',
        ],
        'once' => [
            'default' => 'misc/jquery.once.js',
            'version' => '1.2.6',
            'file' => 'jquery.once',
        ],
    ];

    foreach ($plugins as &$plugin) {
        $plugin['file'] = $plugin_path . $plugin['file'] . CELLULAR_JS_EXT;
        $plugin['group'] = JS_LIBRARY;
        cellular_js_override($javascript, $plugin, true);
    }
}

/**
 * Pass variables to javascript , used to call plugin.js if plugins are selected.
 */
function cellular_js_plugin_settings()
{
    // Javascript Drupal.settings.cellular.plugin === TRUE if selected in theme settings.
    $js_plugins = [];
    theme_get_setting('backstretch') == 1
        ? ($js_plugins['backstretch'] = true)
        : null;
    theme_get_setting('flowtype') == 1
        ? ($js_plugins['flowtype'] = true)
        : null;
    theme_get_setting('freetile') == 1
        ? ($js_plugins['freetile'] = true)
        : null;
    theme_get_setting('jparallax') == 1
        ? ($js_plugins['jparallax'] = true)
        : null;
    theme_get_setting('smoove') == 1 ? ($js_plugins['smoove'] = true) : null;
    theme_get_setting('nprogress') == 1
        ? ($js_plugins['nprogress'] = true)
        : null;

    return $js_plugins;
}

/**
 * Add javascript plugins using the cellular libraary.
 *
 * @return array
 *   Associative array of plugin data.
 */
function cellular_plugins_js()
{
    $jquery = cellular_jquery_info();
    $plugin_path = '/lib/';
    // Scripts to add, relative to /libraries/cellular/js/
    $js_plugins = [];

    // Add migrate to prevent plugins from breaking with jQuery > v1.9.
    if (theme_get_setting('jquery_migrate') == 1) {
        if (intval($jquery['version'], 0) === 3) {
            $js_plugins['migrate'] = [
                'group' => JS_LIBRARY,
                'file' => 'jquery.migrate-3.0.0',
                'version' => '3.0.0',
                'weight' => -96,
            ];
        }
        if (
            intval($jquery['version'], 0) === 2 ||
            (intval($jquery['version'], 0) === 1 &&
                floatval(substr($jquery['version'], 2)) >= 9)
        ) {
            $js_plugins['migrate'] = [
                'group' => JS_LIBRARY,
                'file' => 'jquery.migrate-1.4.1',
                'version' => '1.4.1',
                'weight' => -96,
            ];
        }
    }
    theme_get_setting('backstretch') == 1
        ? ($js_plugins['backstretch'] = [
            'object' => 'backstretch',
            'file' => 'jquery.backstretch',
            'version' => '2.0.4',
        ])
        : null;
    theme_get_setting('d3js') == 1
        ? ($js_plugins['d3'] = [
            'object' => 'd3',
            'cdn' => '//cdnjs.cloudflare.com/ajax/libs/d3/4.2.1/d3.js',
            'file' => 'd3',
            'version' => '4.2.1',
        ])
        : null;
    theme_get_setting('freetile') == 1
        ? ($js_plugins['freetile'] = [
            'file' => 'jquery.freetile',
            'version' => '0.3.1',
        ])
        : null;
    theme_get_setting('flowtype') == 1
        ? ($js_plugins['flowtype'] = [
            'file' => 'jquery.flowtype',
            'version' => '',
        ])
        : null;
    theme_get_setting('jparallax') == 1
        ? ($js_plugins['jparallax'] = [
            'file' => 'jquery.parallax',
            'version' => '2.0',
        ])
        : null;
    theme_get_setting('prism') == 1
        ? ($js_plugins['prism'] = [
            'group' => JS_DEFAULT,
            'object' => 'Prism',
            'file' => 'prism',
            'version' => '1.5.1',
        ])
        : null;
    theme_get_setting('smoove') == 1
        ? ($js_plugins['smoove'] = [
            'object' => 'smoove',
            'file' => 'jquery.smoove',
            'version' => '0.2.8',
        ])
        : null;
    theme_get_setting('snap-svg') == 1
        ? ($js_plugins['snap-svg'] = [
            'file' => 'snap.svg',
            'version' => '0.4.1',
        ])
        : null;
    theme_get_setting('threejs') == 1
        ? ($js_plugins['threejs'] = [
            'object' => 'THREE',
            'cdn' =>
                'https://cdnjs.cloudflare.com/ajax/libs/three.js/r79/three.js',
            'file' => 'three',
            'version' => 'r79',
        ])
        : null;

    if (theme_get_setting('nprogress') == 1) {
        $js_plugins['nprogress'] = [
            'object' => 'NProgress',
            'file' => 'nprogress',
            'scope' => 'critical',
            'weight' => 1,
        ];
        $js_plugins['nprogress_init'] = [
            'file' => 'nprogress_init',
            'scope' => 'critical',
            'weight' => 2,
        ];
    }
    if (theme_get_setting('gsap') == 1) {
        $gsappath =
            CELLULAR_JS_EXT === '.js' ? 'gsap/uncompressed/' : 'gsap/minified/';
        $gsap['cssplugin'] = [
            'object' => 'CSSPlugin',
            'cdn' =>
                '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/plugins/CSSPlugin.min.js',
            'file' => $gsappath . 'plugins/CSSPlugin',
            'version' => '1.19.0',
            'weight' => 1,
        ];
        $gsap['easepack'] = [
            'object' => 'EasePack',
            'cdn' =>
                '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/easing/EasePack.min.js',
            'file' => $gsappath . 'easing/EasePack',
            'version' => '1.15.5',
            'weight' => 2,
        ];
        $gsap['tweenlite'] = [
            'object' => 'TweenLite',
            'cdn' =>
                '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/TweenLite.min.js',
            'file' => $gsappath . 'TweenLite',
            'version' => '1.19.0',
            'weight' => 3,
        ];
        $gsap['jquerygsap'] = [
            'object' => 'gsap',
            'cdn' =>
                '//cdnjs.cloudflare.com/ajax/libs/gsap/1.19.0/jquery.gsap.min.js',
            'file' => $gsappath . 'jquery.gsap',
            'version' => '0.1.12',
            'weight' => 4,
        ];

        $js_plugins = array_merge($js_plugins, $gsap);
    }

    foreach ($js_plugins as &$plugin) {
        $plugin['group'] = !empty($plugin['group'])
            ? $plugin['group']
            : JS_DEFAULT;
        $plugin['file'] = $plugin_path . $plugin['file'] . CELLULAR_JS_EXT;
    }

    return $js_plugins;
}

/*
 * @see file: src/preprocess/plugin_css.inc
 * Functions to add javascript plugins.
 */

/**
 * Stylesheets used by javascript plugins.
 *
 * @return array
 *   Array of stylesheets used by javascript plugins.
 */
function cellular_plugins_css()
{
    $plugin_path = '/lib/css/';
    $plugin_css = [];
    // Plugins available through cellular, styles added based on theme settings.
    // $plugin_css paths are relative to /libraries/cellular/css/
    theme_get_setting('prism') == 1
        ? ($plugin_css['prism'] = [
            'file' => 'prism.css',
            'weight' => 101,
        ])
        : null;

    theme_get_setting('nprogress') == 1
        ? ($plugin_css['nprogress'] = [
            'file' => 'nprogress.css',
            'weight' => 101,
        ])
        : null;

    foreach ($plugin_css as &$plugin) {
        $plugin['group'] = !empty($plugin['group'])
            ? $plugin['group']
            : CSS_DEFAULT;
        $plugin['file'] = $plugin_path . $plugin['file'];
    }

    return $plugin_css;
}

/*
 * @see file: src/preprocess/alter.inc
 * Alter misc. hooks for templates.
 */

/**
 * Implements hook_html_head_alter().
 */
function cellular_html_head_alter(&$head_elements)
{
    // Remove unwanted meta tags.
    unset($head_elements['system_meta_generator']);
}

/**
 * Implements hook_page_alter().
 */
function cellular_page_alter(&$vars)
{
    /*
    $element = $vars['content'];

    $styles = array(
    'style' => array(
    'file' => 'style' . CELLULAR_CSS_EXT,
    'weight' => 99,
    ),
    'drupal' => array(
    'file' => 'drupal' . CELLULAR_CSS_EXT,
    'weight' => 100,
    ),
    // Single stylesheet used to hack old internet explorer quirks.
    // Minimal support for deprecated breowsers is fine imo...
    'ie' => array(
    'file' => 'ie' . CELLULAR_CSS_EXT,
    'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
    'group' => CSS_THEME,
    'weight' => 999,
    ),
    'print' => array(
    'file' => 'print' . CELLULAR_CSS_EXT,
    'media' => 'print',
    'preprocess' => FALSE,
    'group' => CSS_THEME,
    'weight' => 101,
    ),
    );

    $scripts = array(
    'script' => array(
    'file' => 'script' . CELLULAR_JS_EXT,
    'group' => JS_THEME,
    'weight' => 100,
    ),
    'plugins' => array(
    'file' => 'plugins' . CELLULAR_JS_EXT,
    'group' => JS_THEME,
    'weight' => 99,
    ),
    );
    if (theme_get_setting('prism') == 1) {

    }
    // Add to plugin settings to Drupal.settings.
    $cellular_settings = array('cellular' => cellular_js_plugin_settings());

    if (theme_get_setting('cellularui') == 1) {
    $cellular_settings['cellularui'] = TRUE;

    $scripts['cellularui'] = array(
    'object' => 'cellular',
    'file' => 'jquery.cellular-ui' . CELLULAR_JS_EXT,
    'group' => JS_THEME,
    'weight' => 98,
    );

    if (theme_get_setting('social_media_follow') == 1) {
    $cellular_settings['jSocial_follow'] = cellular_social_media_follow();
    }

    if (theme_get_setting('social_media_share') == 1) {
    $cellular_settings['jSocial_share'] = cellular_social_media_share();
    }
    }

    // Add cellular plugin settings to Drupal.settings.
    drupal_add_js(array('cellular' => $cellular_settings), 'setting');
    // Attach styles.
    cellular_attach_css($vars['content'], $styles);
    // Attach scripts.
    cellular_attach_js($vars['content'], $scripts);
    // Add plugin assets.
    cellular_attach_js($vars['content'], cellular_plugins_js(), TRUE);
    cellular_attach_css($vars['content'], cellular_plugins_css(), TRUE);
    // Add critical css inline if set.
    cellular_critical_css($vars);
    // Add to plugin settings to Drupal.settings.
    drupal_add_js(array('cellular' => cellular_js_plugin_settings()), 'setting');
    //dpm($styles);
    //dpm(cellular_plugins_css());
    //dpm($vars);

   */
}

/*
 * @see file: src/preprocess/alter_css.inc
 * Add/Update/Delete stylesheets.
 */

/**
 * Implements hook_css_alter().
 */
function cellular_css_alter(&$css)
{
    // Remove stylesheets based on theme settings.
    cellular_remove_default_css($css);

    // Update jqueryui styles if needed.
    if (theme_get_setting('jquery_update') == 1) {
        cellular_jqueryui_update_css($css);
    }

    //dpm($css);
}

/*
 * @see file: src/preprocess/alter_js.inc
 * Add/Update/Delete javascript.
 */

/**
 * Implements hook_js_alter().
 */
function cellular_js_alter(&$javascript)
{
    $cell_path = drupal_get_path('theme', 'cellular');
    // Update jQuery & jQueryUI.
    if (theme_get_setting('jquery_update') == 1) {
        cellular_jquery_update($javascript);
        cellular_jqueryui_update_js($javascript);
    }

    // Override misc. js
    $override = [];
    if (module_exists('admin_menu')) {
        /*
        $override['admin_menu'] = [
            'default' =>
                drupal_get_path('module', 'admin_menu') . '/admin_menu.js',
            'file' => $cell_path . '/js/admin_menu.js',
            //'version' => '',
        ];
        */
    }
    if (module_exists('ckeditor')) {
        /*
      $override['ckeditor'] = array(
      'default' => drupal_get_path('module', 'ckeditor') . '/ckeditor.config.js',
      'file' => $cell_path . '/js/ckeditor.config.js',
      ); */
    }

    foreach ($override as &$js) {
        $js['group'] = JS_DEFAULT;
        cellular_js_override($javascript, $js);
    }

    //dpm($javascript);
}

/*
 * @see file: src/preprocess/alter_form.inc
 * Alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id)
{
    //dpm($form_state);
    //$form['#validate'][] = 'cellular_form_validate';

    switch ($form['#id']) {
        /* Search page. */
        case 'search-form':
            $form['#attributes']['class'][] = 'site-search';
            break;

        /* Search block. */
        case 'search-block-form':
            $form['#attributes']['class'][] = 'site-search';
            $form[$form_id]['#title'] = t('Search this site');
            $form[$form_id]['#default_value'] = t('Keywords');
            $form[$form_id]['#type'] = 'textfield';
            $form[$form_id]['#size'] = CELLULAR_INPUT_SIZE;
            // Submit button.
            $form['actions']['submit']['#type'] = 'submit';
            $form['actions']['submit']['#value'] = t('Search');
            break;

        /* User Login block. */
        case 'user-login-form':
            $orient = theme_get_setting('login_block_orientation');
            $form['#attributes']['class'][] = $orient;

            switch ($orient) {
                case 'horizontal':
                    break;

                case 'vertical':
                default:
                    $form['actions']['submit']['#attributes']['class'][] =
                        'clearfix';
                    break;
            }

            // Username
            $form['name'] = [
                '#type' => 'textfield',
                '#title' => t('Name'),
                '#default_value' => t('Username'),
                '#size' => CELLULAR_INPUT_SIZE,
            ];
            // Password
            $form['pass'] = [
                '#type' => 'password',
                '#title' => t('Password'),
                '#default_value' => t('Password'),
                '#size' => CELLULAR_INPUT_SIZE,
            ];
            // Submit button
            $form['actions']['submit']['#attributes']['value'] = t('Log in');

            /* Request New Password & Register New Account Links. */
            $login_links = null;
            $user_reg = theme_get_setting('login_block_register');
            $user_pass = theme_get_setting('login_block_password');

            if (!empty($user_reg) || !empty($user_pass)) {
                $login_links = '<div class="login-links">';
                if (!empty($user_reg)) {
                    $login_links .= l(t('Register'), 'user/register', [
                        'attributes' => [
                            'class' => ['register'],
                        ],
                    ]);
                }
                if (!empty($user_pass)) {
                    $login_links .= l(
                        t('Forgotten Password?'),
                        'user/password',
                        [
                            'attributes' => [
                                'class' => ['password'],
                            ],
                        ]
                    );
                }
                $login_links .= '</div>';
            }
            $form['links']['#markup'] = $login_links;
            break;

        /* Comment Form. */
        case 'comment-form':
            $form['comment_body']['und'][0]['#title_display'] = 'invisible';
            $form['comment_body']['und'][0]['#default_value'] = '';
            // Hide unwanted form fields.
            $form['author']['#access'] = false;
            $form['subject']['#access'] = false;
            $form['actions']['preview']['#access'] = false;
            // Customize Submit button.
            $form['actions']['submit']['#value'] = t('Submit');
            $form['actions']['submit']['#attributes']['class'][] = 'right';

            // Remove text format option descriptions.
            $form['comment_body']['#after_build'][] =
                'cellular_form_format_opt';
            break;
    }
}

/*
 * @see file: src/preprocess/preprocess_html.inc
 * HTML preprocess functions.
 */

/**
 * Implements template_preprocess_html().
 */
function cellular_preprocess_html(&$vars)
{
    if (theme_get_setting('cookie_time') == true) {
        $cookies = cellular_cookies();
        $cookies == false ? null : cellular_cookies('set');
    }

    cellular_http_headers();
    cellular_html_attributes($vars);
    cellular_rdf($vars);
    cellular_metatags($vars);
    cellular_favicons();

    cellular_body_attributes($vars);

    $cellular_theme_path = drupal_get_path('theme', 'cellular');

    /* Add javascript. */

    $scripts = [
        'plugins' => [
            'file' => 'plugins' . CELLULAR_JS_EXT,
            'group' => JS_THEME,
            'weight' => 99,
        ],
    ];
    // Add plugin settings to Drupal.settings.
    $cellular_settings = [
        'first_visit' => !$cookies,
        'plugins' => cellular_js_plugin_settings(),
    ];
    if (theme_get_setting('cellularui') == 1) {
        $cellular_settings['ui'] = [
            'enable' => true,
        ];
        $scripts['cellularui'] = [
            'object' => 'cellular',
            'file' => 'jquery.cellular-ui' . CELLULAR_JS_EXT,
            'group' => JS_THEME,
            'weight' => 98,
        ];
        if (theme_get_setting('social_media_follow') == 1) {
            $cellular_settings['ui'][
                'jSocial_follow'
            ] = cellular_social_media_follow();
        }
        if (theme_get_setting('social_media_share') == 1) {
            $cellular_settings['ui'][
                'jSocial_share'
            ] = cellular_social_media_share();
        }
    }
    // Add settings to Drupal.settings.cellular
    drupal_add_js(['cellular' => $cellular_settings], 'setting');
    // Add theme scripts.
    cellular_add_js($scripts);
    // Add plugin scripts.
    cellular_add_js(cellular_plugins_js(), true);
    // Add JS classes to body.
    drupal_add_js('document.body.className += " javascript cellular";', [
        'type' => 'inline',
        'scope' => 'critical',
        'weight' => 1,
    ]);

    /* Add stylesheets. */

    $styles = [
        'style' => [
            'file' => 'style' . CELLULAR_CSS_EXT,
            'weight' => 99,
        ],
        'drupal' => [
            'file' => 'drupal' . CELLULAR_CSS_EXT,
            'weight' => 100,
        ],
        'print' => [
            'file' => 'print' . CELLULAR_CSS_EXT,
            'media' => 'print',
            'preprocess' => false,
            'group' => CSS_THEME,
            'weight' => 101,
        ],
        /*
    // Stylesheet used to hack old internet explorer quirks.
    // Minimal support for deprecated breowsers is fine imo...
    'ie' => array(
      'file' => 'ie' . CELLULAR_CSS_EXT,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'group' => CSS_THEME,
      'weight' => 999,
    ),*/
    ];
    // Add styles.
    cellular_add_css($styles);
    // Add JS Plugin CSS.
    cellular_add_css(cellular_plugins_css(), true);
    // Add critical css inline if set.
    cellular_critical_css($vars);

    /* Additional assets for logged-in users */
    if (user_is_logged_in()) {
        // Add JS.
        drupal_add_js($cellular_theme_path . '/dist/js/user.js', []);
        // Add CSS
        $user_style = [
            'weight' => 999,
            'group' => CSS_THEME,
            'preprocess' => true,
            'media' => 'all',
            'every_page' => true,
            'browsers' => ['IE' => true, '!IE' => true],
        ];
        drupal_add_css(
            $cellular_theme_path . '/dist/css/user.css',
            $user_style
        );
    }
}

/**
 * Set cookie for site, used to load additional resources if needed.
 */
function cellular_cookies($getset = 'get')
{
    $cookie = variable_get('site_name');
    $cookie = preg_replace('/[ \d]+/', '_', strtolower($cookie)) . '_visited';

    switch ($getset) {
        case 'set':
            if (empty($_COOKIE[$cookie])) {
                setcookie(
                    $cookie,
                    true,
                    time() + 86400 * theme_get_setting('cookie_time'),
                    '/',
                    $_SERVER['SERVER_NAME'],
                    false,
                    true
                );
            }
            break;

        case 'get':
        default:
            // $first-visit ?
            return empty($_COOKIE[$cookie]) ? true : false;
    }
}

/**
 * Add HTTP Response Headers.
 */
function cellular_http_headers()
{
    // Set IE compatibility mode.
    drupal_add_http_header('X-UA-Compatible', 'IE=Edge');
    /**
     * Security headers
     */
    drupal_add_http_header('X-Content-Type-Options', 'nosniff');
    // Try to prevent clickjacking.
    drupal_add_http_header('X-Frame-Options', 'DENY');
    // Set IE xss policy.
    drupal_add_http_header('X-XSS-Protection', '1');
    // Limit site sources.
    if (theme_get_setting('secure_sources') == true) {
        $params = [
            theme_get_setting('secure_unsafeinline') ? "'unsafe-inline'" : null,
            theme_get_setting('secure_unsafeeval') ? "'unsafe-eval'" : null,
            "'self'",
        ];
        // Add whitelisted sites from theme settings.
        $sources = preg_split(
            '/[,\s]/',
            theme_get_setting('site_source_whitelist')
        );
        // Whitelist CDN provider if necessary.
        if (theme_get_setting('jquery_cdn') == true) {
            $cdn = cellular_cdn();
            $cdn = preg_match('/\w+(?:\.com)/', $cdn['base_url'], $cdn_base);
            $sources[] = '*.' . $cdn_base[0];
        }
        $params = implode(' ', array_merge($params, $sources));

        // Set security policy header
        drupal_add_http_header(
            'Content-Security-Policy',
            "default-src $params"
        );
    }
}

/**
 * Set html attributes.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_html_attributes(&$vars)
{
    global $language;

    $vars['doctype'] = "<!DOCTYPE html>\n";
    $html_attributes = [
        'lang' => $language->language,
        'xml:lang' => $language->language,
        'dir' => $language->dir,
    ];

    // Check support for RDF, adding namespace if needed.
    if (module_exists('rdf')) {
        // Set namespace.
        $html_attributes['xmlns'] = 'http://www.w3.org/1999/xhtml';
    }

    $vars['html_attributes'] = drupal_attributes($html_attributes);
}

/**
 * Convert xmlns to profile.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_rdf(&$vars)
{
    // Add extra namespaces if needed:
    // $vars['rdf_namespaces'] .= "\nxmlns:og=\"http://opengraphprotocol.org/schema/\"";
    // Check support for RDF & add attributes:
    $vars['rdf_prefixes'] = '';
    if (module_exists('rdf')) {
        // @see http://phase2technology.com/?p=552
        $head_attributes = [];
        $prefixes = [];
        $namespaces = explode("\n", trim($vars['rdf_namespaces']));

        foreach ($namespaces as $name) {
            list($key, $url) = explode('=', $name, 2);
            list($xml, $space) = explode(':', $key, 2);
            unset($xml);
            $url = trim(str_replace('"', '', $url));
            $prefixes[] = "\n" . $space . ': ' . $url;
        }
        $head_attributes['prefix'] = implode(' ', $prefixes);

        $vars['rdf_prefixes'] = drupal_attributes($head_attributes);
    }

    // Check if google+ metatags are present, add emtpy string if not.
    if (!module_exists('metatag_google_plus')) {
        $vars['schemaorg'] = '';
    }
}

/**
 * Add variable classes to <body>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_body_attributes(&$vars)
{
    $body_attributes = [];
    $path = drupal_get_path_alias();
    // Page URL is used to set id & classes of body.
    $aliases = explode('/', $path);
    // Set current page as body id.
    $body_attributes['id'] = array_pop($aliases);

    // Add path-based classes.
    foreach ($aliases as $alias) {
        $body_attributes['class'][] = 'page--' . $alias;
    }
    // Add class for 1st-time visitors.
    if (theme_get_setting('cookie_time') == true) {
        $body_attributes['class'][] = cellular_cookies() ? 'first-visit' : null;
    }
    // Add frontpage class
    drupal_is_front_page() ? ($body_attributes['class'][] = 'frontpage') : null;
    // Add user classes
    if (user_is_logged_in()) {
        foreach ($GLOBALS['user']->roles as $roles => $role) {
            $body_attributes['class'][] = $role;
        }
    }

    $vars['body_attributes'] = drupal_attributes($body_attributes);
}

/**
 * Build links to favicons & apple-touch-icons.
 */
function cellular_favicons()
{
    // Get icon file names from theme settings.
    $settings = [
        'favicon' => theme_get_setting('favicon'),
        'favicon-32' => theme_get_setting('favicon_32'),
        'apple-default' => theme_get_setting('apple_icon_57'),
        'apple-72' => theme_get_setting('apple_icon_72'),
        'apple-114' => theme_get_setting('apple_icon_114'),
        'apple-144' => theme_get_setting('apple_icon_144'),
    ];

    $favicons = [];
    !empty($settings['favicon'])
        ? ($favicons['favicon-16x16'] = [
            'rel' => 'shortcut icon',
            'type' => 'image/x-icon',
            'size' => null,
            'href' => $settings['favicon'],
            'weight' => 95,
        ])
        : null;
    !empty($settings['favicon-32'])
        ? ($favicons['favicon-32x32'] = [
            'rel' => 'shortcut icon',
            'type' => 'image/png',
            'size' => '32x32',
            'href' => $settings['favicon-32'],
            'weight' => 96,
        ])
        : null;
    /* Older iOS devices don't understand the sizes attribute and use
     * whichever value is last, so 'default' is given highest weight.
     */
    !empty($settings['apple-default'])
        ? ($favicons['apple-default'] = [
            'rel' => 'apple-touch-icon',
            'size' => null,
            'href' => $settings['apple-default'],
            'weight' => 100,
        ])
        : null;
    !empty($settings['apple-72'])
        ? ($favicons['apple-72x72'] = [
            'rel' => 'apple-touch-icon',
            'size' => '72x72',
            'href' => $settings['apple-72'],
            'weight' => 99,
        ])
        : null;
    !empty($settings['apple-114'])
        ? ($favicons['apple-114x114'] = [
            'rel' => 'apple-touch-icon',
            'size' => '114x114',
            'href' => $settings['apple-114'],
            'weight' => 98,
        ])
        : null;
    !empty($settings['apple-144'])
        ? ($favicons['apple-144x144'] = [
            'rel' => 'apple-touch-icon',
            'size' => '144x144',
            'href' => $settings['apple-144'],
            'weight' => 97,
        ])
        : null;

    foreach ($favicons as &$favicon) {
        if (isset($favicon)) {
            // Set tag type to <link>
            $favicon['tag'] = 'link';
            // Set href relative to /dist/assets/favicons/
            $favicon['href'] =
                $GLOBALS['base_url'] .
                '/' .
                CURRENT_THEME_PATH .
                '/dist/assets/favicons/' .
                $favicon['href'];
        }
    }

    cellular_build_head_tags($favicons);
}

/**
 * Add meta tags to <head>.
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_metatags(&$vars)
{
    $meta_tags = [
        'viewport' => [
            'tag' => 'meta',
            'name' => 'viewport',
            'content' => 'width=device-width, initial-scale=1',
            'weight' => 0,
        ],
        'robots' => [
            'tag' => 'meta',
            'name' => 'robots',
            'content' => 'index, follow',
            'weight' => 2,
        ],
        'humans' => [
            'tag' => 'link',
            'type' => 'text/plain',
            'rel' => 'author',
            'href' => $GLOBALS['base_url'] . '/humans.txt',
            'weight' => 3,
        ],
    ];

    // Add conditional metatags:
    isset($vars['grddl_profile'])
        ? ($meta_tags['grddl'] = [
            'tag' => 'link',
            'rel' => 'profile',
            'href' => $vars['grddl_profile'],
            'weight' => 4,
        ])
        : null;

    cellular_build_head_tags($meta_tags);
}

/*
 * @see file: src/preprocess/preprocess_node.inc
 * Node preprocess functions.
 */

/**
 * Implements template_preprocess_node().
 */
function cellular_preprocess_node(&$vars)
{
    $node = $vars['elements']['#node'];

    // Set attributes.
    $vars['title_attributes_array']['class'][] = 'node-title';
    $vars['content_attributes_array']['class'][] = 'node-content';
    /* Set additional template variables. */
    // Date node was created.
    $date = "\n<span class=\"day\">" . date('j', $node->created) . "</span>\n";
    $date .= "<span class=\"month\">" . date('M', $node->created) . "</span>\n";
    $date .= "<span class=\"year\">" . date('Y', $node->created) . "</span>\n";
    // Author info
    $aid = user_load($vars['uid']);
    $author = theme('user_picture', ['account' => $aid]);
    $author .= $aid->name;

    // Push variables to the node array.
    $vars['post_date'] = $date;
    $vars['author'] = $author;
    // Set default template suggestions.
    //$vars['theme_hook_suggestions'][] = 'node__' . $vars['type'];
    // Set custom template suggestions.
    switch ($vars['node']->type) {
        case 'forum':
            $vars['theme_hook_suggestions'][] = 'forum_post';
            //$vars['theme_hook_suggestions'] = array('forum_post');
            //$vars['theme_hook_suggestion'] = 'forum_post';
            break;
    }
    /**/
}

/*
 * @see file: src/preprocess/preprocess_page.inc
 * Template page preprocess functions.
 */

/**
 * Implements template_preprocess_page().
 */
function cellular_preprocess_page(&$vars)
{
    // Add template suggestions for custom content types(page--content-type.tpl.php)
    if (isset($vars['node']->type)) {
        $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
    }
    // Automate error pages.
    cellular_error_page($vars);
    // Set main menu to show all links.
    cellular_main_menu($vars);

    /* Page Variables */

    // Link site name to frontpage.
    $vars['page']['logo'] =
        '<div class="logo">' . l($vars['site_name'], '<front>') . '</div>';

    $vars['page']['skiplinks'] = cellular_skiplinks();
    // Set copyright info if provided.
    $copyright = theme_get_setting('copyright');
    $vars['page']['copyright'] = !empty($copyright)
        ? '&copy; ' . date('Y') . " $copyright"
        : '';
 // Set search block variable for addition to page templates.
 $vars['page']['search_box'] = '';
 if (module_exists('search')) {
  $vars['page']['search_box'] = drupal_get_form('search_form');
 }
    //dpm($vars);
}

/**
 *
 */
function cellular_skiplinks()
{
    $output = '';
    $output .= '<div id="skiplinks" class="hidden">';
    $output .= l(t('Skip to main content'), '#content');
    $output .= l(t('Skip to site navigation'), '#main-menu');
    $output .= '</div>';

    return $output;
}

/**
 * Implements template_preprocess_maintenance_page().
 *
 * Duplicate page variables for the maintenance page.
 */
function cellular_preprocess_maintenance_page(&$vars)
{
    // Add critical css inline if set.
    cellular_critical_css($vars);
    // Set main_menu as full-tree or top-level as defined in settings.
    cellular_main_menu($vars);
    // Automate error pages.
    cellular_error_page($vars);
    // Link site name to frontpage.
    $vars['site_name'] = l($vars['site_name'], '<front>');
    // Set Social Media links.
    $vars['page']['social_media_share'] = cellular_social_media_share();
    $vars['page']['social_media_follow'] = cellular_social_media_follow();

    // Set copyright info if provided.
    $copyright = theme_get_setting('copyright');
    $vars['page']['copyright'] = !empty($copyright)
        ? '&copy; ' . date('Y') . " $copyright"
        : '';
    // Set search block variable for addition to page templates.
    $vars['page']['search_box'] = '';
    if (module_exists('search')) {
      $vars['page']['search_box'] = (drupal_get_form('search_form'));
    }
    // Add template suggestion for custom content types(page--content-type.tpl.php)
    if (isset($vars['node']->type)) {
        $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
    }
}

/*
 * @see file: src/preprocess/preprocess_block.inc
 * Block preprocess functions.
 */

/**
 * Implements template_preprocess_block().
 */
function cellular_preprocess_block(&$vars)
{
    $block = $vars['elements']['#block'];
    // Hide block titles in the header regions.
    switch ($block->region) {
        case 'header':
        case 'header-top':
        case 'header-bottom':
            $vars['title_attributes']['class'][] = 'element-invisible';

            break;
    }
}

/*
 * @see file: src/preprocess/preprocess_comments.inc
 *  Cellular comment preprocess functions.
 */

/**
 * Implements template_preprocess_comment_wrapper().
 */
function cellular_preprocess_comment_wrapper(&$vars)
{
    $vars['theme_hook_suggestions'][] = 'comment_wrapper';
    $vars['theme_hook_suggestions'][] =
        'comment_wrapper__' . $vars['node']->type;
    $vars['classes_array'][] = 'clearfix';

    $title = &$vars['content']['comment_form']['#title'];

    switch ($vars['node']->type) {
        case 'forum_topic':
            $title = t('Reply');
            break;
        case 'article':
        default:
            $title = t('Post your comment');
            break;
    }
}

/**
 * Implements template_preprocess_comment().
 */
function cellular_preprocess_comment(&$vars)
{
    $comment = $vars['elements']['#comment'];
    //dpm($comment);
    // Set the template used by comments.
    $vars['theme_hook_suggestions'][] = 'comment';
    $vars['theme_hook_suggestions'][] = 'comment__' . $vars['node']->type;
    $vars['title_attributes_array']['class'][] = 'comment-title';
    $vars['content_attributes_array']['class'][] = 'comment-content';

    switch ($vars['node']->type) {
        case 'forum':
            cellular_preprocess_forum_reply($vars);
            break;
    }

    if (!empty($vars['new'])) {
        $vars['classes_array'][] = 'new';
    }
    $submitted = '';
    if (!empty($vars['author'])) {
        $submitted .= '<span class="comment-author">';
        $submitted .= $vars['picture'];
        $submitted .=
            '<div>' .
            t('Posted by !username', [
                '!username' => $vars['author'],
            ]) .
            '</div>';
        $submitted .= '</span>';
    }

    $submitted .= '<span class="comment-date">' . $vars['created'] . '</span>';

    // No need to link comments...
    $vars['title'] = $comment->subject;

    $vars['submitted'] = $submitted;
}

function cellular_preprocess_forum_reply(&$vars)
{
}

/*
 * @see file: src/preprocess/theme.inc
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
function cellular_links($vars)
{
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
                $heading = [
                    'text' => $heading,
                    // Set the default level of the heading.
                    'level' => 'h2',
                ];
            }
            $output .= '<' . $heading['level'];
            if (!empty($heading['class'])) {
                $output .= drupal_attributes(['class' => $heading['class']]);
            }
            $output .=
                '>' .
                check_plain($heading['text']) .
                '</' .
                $heading['level'] .
                '>';
        }

        $output .= '<ul' . drupal_attributes($attributes) . '>';

        $num_links = count($links);
        $i = 1;

        foreach ($links as $key => $link) {
            $class = [$key];

            // Add first, last and active classes to the list of links to help out themers.
            if ($i == 1) {
                $class[] = 'first';
            }
            if ($i == $num_links) {
                $class[] = 'last';
            }
            if (
                isset($link['href']) &&
                ($link['href'] == $_GET['q'] ||
                    ($link['href'] == '<front>' && drupal_is_front_page())) &&
                (empty($link['language']) ||
                    $link['language']->language == $language_url->language)
            ) {
                $class[] = 'active';
            }
            $output .= '<li' . drupal_attributes(['class' => $class]) . '>';

            if (isset($link['href'])) {
                // Pass in $link as $options, they share the same keys.
                $output .= l(ucfirst($link['title']), $link['href'], $link);
            } elseif (!empty($link['title'])) {
                // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
                if (empty($link['html'])) {
                    $link['title'] = check_plain(ucfirst($link['title']));
                }
                $span_attributes = '';
                if (isset($link['attributes'])) {
                    $span_attributes = drupal_attributes($link['attributes']);
                }
                $output .=
                    '<span' .
                    $span_attributes .
                    '>' .
                    $link['title'] .
                    '</span>';
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
function cellular_field(&$vars)
{
    $output = '';
    $wrap = theme_get_setting('field_wrappers');
    // Render the label, if it's not hidden.
    if (!$vars['label_hidden']) {
        $output .=
            "<h5 class=\"field-label\"" . $vars['title_attributes'] . '>';
        $output .= $vars['label'] . '</h5>';
    }
    // Render the field.
    foreach ($vars['items'] as $delta => $item) {
        $output .= drupal_render($item);
        // Add attributes for each item.
        if (!empty($wrap) && !empty($output)) {
            $output =
                "\n<div" .
                $vars['item_attributes'][$delta] .
                ">\n $output \n</div>";
        }
    }
    // Wrap field if set.
    if ($wrap == 1) {
        $prefix =
            "<div class=\"" .
            $vars['classes'] .
            '"' .
            $vars['attributes'] .
            ">\n";
        $output = $prefix . $output . "\n</div>\n";
    }

    return $output;
}

/**
 * Implements theme_breadcrumb().
 */
function cellular_breadcrumb(&$vars)
{
    $output = null;
    if (theme_get_setting('breadcrumb_display') == 1) {
        if (!empty($vars['breadcrumb'])) {
            $vars['breadcrumb'][] =
                '<span class="active">' . drupal_get_title() . '</span>';
            $breadcrumb = $vars['breadcrumb'];
            // Provide a navigational heading to give context for breadcrumb links to
            // screen-reader users. Make the heading invisible with .element-invisible.
            $output .=
                '<h2 class="element-invisible">' . t('You are here') . '</h2>';
            $output .= theme('item_list', [
                'items' => $breadcrumb,
                'type' => 'ul',
                'attributes' => ['id' => 'breadcrumb'],
            ]);
        }
    }

    return $output;
}

/**
 * Implements theme_file_icon().
 */
function cellular_file_icon(&$vars)
{
    //Use css classes to style output instead of <img>.
    $file = $vars['file'];
    $mime = check_plain($file->filemime);
    $generic_mime = (string) file_icon_map($file);

    // Use generic icons for each category that provides such icons.
    foreach (['audio', 'image', 'text', 'video'] as $category) {
        if (strpos($file->filemime, $category . '/') == 0) {
            $cname = $category;
        }
    }
    if ($generic_mime) {
        $xmime = explode('/', $mime);
        $cname = $xmime[1];
    }
    isset($cname) ? ($cname = $cname) : '';

    return '<span class="icon ' . $cname . '"></span>' . "\n";
}

/**
 * Implements theme_feed_icon().
 */
function cellular_feed_icon(&$vars)
{
    $text = t('Subscribe to !feed-title', [
        '!feed-title' => $vars['title'],
    ]);

    $icon = l($text, $vars['url'], [
        'html' => true,
        'attributes' => [
            'class' => ['icon', 'rss'],
            'title' => $text,
        ],
    ]);

    return $icon;
}

/*
 * @see file: src/preprocess/theme_form.inc
 * Theme markup of form elements.
 */

/**
 * Implements theme_form().
 */
function cellular_form($vars)
{
    $element = $vars['element'];
    // Chrome prevents form submission if a field is required & hidden-
    // Add novalidate to ignore browser & rely on js for client validation.
    $element['#attributes']['novalidate'] = 1;
    // $element['#attributes']['class'][] = 'cell';
    element_set_attributes($element, ['method', 'id']);
    if (!empty($element['#action'])) {
        $element['#attributes']['action'] = drupal_strip_dangerous_protocols(
            $element['#action']
        );
    }
    if (empty($element['#attributes']['accept-charset'])) {
        $element['#attributes']['accept-charset'] = 'UTF-8';
    }
    // Generate markup.
    $output = "\n<form" . drupal_attributes($element['#attributes']) . ">\n";
    $output .= $element['#children'] . "\n</form>\n";

    return $output;
}

/**
 * Implements theme_container().
 */
function cellular_container(&$vars)
{
    $element = $vars['element'];
    // Special handling for form elements.
    if (!empty($element['#array_parents'])) {
        // Add the 'form-wrapper' class.
        $element['#attributes']['class'][] = ['center'];
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
function cellular_button(&$vars)
{
    $element = $vars['element'];
    $element['#attributes']['type'] = 'submit';
    $element['#attributes']['class'][] = 'button';
    $element['#attributes']['class'][] = $element['#parents'][0];

    element_set_attributes($element, ['id', 'name', 'value']);

    if (!empty($element['#attributes']['disabled'])) {
        $element['#attributes']['class'][] = 'disabled';
    }

    return "\n<input" . drupal_attributes($element['#attributes']) . " />\n";
}

/**
 * Implements theme_fieldset().
 */
function cellular_fieldset(&$vars)
{
    $element = $vars['element'];
    $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
    if (!empty($element['#title'])) {
        $output .= '<legend>' . $element['#title'] . "</legend>\n";
    }
    if (!empty($element['#description'])) {
        $output .=
            '<div class="description">' .
            t($element['#description']) .
            "</div>\n";
    }
    // Add form elements.
    $output .= $element['#children'];
    $output .= !empty($element['#value']) ? $element['#value'] . "\n" : null;
    $output .= "</fieldset>\n";

    return $output;
}

/**
 * Implements theme_checkboxes().
 */
function cellular_checkboxes(&$vars)
{
    return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_radios().
 */
function cellular_radios(&$vars)
{
    return cellular_xinputs($vars['element']);
}

/**
 * Implements theme_checkbox().
 */
function cellular_checkbox(&$vars)
{
    return cellular_xinput($vars['element'], 'checkbox');
}

/**
 * Implements theme_radio().
 */
function cellular_radio(&$vars)
{
    return cellular_xinput($vars['element'], 'radio');
}

/**
 * Implements theme_select().
 */
function cellular_select(&$vars)
{
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
function cellular_textfield(&$vars)
{
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
function cellular_textarea(&$vars)
{
    $element = $vars['element'];
    $attributes = cellular_form_element_attributes($element);
    $attributes['placeholder'] = t($element['#default_value']);
    $attributes['cols'] = !empty($element['#cols']) ? $element['#cols'] : 60;
    $attributes['rows'] = !empty($element['#rows']) ? $element['#rows'] : 5;

    return '<textarea' . drupal_attributes($attributes) . '></textarea>';
}
/*
 * @see file: src/preprocess/theme_pager.inc
 * Generate & theme drupal pager.
 */

/**
 * Implements theme_pager().
 */
function cellular_pager($vars)
{
    $output = '';
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
    if ($pager_max > 1) {
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
        $li_first = theme('pager_first', [
            'text' => isset($tags[0]) ? $tags[0] : t('First'),
            'element' => $element,
            'parameters' => $parameters,
        ]);
        $li_previous = theme('pager_previous', [
            'text' => isset($tags[1]) ? $tags[1] : t('Previous'),
            'element' => $element,
            'interval' => 1,
            'parameters' => $parameters,
        ]);
        $li_next = theme('pager_next', [
            'text' => isset($tags[3]) ? $tags[3] : t('Next'),
            'element' => $element,
            'interval' => 1,
            'parameters' => $parameters,
        ]);
        $li_last = theme('pager_last', [
            'text' => isset($tags[4]) ? $tags[4] : t('Last'),
            'element' => $element,
            'parameters' => $parameters,
        ]);

        if ($li_first) {
            $items[] = [
                'class' => ['pager-first'],
                'data' => $li_first,
            ];
        }
        if ($li_previous) {
            $items[] = [
                'class' => ['pager-previous'],
                'data' => $li_previous,
            ];
        }

        // When there is more than one page, create the pager list.
        if ($i != $pager_max) {
            if ($i > 1) {
                $items[] = [
                    'class' => ['pager-ellipsis'],
                    'data' => '…',
                ];
            }
            // Now generate the actual pager piece.
            for (; $i <= $pager_last && $i <= $pager_max; $i++) {
                if ($i < $pager_current) {
                    $items[] = [
                        'class' => ['pager-item'],
                        'data' => theme('pager_previous', [
                            'text' => $i,
                            'element' => $element,
                            'interval' => $pager_current - $i,
                            'parameters' => $parameters,
                        ]),
                    ];
                }
                if ($i == $pager_current) {
                    $items[] = [
                        'class' => ['pager-current'],
                        'data' => $i,
                    ];
                }
                if ($i > $pager_current) {
                    $items[] = [
                        'class' => ['pager-item'],
                        'data' => theme('pager_next', [
                            'text' => $i,
                            'element' => $element,
                            'interval' => $i - $pager_current,
                            'parameters' => $parameters,
                        ]),
                    ];
                }
            }
            if ($i < $pager_max) {
                $items[] = [
                    'class' => ['pager-ellipsis'],
                    'data' => '…',
                ];
            }
        }
        // End generation.
        if ($li_next) {
            $items[] = [
                'class' => ['pager-next'],
                'data' => $li_next,
            ];
        }
        if ($li_last) {
            $items[] = [
                'class' => ['pager-last'],
                'data' => $li_last,
            ];
        }

        $output .= '<h2 class="element-invisible">' . t('Pages') . '</h2>';
        $output .= theme('item_list', [
            'items' => $items,
            'attributes' => [
                'class' => ['pager'],
            ],
        ]);

        return $output;
    }
}

/*
 * @see file: src/preprocess/panels.inc
 * Custom Panels functions.
 */

/**
 * Implements theme_panels_default_style_render_region().
 */
function cellular_panels_default_style_render_region($vars)
{
    // Remove the panel separator.
    return implode('', $vars['panes']);
}

/*
 * @see file: src/preprocess/social.inc
 * Generate social media links.
 */

/**
 * Generate links for social media.
 *
 * @param array $links
 *   Array of links to add.
 * @param array $parent
 *   Media block array used to wrap links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_build_links($links, $parent)
{
    $output = '';
    foreach ($links as $link) {
        if (!empty($link['tag'])) {
            // Use preformatted html if set.
            $output .= "\n " . $link['tag'] . "\n";
        } else {
            // Or create link using key's attributes:
            if (!empty($link['url'])) {
                $text = $parent['link_text'] . $link['name'];
                $output .=
                    l(t($text), $link['url'], [
                        'attributes' => [
                            'class' => [$parent['link_class'], $link['class']],
                        ],
                    ]) . "\n";
            }
        }

        if (!empty($link['script'])) {
            // Add script if provided.
            drupal_add_js($link['script'], [
                'type' => 'inline',
                'group' => JS_THEME,
                'weight' => isset($link['weight']) ? $link['weight'] : 100,
            ]);
        }
    }

    return $output;
}

/**
 * Collect Social Media share settings.
 *
 * @param string $type
 *   String used to select the array to return ("follow" || "share").
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_settings($type)
{
    switch ($type) {
        case 'follow':
            $output = [
                'title' => theme_get_setting('sm_follow_title'),
                'fb' => theme_get_setting('follow_facebook'),
                'google' => theme_get_setting('follow_google_plus'),
                'twitter' => theme_get_setting('follow_twitter'),
                'linkedin' => theme_get_setting('follow_linkedin'),
                'github' => theme_get_setting('follow_github'),
            ];
            break;

        case 'share':
            $output = [
                'title' => theme_get_setting('sm_share_title'),
                'fb' => theme_get_setting('share_facebook'),
                'google' => theme_get_setting('share_google_plus'),
                'twitter' => theme_get_setting('share_twitter'),
                'linkedin' => theme_get_setting('share_linkedin'),
                'pinterest' => theme_get_setting('share_pinterest'),
                'reddit' => theme_get_setting('share_reddit'),
                'digg' => theme_get_setting('share_digg'),
                'stumbleupon' => theme_get_setting('share_stumbleupon'),
                'tumblr' => theme_get_setting('share_tumblr'),
            ];
            break;
    }

    return $output;
}

/**
 * Collect Social Media URLs.
 *
 * @param string $type
 *   String ("follow" || "share") used to select the array to return.
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_urls($type)
{
    switch ($type) {
        case 'follow':
            $output = [
                'facebook' => theme_get_setting('follow_facebook_url'),
                'google' => theme_get_setting('follow_google_plus_url'),
                'twitter' => theme_get_setting('follow_twitter_url'),
                'linkedin' => theme_get_setting('follow_linkedin_url'),
                'github' => theme_get_setting('follow_github_url'),
            ];
            break;

        case 'share':
            $output = [
                'facebook' => theme_get_setting('share_facebook_url'),
                'google' => theme_get_setting('share_google_plus_url'),
                'twitter' => theme_get_setting('share_twitter_url'),
                'linkedin' => theme_get_setting('share_linkedin_url'),
                'pinterest' => theme_get_setting('share_pinterest_url'),
                'reddit' => theme_get_setting('share_reddit_url'),
            ];
    }

    return $output;
}

/**
 * Generate Social media follow links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_follow()
{
    $set = cellular_sm_settings('follow');
    $url = cellular_sm_urls('follow');

    $links = [];

    $set['fb'] == 1
        ? ($links['facebook'] = [
            'title' => 'Facebook',
            'url' => $url['facebook'],
        ])
        : null;
    $set['google'] == 1
        ? ($links['google'] = [
            'title' => 'Google',
            'url' => $url['google'],
        ])
        : null;
    $set['twitter'] == 1
        ? ($links['twitter'] = [
            'title' => 'Twitter',
            'url' => $url['twitter'],
        ])
        : null;
    $set['linkedin'] == 1
        ? ($links['linkedin'] = [
            'title' => 'LinkedIn',
            'url' => $url['linkedin'],
        ])
        : null;
    $set['github'] == 1
        ? ($links['github'] = [
            'title' => 'Github',
            'url' => $url['github'],
        ])
        : null;

    if (empty($links)) {
        $links = null;
    }

    return $links;
}

/**
 * Generate Social media share links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_share()
{
    global $base_url;
    $set = cellular_sm_settings('share');
    $links = [];

    $set['fb'] == 1 ? ($links[] = 'facebook') : null;
    $set['google'] == 1 ? ($links[] = 'google') : null;
    $set['twitter'] == 1 ? ($links[] = 'twitter') : null;
    $set['linkedin'] == 1 ? ($links[] = 'linkedin') : null;
    $set['pinterest'] == 1 ? ($links[] = 'pinterest') : null;
    $set['reddit'] == 1 ? ($links[] = 'reddit') : null;
    $set['digg'] == 1 ? ($links[] = 'digg') : null;
    $set['stumbleupon'] == 1 ? ($links[] = 'stumbleupon') : null;
    $set['tumblr'] == 1 ? ($links[] = 'tumblr') : null;

    if (empty($links)) {
        $links = null;
    }

    return $links;
}

/*
 * @see file: src/preprocess/views.inc
 * Preprocess functions for Views.
 */

/**
 * Implements template_preprocess_views_view().
 *
 * @param array $vars
 *   Associative array of variables to merge with defaults from the theme registry.
 */
function cellular_preprocess_views_view(&$vars)
{
    // Set hooks for view preprocess functions.
    if (isset($vars['view']->name)) {
        $function = 'cellular_preprocess_views_view__' . $vars['view']->name;
        if (function_exists($function)) {
            $function($vars);
        }
    }
}

/*
 * @see file: src/preprocess/process.inc
 * Cellular process functions.
 */

/**
 * Implements template_process_html().
 */
function cellular_process_html(&$vars)
{
    // Add vars for critical scoped js
    $vars['critical_js'] = drupal_get_js('critical');
    // Get updated styles.
    $vars['styles'] = drupal_get_css();
    //dpm($vars);
}
/**
 * Implements template_process_page().
function cellular_process_page(&$vars) {
   //dpm($vars);
}
 */
