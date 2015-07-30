<?php
/**
 * @file
 * Custom Panels functions.
 */

/**
 * Alter the default Panels markup to remove the panel separator.
 */
function cellular_panels_default_style_render_region($vars) {
  
  return implode('', $vars['panes']);
}
