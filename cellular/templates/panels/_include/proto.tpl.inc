<?php

/**
 * @file
 * Template for prototype panel layouts.
 *
 *  Variables:
 *  $content['left']
 *  $content['right']
 *
 *  $content['center']
 *
 *  $content['midleft']
 *  $content['midright']
 */

$content = $content ?? array();
$attributes = $attributes ?? '';
$classes = $classes ?? '';
// Format markup for the css id.
$id = !empty($css_id) ? " id=\"$css_id\"" : '';
?>
<div<?php print "$id class=\"panels cell $classes\" $attributes"; ?>>
  <?php
  foreach ($content as $name => $markup) :
    if (!empty($content[$name])) :
      ?>
      <div<?php print drupal_attributes($region_attributes[$name]) ?>>
        <?php print $markup ?>
      </div>
      <?php
    endif;
  endforeach;
  ?>
</div>
