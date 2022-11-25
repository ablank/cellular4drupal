<?php
/**
 * @file
 * Initialize constants & globals
 */

/* Cellular defined constants:
'CURRENT_THEME_PATH' : (string) Path to the active theme dirrectory
                    i.e.: CURRENT_THEME_PATH . '/css/lib/thing.css';
'CELLULAR_CSS_EXT' : (string) File extension for stylesheets (.min.css or .css).
                    default: .css
'CELLULAR_JS_EXT' : (string) File extension for javascript (.min.js or .js).
                    default: .js
'CELLULAR_INPUT_SIZE' : (int) Size of the default textfield input.
                        default: 20
// May convert to use Libraries module at some point...
'CELLULAR_LIB' : (string) Path to the Cellular library.
                  default: /sites/all/libraries/cellular

// These values can be overridden if necessary by implementing the php runkit,
 * i.e.:
 runkit_constant_redefine('CELLULAR_LIB', '/path/to/lib');
*/