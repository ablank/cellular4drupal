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

<div<?php
if (!empty($css_id)): print " id=\"$css_id\"";
endif;

?> class="panels cell">

    <?php if ($content['header']): ?>
    <div class="panel-header cell-100">
    <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['body']): ?>
    <div class="panel-body cell-100">
    <?php print $content['body']; ?>
    </div>
  <?php endif; ?>

    <?php if ($content['footer']): ?>
    <div class="panel-footer cell-100">
    <?php print $content['footer']; ?>
    </div>
<?php endif; ?>

</div>
