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

  <?php if ($content['header']): ?>
    <div class="header cell">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['body']): ?>
    <div class="content cell">
      <?php print $content['body']; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['footer']): ?>
    <div class="footer cell">
      <?php print $content['footer']; ?>
    </div>
  <?php endif; ?>
</div>
