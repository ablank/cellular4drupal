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

  <div class="cell-75">
    <?php if (!empty($content['header'])): ?>
      <div id="header">
        <?php print $content['header']; ?>
      </div>
    <?php endif; ?>

    <div id="app" class="cell">
      <?php if (!empty($content['body'])): ?>
        <div id="content-wrap" class="cell">
          <div id="content">
            <?php print $content['body']; ?>
          </div>
        </div>
      <?php endif; ?>
    </div>

    <?php if (!empty($content['footer'])): ?>
      <div id="footer">
        <?php print $content['footer']; ?>
      </div>
    <?php endif; ?>
  </div>
  
  <?php if (!empty($content['inset'])): ?>
    <div id="inset" class="cell-25">
      <?php print $content['inset']; ?>
    </div>
  <?php endif; ?>
</div>
