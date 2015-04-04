<?php
/**
 * @file
 * Add/Update/Delete stylesheets.
 */

/**
 * Cellular hook_css_alter().
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_css_alter(array &$css) {
  // Remove stylesheets based on theme settings.
  cellular_remove_default_css($css);

  $ext = theme_get_setting('min_style') == 1 ? '.min.css' : '.css';
  // Add stylesheets to theme.
  // Paths are relative to /yourTheme/css/
  $add_css = array(
    'drupal' => array(
      'file' => 'drupal' . $ext,
      'weight' => 10,
    ),
    'style' => array(
      'file' => 'style' . $ext,
      'weight' => 11,
    ),
    'print' => array(
      'file' => 'print' . $ext,
      'media' => 'print',
      'weight' => 100,
      'preprocess' => FALSE,
    ),
    'ie' => array(
      // Single stylesheet used to hack old internet explorer quirks.
      // Minimal support for deprecated breowsers is fine imo...
      'file' => 'ie' . $ext,
      'browsers' => array('IE' => 'lt IE 10', '!IE' => FALSE),
      'weight' => 999,
    ),
  );
  cellular_add_css($css, $add_css);

  // Add js plugin styles.
  $plugins = cellular_plugin_css();
  // Update jqueryui styles if needed.
  if (theme_get_setting('jquery_update') == 1) {
    cellular_jqueryui_update_css($css);
  }
  !empty($plugins) ? cellular_add_css($css, $plugins, TRUE) : NULL;
}

/**
 * Remove core stylesheets based on theme settings.
 *
 * @param array $css
 *   Associative array of stylesheets to merge with defaults from theme registry.
 */
function cellular_remove_default_css(array &$css) {
  // Nuke all css not a member of group CSS_THEME:
  $exclude = array();
  if (theme_get_setting('remove_drupal_css') === 'theme_only') {
    foreach ($css as $key => $value) {
      if ($value['group'] !== CSS_THEME
      // Keep admin stuff.
      && ($key !== 'admin_menu' || $key !== 'toolbar')
      ) {
        unset($css[$key]);
      }
    }
  }
  // 86 SYSTEM_CSS.
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
        'system.menus.css',
        'system.messages.css',
        'system.theme.css',
      ),
      'block' => 'block.css',
      'colorbox' => 'styles/default/colorbox_style.css',
      'comment' => 'comment.css',
      'field' => 'theme/field.css',
      'filter' => 'filter.css',
      'help' => 'help.css',
      'menu' => 'menu.css',
      'node' => 'node.css',
      'panels' => 'css/panels.css',
      'search' => 'search.css',
      'shortcut' => 'shorcut.css',
      'user' => 'user.css',
    );

    cellular_remove_css($css, $exclude);
  }
}
