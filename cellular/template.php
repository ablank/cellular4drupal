<?php
/**
 * @file
 * Set global vars & load all functions for templates.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/inc';
$include = array(
  // 'dev-functions.inc',
  'fn.inc',
  'fn.javascript.inc',
  'fn.jquery.inc',
  'fn.preprocess.inc',
  'alter.inc',
  'alter.form.inc',
  'alter.css.inc',
  'alter.js.inc',
  'preprocess.inc',
  'theme.inc',
  'theme.form.inc',
  'theme.pager.inc',
  'social.inc',
);

foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

$GLOBALS['theme_path'] = cellular_theme_path();
$GLOBALS['cellular_lib'] = $GLOBALS['base_url'] . '/sites/all/libraries/cellular';
