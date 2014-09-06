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

<div class="cell" <?php if (!empty($css_id)): print "id=\"$css_id\""; endif; ?>>

  <?php if ($content['top']): ?>
    <div class="panel cell">
      <div class="panel-content">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left']): ?>
    <div class="panel cell-33">
      <div class="panel-content">
        <?php print $content['left']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['middle']): ?>
    <div class="panel cell-33">
      <div class="panel-content">
        <?php print $content['middle']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['right']): ?>
    <div class="panel cell-33">
      <div class="panel-content">
        <?php print $content['right']; ?>
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
