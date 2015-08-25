<?php
/**
 * @file
 * Template for the Inset Left column panel layout.
 */
/* Variables:
 *  $content['inset']
 *  $content['header']
 *  $content['body']
 *  $content['footer']
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;

?> class="panels cell <?php print ($classes); ?>">

  <?php if (!empty($content['header'])): ?>
    <div class="header cell">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['left']) || !empty($content['right'])): ?>
    <div class="content cell">
      <?php if (!empty($content['left'])): ?>
        <div class="content cell-50">
          <?php print $content['left']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['right'])): ?>
        <div class="content cell-50">
          <?php print $content['right']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['footer'])): ?>
    <div class="footer cell">
      <?php print $content['footer']; ?>
    </div>
  <?php endif; ?>

</div>
