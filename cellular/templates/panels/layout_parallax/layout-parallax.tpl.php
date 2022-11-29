<?php

/**
 * @file
 * Template for a parallax layout.
 */
/* Variables:
 *  $content['header']
 *  $content['footer']
 *  $content['g1_top']
 *  $content['g1_base']
 *  $content['g2_top']
 *  $content['g2_base']
 *  $content['g3_top']
 *  $content['g3_base']
 *  $content['g4_top']
 *  $content['g4_base']
 *  $content['g5_top']
 *  $content['g5_base']
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";
endif;

?> class="cell <?php print ($classes); ?>">

  <?php
  // Header.
  if (!empty($content['header'])) :

    ?>
    <div class="header cell">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

  <?php
  // Main content regions.
  if (!empty($content)) :

    ?>

    <?php
    // Group 1.
    if (!empty($content['g1_top']) || !empty($content['g1_base'])):

      ?>
      <div class="parallax content g1 cell">
        <?php print $content['g1_top']; ?>
      </div>

      <?php if ($content['g1_base']) : ?>
        <div class="content g1 cell">
          <?php print $content['g1_base']; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

    <?php
    // Group 2.
    if (!empty($content['g2_top']) || !empty($content['g2_base'])):

      ?>
      <div class="parallax content g2 cell">
        <?php print $content['g2_top']; ?>
      </div>

      <?php if ($content['g2_base']) : ?>
        <div class="content g2 cell">
          <?php print $content['g2_base']; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

    <?php
    // Group 3.
    if (!empty($content['g3_top']) || !empty($content['g3_base'])):

      ?>
      <div class="parallax content g3 cell">
        <?php print $content['g3_top']; ?>
      </div>
      <?php if ($content['g3_base']) : ?>
        <div class="content g3 cell">
          <?php print $content['g3_base']; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

    <?php
    // Group 4.
    if (!empty($content['g4_top']) || !empty($content['g4_base'])):

      ?>
      <div class="parallax content g4 cell">
        <?php print $content['g4_top']; ?>
      </div>

      <?php if ($content['g4_base']) : ?>
        <div class="content g4 cell">
          <?php print $content['g4_base']; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

    <?php
    // Group 5.
    if (!empty($content['g5_top']) || !empty($content['g5_base'])):

      ?>
      <div class="parallax content g5 cell">
        <?php print $content['g5_top']; ?>
      </div>
      <?php if ($content['g5_base']) : ?>
        <div class="content g5 cell">
          <?php print $content['g5_base']; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

  <?php endif; ?>
</div>

<?php
// Footer.
if (!empty($content['footer'])) :

  ?>
  <div class="footer cell">
    <?php print $content['footer']; ?>
  </div>
<?php endif; ?>

</div>
