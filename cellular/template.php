<?php
/**
 * @file
 * Set global vars & load all functions for templates.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/preprocess';
$include = array(
  'fn.cellular/fn.inc',
  'fn.cellular/fn.javascript.inc',
  'fn.cellular/fn.stylesheets.inc',
  'fn.cellular/fn.jquery.inc',
  'fn.cellular/fn.menu.inc',
  'fn.cellular/fn.preprocess.inc',
  'alter/alter.inc',
  'alter/alter.form.inc',
  'alter/alter.css.inc',
  'alter/alter.js.inc',
  'preprocess.inc',
  'theme/theme.inc',
  'theme/theme.form.inc',
  'theme/theme.pager.inc',
  'fn.cellular/fn.social.inc',
);

foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');
