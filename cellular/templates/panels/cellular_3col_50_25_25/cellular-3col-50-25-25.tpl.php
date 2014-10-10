<?php
/**
 * @file
 * This template provides a three column 50%-25%-25% panel display layout.
 */

/* Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['right']: Content in the right column.
 */

?>

<div<?php if (!empty($css_id)): print " id=\"$css_id\"";
endif;?> class="panels cell">

  <?php if ($content['top']): ?>
    <div class="panel-top cell">
      <div class="panel-content">
        <?php print $content['top']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($content['left']): ?>
    <div class="panel-left cell-50">
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
    <div class="panel-right cell-25">
      <div class="panel-content">
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
