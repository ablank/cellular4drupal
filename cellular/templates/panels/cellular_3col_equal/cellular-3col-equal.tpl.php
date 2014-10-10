<?php
/**
 * @file
 * Template for a 3 equal columns (33%/33%/33%) panel layout.
 */

/* Variables:
 *  $content['top']
 *  $content['left']
 *  $content['middle']
 *  $content['right']
 *  $content['bottom']
 */

?>

<div <?php if (!empty($css_id)): print "id=\"$css_id\"";
endif; ?> class="panels cell">

  <?php if ($content['top']): ?>
    <div class="panel-top cell">
      <div class="panel-content">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left']): ?>
    <div class="panel-left cell-33">
      <div class="panel-content">
        <?php print $content['left']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['middle']): ?>
    <div class="panel-middle cell-33">
      <div class="panel-content">
        <?php print $content['middle']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['right']): ?>
    <div class="panel-right cell-33">
      <div class="panel-content">
        <?php print $content['right']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['bottom']): ?>
    <div class="panel-bottom cell">
      <div class="panel-content">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>

</div>
