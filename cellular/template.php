<?php
/**
 * @file
 * Set global vars & load all functions for templates.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/inc';
$include = array(
  // 'dev-functions.inc',
  'functions.inc',
  'social.inc',
  'preprocess.inc',
  'theme.inc',
  'theme_form.inc',
  'theme_pager.inc',
  'alter.inc',
  'alter_form.inc',
  'alter_css.inc',
  'alter_js.inc',
  'process.inc',
);

foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

$GLOBALS['theme_path'] = cellular_theme_path();
$GLOBALS['cellular_lib'] = $GLOBALS['base_url'] . '/sites/all/libraries/cellular';
