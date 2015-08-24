<?php
/**
 * @file
 * Template for a 4 equal columns (25%/25%/25%/25%) panel layout.
 */
/* Variables:
 * $css_id: An optional CSS id to use for the layout.
 *
 *  $content['left']
 *  $content['mid_left']
 *  $content['mid_right']
 *  $content['right']
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;

?> class="panels cell <?php print ($classes); ?>">

    <?php if ($content['left']): ?>
    <div class="panel-left cell-25">
    <?php print $content['left']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['mid_left']): ?>
    <div class="panel-mid-left cell-25">
    <?php print $content['mid_left']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['mid_right']): ?>
    <div class="panel-mid-right cell-25">
    <?php print $content['mid_right']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['right']): ?>
    <div class="panel-right cell-25">
    <?php print $content['right']; ?>
    </div>
<?php endif; ?>

</div>
