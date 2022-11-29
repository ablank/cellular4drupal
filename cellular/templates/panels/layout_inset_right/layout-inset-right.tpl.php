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

  <?php
  // Main content regions.
  if (!empty($content['header']) ||
  !empty($content['body']) ||
  !empty($content['footer'])
  ):

    ?>
    <div class="cell-75">

      <?php
      // Header.
      if (!empty($content['header'])):

        ?>
        <div class="header cell">
          <?php print $content['header']; ?>
        </div>
      <?php endif; ?>

      <?php
      // Body.
      if (!empty($content['body'])):

        ?>
        <div class="content cell">
          <?php print $content['body']; ?>
        </div>
      <?php endif; ?>

    <?php
    // Footer.
    if (!empty($content['footer'])):

      ?>
      <div class="footer cell">
        <?php print $content['footer']; ?>
      </div>
    <?php endif; ?>
  </div>
  <?php endif; ?>

<?php
// Inset region.
if (!empty($content['inset'])):

  ?>
  <div class="inset pad cell-25
  <?php
  if (empty($content['header']) &&
  empty($content['body']) &&
  empty($content['footer'])
  ):

    ?> offset-75<?php
  endif; ?>">
    <?php print $content['inset']; ?>
  </div>
<?php endif; ?>
</div>
