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
if (!empty($css_id)): print " id=\"$css_id\"";
endif;

?> class="panels cell">

    <?php if ($content['inset']): ?>
    <div class="cell-25">
    <?php print $content['inset']; ?>
    </div>
<?php endif; ?>

  <div class="cell-75">

      <?php if ($content['header']): ?>
      <div class="cell-100">
      <?php print $content['header']; ?>
      </div>
    <?php endif; ?>

      <?php if ($content['body']): ?>
      <div class="cell-100">
      <?php print $content['body']; ?>
      </div>
    <?php endif; ?>
      <?php if ($content['footer']): ?>
      <div class="cell-100">
      <?php print $content['footer']; ?>
      </div>
<?php endif; ?>

  </div>
</div>
