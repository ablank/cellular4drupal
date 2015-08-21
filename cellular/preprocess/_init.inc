<?php
/**
 * @file
 * Initialize constants & global variables.
 */

define('CURRENT_THEME_PATH', cellular_theme_path());
define('CELLULAR_CSS_EXT', cellular_ext('css'));
define('CELLULAR_JS_EXT', cellular_ext('js'));
define('CELLULAR_INPUT_SIZE', 20);
// May convert to use Libraries module at some point...
define('CELLULAR_LIB', $GLOBALS['base_url'] . '/sites/all/libraries/cellular');
