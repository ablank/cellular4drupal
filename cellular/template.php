<?php
/**
 * @file
 * Set global vars & load all functions for templates.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/preprocess';
$include = array(
  'fn.inc',
  'fn.javascript.inc',
  'fn.stylesheets.inc',
  'fn.jquery.inc',
  'fn.menu.inc',
  'fn.preprocess.inc',
  'alter.inc',
  'alter.form.inc',
  'alter.css.inc',
  'alter.js.inc',
  'preprocess.inc',
  'theme.inc',
  'theme.form.inc',
  'theme.pager.inc',
  'fn.social.inc',
  'process.inc',
);

foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');
