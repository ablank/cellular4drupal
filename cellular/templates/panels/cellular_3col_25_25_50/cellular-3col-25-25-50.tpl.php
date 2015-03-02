<?php
/**
 * @file
 * Template for a 3 column (25%/25%/50%) panel layout.
 */

/* Variables:
 *  $content['top']
 *  $content['left']
 *  $content['midle']
 *  $content['right']
 *  $content['bottom']
 */

?>
<div <?php if (!empty($css_id)): print "id=\"$css_id\"";
endif; ?> class="panels cell" >

  <?php if ($content['top']): ?>
    <div class="panel-top cell-100">
      <div class="panel-content">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left']): ?>
    <div class="panel-left cell-25">
      <div class="panel-content">
        <?php print $content['left']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['middle']): ?>
    <div class="panel-middle cell-25">
      <div class="panel-content">
        <?php print $content['middle']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['right']): ?>
    <div class="panel-right cell-50">
      <div class="panel-content">
        <?php print $content['right']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['bottom']): ?>
    <div class="panel-bottom cell-100">
      <div class="panel-content">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>

</div>
