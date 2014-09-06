<?php
/**
 * @file
 * Template for the Inset Right column panel layout.
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

  <div class="cell-75">

    <?php if ($content['top']): ?>
      <div class="cell">
        <div class="panel-content">
          <?php print $content['top']; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($content['left']): ?>
      <div class="panel cell-50">
        <div class="panel-content">
          <?php print $content['left']; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($content['middle']): ?>
      <div class="panel cell-50">
        <div class="panel-content">
          <?php print $content['middle']; ?>
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

  <?php if ($content['right']): ?>
    <div class="panel cell-25">
      <div class="panel-content">
        <?php print $content['right']; ?>
      </div>
    </div>
  <?php endif; ?>

</div>
