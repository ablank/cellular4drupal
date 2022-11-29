<?php

/**
 * @file
 * Cellular stylesheet functions.
 */

/**
 * Attach scripts to a render array, using a CDN if provided.
 *
 * @param array $css
 *   Default array of stylesheets.
 * @param array $array
 *   Associative array of stylesheet data to add.
 * @param bool $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_attach_css(&$vars, $array, $cellular = FALSE) {
  foreach ($array as $style) {
    // Set data source as CDN or local host.
    if (isset($style['cdn'])) {
      $data = $style['cdn'];
    }
    elseif (isset($style['file'])) {
      $data = $cellular === TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH . '/css/';
      $data .= $style['file'];
    }
    if (!empty($data)) {
      // Set stylesheet properties.
      $style['data'] = $data;
      $style['preprocess'] = $style['preprocess'] ?? TRUE;
      $style['every_page'] = $style['every_page'] ?? TRUE;
      $style['group'] = $style['group'] ?? CSS_THEME;
      $style['weight'] = $style['weight'] ?? 1;
      $style['type'] = isset($style['cdn']) ? 'external' : 'file';
      $style['media'] = $style['media'] ?? 'all';
      $style['browsers'] = $style['browsers'] ?? array('IE' => TRUE, '!IE' => TRUE);
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
 * @param bool $cellular
 *   Reference cellular library if TRUE.    * // &$css.
 */
function cellular_add_css($array, $cellular = FALSE) {
  $type = 'file';
  foreach ($array as $style) {
    // Set data source as CDN or local host.
    if (!empty($style['cdn'])) {
      $data = $style['cdn'];
    }
    elseif (!empty($style['file'])) {
      $data = $cellular === TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH . '/css/';
      $data .= $style['file'];
    }
    else {
      $data = $style['data'];
    }
    // Set style attributes.
    if (!empty($style['type'])) {
      $type = $style['type'];
    }
    else {
      if (!empty($style['cdn'])) {
        $type = 'external';
      }
      elseif (!empty($style['file'])) {
        $type = 'file';
      }
    }
    if (!empty($data)) {
      // Set stylesheet properties.
      $style['type'] = $type;
      $style['group'] = !empty($style['group']) ? $style['group'] : CSS_THEME;
      $style['weight'] = !empty($style['weight']) ? $style['weight'] : 1;
      $style['every_page'] = !empty($style['every_page']) ? $style['every_page']
        : TRUE;
      $style['preprocess'] = !empty($style['preprocess']) ? $style['preprocess']
        : TRUE;
      $style['media'] = $style['media'] ?? 'all';
      $style['browsers'] = $style['browsers'] ?? array('IE' => TRUE, '!IE' => TRUE);

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
 * @param bool $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_override_css(&$css, $style, $cellular = FALSE) {
  $ocss = $style['default'];
  // Only override if style is being called.
  if (isset($css[$ocss])) {
    if (isset($style['cdn'])) {
      // If cdn is provided, set data to external source.
      $data = $style['cdn'];
      // Set key to data to prevent multiple calls to same source.
      $ocss = $data;
    }
    else {
      $data = $cellular === TRUE ? CELLULAR_LIB : '';
      // Or set data to local file.
      $data .= $style['file'];
    }
    // Set stylesheet properties.
    $css[$ocss]['data'] = $data;
    $css[$ocss]['preprocess'] = $style['preprocess'] ?? TRUE;
    $css[$ocss]['every_page'] = $style['every_page'] ?? TRUE;
    $css[$ocss]['group'] = $style['group'] ?? CSS_DEFAULT;
    $css[$ocss]['weight'] = $style['weight'] ?? 0;
    $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
    $css[$ocss]['media'] = $style['media'] ?? 'all';
    $css[$ocss]['browsers'] = $style['browsers'] ?? array('IE' => TRUE, '!IE' => TRUE);
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
function cellular_remove_css(&$css, $exclude) {
  foreach ($exclude as $module => $stylesheet) {
    // Remove multiple stylesheets attached by module.
    if (is_array($stylesheet)) {
      foreach ($stylesheet as $style) {
        $index = drupal_get_path('module', $module) . '/' . $style;
        $css[$index] = NULL;
        unset($css[$index]);
      }
    }
    // Remove individual module stylesheet.
    else {
      $index = drupal_get_path('module', $module) . '/' . $stylesheet;
      $css[$index] = NULL;
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
function cellular_remove_default_css(&$css) {
  // Remove selected system & module css.
  if (theme_get_setting('remove_drupal_css') === 'select') {
    // Select module css to exclude.
    $exclude = array(
      'system' => array(
        'system.base.css',
        'system.messages.css',
        'system.theme.css',
        'system.menus.css',
      ),
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
    );
    // Contrib.
    $contrib = array(
      'admin_menu' => array(
        'admin_menu.css',
        'admin_menu_toolbar/admin_menu_toolbar.css',
      ),
      'calendar' => array(
        'css/calendar.css',
        'css/calendar_multiday.css',
      ),
      'colorbox' => 'styles/default/colorbox_style.css',
      'panels' => 'css/panels.css',
      'views' => 'css/views.css',
      'webform' => 'css/webform.css',
    );
    foreach ($contrib as $module => $styles) {
      if (module_exists($module)) {
        $exclude[$module] = $styles;
      }
    }
    cellular_remove_css($css, $exclude);
  }
  else {
    $exclude = array();
    // Nuke CSS_SYSTEM.
    if (theme_get_setting('remove_drupal_css') === 'system') {
      foreach ($css as $key => $value) {
        if ($value['group'] === CSS_SYSTEM) {
          $exclude[] = array($key => $value);
        }
      }
    }
    // Nuke SYSTEM_CSS.
    if (theme_get_setting('remove_drupal_css') === 'module') {
      foreach ($css as $key => $value) {
        if ($value['group'] === CSS_DEFAULT) {
          $exclude[] = array($key => $value);
        }
      }
    }
    // Nuke all css not a member of group CSS_THEME:
    if (theme_get_setting('remove_drupal_css') === 'theme_only') {
      foreach ($css as $key => $value) {
        if ($value['group'] !== CSS_THEME) {
          $exclude[] = array($key => $value);
        }
      }
    }
    $exclude = drupal_array_merge_deep_array($exclude);

    foreach ($exclude as $module => $data) {
      $css[$data['data']] = NULL;
      unset($css[$data['data']]);
    }
  }
}

/**
 * Add critical styles (above the fold) inline.
 *
 * @see http://fourword.fourkitchens.com/article/use-grunt-and-advagg-inline-critical-css-drupal-7-theme
 */
function cellular_critical_css($vars) {
  if (theme_get_setting('inline_critical_css') == 1) {
    $ext = CELLULAR_CSS_EXT;
    $critical_opts = array(
      'type' => 'inline',
      'scope' => 'critical',
      'group' => CSS_SYSTEM,
      'weight' => -1000,
      'preprocess' => FALSE,
    );

    if ($vars['is_front'] == 1) {
      $critical_file = 'critical-front' . $ext;
    }
    else {
      $critical_file = 'critical' . $ext;
    }

    // Add the stylesheet inline.
    drupal_add_css(file_get_contents(CURRENT_THEME_PATH . '/css/' . $critical_file), $critical_opts);
  }
}
