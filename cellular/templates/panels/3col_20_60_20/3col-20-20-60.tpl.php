<?php
/**
 * @file
 * Template for a 3 equal columns (20%/20%/60%) panel layout.
 */
/* Variables:
 * $css_id: An optional CSS id to use for the layout.
 *
 *  $content['left']
 *  $content['middle']
 *  $content['right']
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;

?> class="panels cell <?php print ($classes); ?>">

    <?php if ($content['left']): ?>
    <div class="panel-left cell-20">
    <?php print $content['left']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['middle']): ?>
    <div class="panel-middle cell-20">
    <?php print $content['middle']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['right']): ?>
    <div class="panel-right cell-60">
    <?php print $content['right']; ?>
    </div>
<?php endif; ?>

</div>
