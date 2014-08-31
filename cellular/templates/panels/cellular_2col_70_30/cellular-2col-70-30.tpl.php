<?php
/**
 * @file
 * Template for a 2 column (70%/30%) panel layout.
 */
/* Variables:
 *  $content['top']
 *  $content['left']
 *  $content['right']
 *  $content['bottom']
 */

?>

<div class="cell" <?php
if (!empty($css_id)): print "id=\"$css_id\"";
endif;

?>>

  <div class="panel cell">
    <div class="panel-content">
      <?php print $content['top']; ?>
    </div>
  </div>

  <div class="panel cell-70">
    <div class="panel-content">
      <?php print $content['left']; ?>
    </div>
  </div>

  <div class="panel cell-30">
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
