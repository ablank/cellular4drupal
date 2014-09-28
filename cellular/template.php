<?php
/**
 * @file
 * Load all functions for templates & set theme constants.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/preprocess';
$include = array(
  'fn.inc',
  'fn.css.inc',
  'fn.menu.inc',
  'fn.js.inc',
  'fn.jquery.inc',
  'fn.menu.inc',
  'fn.preprocess.inc',
  'alter.inc',
  'alter.css.inc',
  'alter.form.inc',
  'alter.js.inc',
  'preprocess.inc',
  'theme.inc',
  'theme.form.inc',
  'theme.pager.inc',
  'social.inc',
  'process.inc',
);

foreach ($include as $i) {
  require_once $inc_path . '/' . $i;
}

define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');
