<?php
/**
 * @file
 * Template for the Inset Left column panel layout.
 */
/* Variables:
 *  $content['inset']
 *  $content['header']
 *  $content['body']
 *  $content['footer']
 */

$id = !empty($css_id) ? " id=\"$css_id\"" : '';
?>

<div<?php print "$id class=\"panels cell $classes\" $attributes"; ?>>
  <?php
  foreach ($content as $name => $region):
    if (!empty($region)):
      ?>
      <div<?php print drupal_attributes($region_attributes[$name]) ?>>
        <?php print $region ?>
      </div>
      <?php
    endif;
  endforeach;
  ?>
</div>