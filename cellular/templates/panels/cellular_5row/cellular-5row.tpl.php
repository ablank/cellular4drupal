<?php
/**
 * @file
 * Template for 2 column (30%/70%) panel layout.
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;
?> class="panels cell <?php print($classes); ?>">

    <?php if ($content['row1']) : ?>
    <div class="panel-content cell-100">
    <?php print $content['row1']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['row2']) : ?>
    <div class="panel-content cell-100">
    <?php print $content['row2']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['row3']) : ?>
    <div class="panel-content cell-100">
    <?php print $content['row3']; ?>
    </div>
  <?php endif; ?>  

    <?php if ($content['row4']) : ?>
    <div class="panel-content cell-100">
    <?php print $content['row4']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['row5']) : ?>
    <div class="panel-content cell-100">
    <?php print $content['row5']; ?>
    </div>
<?php endif; ?>
</div>
