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

      <?php if ($content['header']): ?>
    <div id="panel-header" class="cell-100">
      <?php print $content['header']; ?>
      </div>
    <?php endif; ?>

      <?php if ($content['body']): ?>
    <div id="panel-content" class="cell-100">
      <?php print $content['body']; ?>
      </div>
    <?php endif; ?>

      <?php if ($content['footer']): ?>
      <div id="panel-footer" class="cell-100">
      <?php print $content['footer']; ?>
      </div>
<?php endif; ?>
</div>
