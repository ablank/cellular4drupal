<?php
/**
 * @file
 * Template for 2 column (30%/70%) panel layout.
 */
/* Variables:
 *  $content['top']
 *  $content['left']
 *  $content['right']
 *  $content['bottom']
 */

?>

<div<?php if (!empty($css_id)): print " id=\"$css_id\"";
endif; ?> class="parallax panels cell">

  <?php if ($content['g1_top'] || $content['g1_base']): ?>
    <div class="parallax-group cell">
      <?php if ($content['g1_top']) : ?>
        <div class="parallax-layer parallax--top panel-content">
          <?php print $content['g1_top']; ?>
        </div>
      <?php endif; ?>
      <?php if ($content['g1_base']) : ?>
        <div class="parallax-layer parallax--base panel-content">
          <?php print $content['g1_base']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['g2_top'] || $content['g2_base']): ?>
    <div class="parallax-group cell">
      <?php if ($content['g2_top']) : ?>
        <div class="parallax-layer parallax--top panel-content">
          <?php print $content['g2_top']; ?>
        </div>
      <?php endif; ?>
      <?php if ($content['g2_base']) : ?>
        <div class="parallax-layer parallax--base panel-content">
          <?php print $content['g2_base']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['g3_top'] || $content['g3_base']): ?>
    <div class="parallax-group cell">
      <?php if ($content['g3_top']) : ?>
        <div class="parallax-layer parallax--top panel-content">
          <?php print $content['g3_top']; ?>
        </div>
      <?php endif; ?>
      <?php if ($content['g3_base']) : ?>
        <div class="parallax-layer parallax--base panel-content">
          <?php print $content['g3_base']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['g4_top'] || $content['g4_base']): ?>
    <div class="parallax-group cell">
      <?php if ($content['g4_top']) : ?>
        <div class="parallax-layer parallax--top panel-content">
          <?php print $content['g4_top']; ?>
        </div>
      <?php endif; ?>
      <?php if ($content['g4_base']) : ?>
        <div class="parallax-layer parallax--base panel-content">
          <?php print $content['g4_base']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if ($content['g5_top'] || $content['g5_base']): ?>
    <div class="parallax-group cell">
      <?php if ($content['g5_top']) : ?>
        <div class="parallax-layer parallax--top panel-content">
          <?php print $content['g5_top']; ?>
        </div>
      <?php endif; ?>
      <?php if ($content['g5_base']) : ?>
        <div class="parallax-layer parallax--base panel-content">
          <?php print $content['g5_base']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

</div>
