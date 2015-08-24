<?php
/**
 * @file
 * Template for a 3 equal columns (33%/33%/33%) panel layout.
 */
/* Variables:
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
    <div class="panel-left cell-33">
    <?php print $content['left']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['middle']): ?>
    <div class="panel-middle cell-33">
    <?php print $content['middle']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['right']): ?>
    <div class="panel-right cell-33">
    <?php print $content['right']; ?>
    </div>
<?php endif; ?>

</div>
