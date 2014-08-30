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

<div class="cell" <?php
if (!empty($css_id)) {
  print "id=\"$css_id\"";
}
?>>

  <div class="panel cell">
    <div class="panel-content">
      <?php print $content['top']; ?>
    </div>
  </div>

  <div class="panel cell-25">
    <div class="panel-content">
      <?php print $content['left']; ?>
    </div>
  </div>

  <div class="panel cell-25">
    <div class="panel-content">
      <?php print $content['middle']; ?>
    </div>
  </div>

  <div class="panel cell-50">
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
