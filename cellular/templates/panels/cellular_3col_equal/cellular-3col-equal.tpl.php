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

  <div class="panel cell">
    <div class="panel-content">
      <?php print $content['top']; ?>
    </div>
  </div>

  <div class="panel cell-33">
    <div class="panel-content">
      <?php print $content['left']; ?>
    </div>
  </div>

  <div class="panel cell-33">
    <div class="panel-content">
      <?php print $content['middle']; ?>
    </div>
  </div>

  <div class="panel cell-33">
    <div class="panel-content">
      <?php print $content['right']; ?>
    </div>
  </div>

  <div class="panel cell">
    <div class="panel-content">
      <?php print $content['bottom']; ?>
    </div>
  </div>

</div>
