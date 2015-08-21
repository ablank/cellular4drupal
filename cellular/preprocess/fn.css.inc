<?php
/**
 * @file
 * Cellular stylesheet functions.
 */

/**
 * Add array of stylesheets to $css, using a CDN if provided.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 * @param array $array
 *   Associative array of stylesheets data.
 * @param boolean $cellular
 *   Reference cellular library if TRUE.
 */
function cellular_add_css(&$css, $array, $cellular = FALSE) {
  foreach ($array as $style) {
    // Set data source as CDN or local host.
    if (isset($style['cdn'])) {
      $data = $style['cdn'];
    }
    elseif (isset($style['file'])) {
      $data = $cellular === TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH;
      $data .= '/css/' . $style['file'];
    }
    if (!empty($data)) {
      // Set stylesheet properties.
      $style['data'] = $data;
      $style['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : TRUE;
      $style['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
      $style['group'] = isset($style['group']) ? $style['group'] : CSS_THEME;
      $style['weight'] = isset($style['weight']) ? $style['weight'] : 1;
      $style['type'] = isset($style['cdn']) ? 'external' : 'file';
      $style['media'] = isset($style['media']) ? $style['media'] : 'all';
      $style['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);
      // Add stylesheet to $css.
      $css[$data] = $style;
    }
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
        unset($css[drupal_get_path('module', $module) . '/' . $style]);
      }
    }
    // Remove individual module stylesheet.
    else {
      unset($css[drupal_get_path('module', $module) . '/' . $stylesheet]);
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
      $path = $cellular === TRUE ? CELLULAR_LIB : CURRENT_THEME_PATH;
      // Or set data to local file.
      $data = $path . '/css/' . $style['file'];
    }
    // Set stylesheet properties.
    $css[$ocss]['data'] = $data;
    $css[$ocss]['preprocess'] = isset($style['preprocess']) ? $style['preprocess'] : FALSE;
    $css[$ocss]['every_page'] = isset($style['every_page']) ? $style['every_page'] : TRUE;
    $css[$ocss]['group'] = isset($style['group']) ? $style['group'] : CSS_DEFAULT;
    $css[$ocss]['weight'] = isset($style['weight']) ? $style['weight'] : 0;
    $css[$ocss]['type'] = isset($style['cdn']) ? 'external' : 'file';
    $css[$ocss]['media'] = isset($style['media']) ? $style['media'] : 'all';
    $css[$ocss]['browsers'] = isset($style['browsers']) ? $style['browsers'] : array('IE' => TRUE, '!IE' => TRUE);
  }
}

/**
 * Remove core stylesheets based on theme settings.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_remove_default_css(&$css) {
  $exclude = array();
  // Nuke all css not a member of group CSS_THEME:
  if (theme_get_setting('remove_drupal_css') === 'theme_only') {
    foreach ($css as $key => $value) {
      $keep = array(
        'toolbar',
        'admin_menu',
        'admin_menu_toolbar'
      );

      if (!array_key_exists($key, $keep) && $value['group'] !== CSS_THEME) {
        unset($css[$key]);
      }
    }
  }
  // Nuke SYSTEM_CSS.
  if (theme_get_setting('remove_drupal_css') === 'system') {
    foreach ($css as $key => $value) {
      if ($value['group'] === CSS_SYSTEM) {
        unset($css[$key]);
      }
    }
  }
  // Remove selected system & module css.
  if (theme_get_setting('remove_drupal_css') === 'select') {
    // Select module css to exclude.
    $exclude = array(
      'system' => array(
        'system.base.css',
        //'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block' => 'block.css',
      'colorbox' => 'styles/default/colorbox_style.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'file' => 'file.css',
      'image' => 'image.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'media' => 'css/media.css',
      'node' => 'node.css',
      'panels' => 'css/panels.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
}

/**
 * Add critical styles (above the fold) inline.
 * @see http://fourword.fourkitchens.com/article/use-grunt-and-advagg-inline-critical-css-drupal-7-theme
 */
function cellular_critical_css($vars) {
  if (theme_get_setting('inline_critical_css') == 1) {
    $ext = CELLULAR_CSS_EXT;
    $critical_opts = array(
      'type' => 'inline',
      'scope' => 'header',
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
