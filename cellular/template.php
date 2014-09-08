<?php
/**
 * @file
 * Set global vars & load all functions for templates.
 */

$inc_path = drupal_get_path('theme', 'cellular') . '/inc';
$include = array(
  'cellular/fn.inc',
  'cellular/fn.javascript.inc',
  'cellular/fn.stylesheets.inc',
  theme_get_setting('social_media_follow') == 1 ? 
  'cellular/fn.jquery.inc' : NULL,
  'cellular/fn.menu.inc',
  'cellular/fn.preprocess.inc',
  'alter/alter.inc',
  'alter/alter.form.inc',
  'alter/alter.css.inc',
  'alter/alter.js.inc',
  'preprocess.inc',
  'theme/theme.inc',
  'theme/theme.form.inc',
  'theme/theme.pager.inc',
  theme_get_setting('social_media_follow') == 1 ||
  theme_get_setting('social_media_share') == 1 ? 
  'cellular/social.inc' : NULL,
);

foreach ($include as $i) {
  require_once($inc_path . '/' . $i);
}

$GLOBALS['cellular_lib'] = $GLOBALS['base_url'] . '/sites/all/libraries/cellular';
