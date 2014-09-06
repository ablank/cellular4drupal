<?php
/**
 * @file
 * Template for 2 column (30%/70%) panel layout.
 */

/* Variables:
 *  $content['top']
 *  $content['left']
 *  $content['right']
 *  $content['bottom']
 */

?>

<div class="cell" <?php if (!empty($css_id)): print "id=\"$css_id\""; endif; ?>>

  <?php if ($content['top']): ?>
    <div class="panel cell">
      <div class="panel-content">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['right']): ?>
    <div class="panel cell-30">
      <div class="panel-content">
        <?php print $content['right']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left']): ?>
    <div class="panel cell-70">
      <div class="panel-content">
        <?php print $content['left']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['bottom']): ?>
    <div class="panel cell">
      <div class="panel-content">
        <?php print $content['bottom']; ?>
      </div>
    </div>
  <?php endif; ?>

</div>
