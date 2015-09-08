<?php
/**
 * @file
 * Template for a standard page layout (Header, Body, Footer).
 */
/* Variables:
 *  $content['header']
 *  $content['body']
 *  $content['footer']
 */

?>

<div  class="panels cell <?php print ($classes); ?>" <?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;
print $attributes;

?>>

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