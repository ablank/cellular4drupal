<?php
/**
 * @file
 * Template for a parallax layout grouped by rows.
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

?> class="parallax panels cell <?php print ($classes); ?>">

  <?php if ($content['header']) : ?>
    <div class="header cell">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

  <div class="content cell">
    <?php if (!empty($content['g1_top']) || !empty($content['g1_base'])): ?>
      <div class="parallax-group cell">
        <?php if (!empty($content['g1_top'])) : ?>
          <div class="parallax-layer parallax--top panel-content cell">
            <?php print $content['g1_top']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['g1_base'])) : ?>
          <div class="parallax-layer parallax--base panel-content cell">
            <?php print $content['g1_base']; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($content['g2_top']) || !empty($content['g2_base'])): ?>
      <div class="parallax-group cell">
        <?php if (!empty($content['g2_top'])) : ?>
          <div class="parallax-layer parallax--top panel-content cell">
            <?php print $content['g2_top']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['g2_base'])) : ?>
          <div class="parallax-layer parallax--base panel-content cell">
            <?php print $content['g2_base']; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($content['g3_top']) || !empty($content['g3_base'])): ?>
      <div class="parallax-group cell">
        <?php if (!empty($content['g3_top'])) : ?>
          <div class="parallax-layer parallax--top panel-content cell">
            <?php print $content['g3_top']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['g3_base'])) : ?>
          <div class="parallax-layer parallax--base panel-content cell">
            <?php print $content['g3_base']; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($content['g4_top']) || !empty($content['g4_base'])): ?>
      <div class="parallax-group  cell">
        <?php if (!empty($content['g4_top'])) : ?>
          <div class="parallax-layer parallax--top panel-content cell">
            <?php print $content['g4_top']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['g4_base'])) : ?>
          <div class="parallax-layer parallax--base panel-content cell">
            <?php print $content['g4_base']; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($content['g5_top']) || !empty($content['g5_base'])): ?>
      <div class="parallax-group cell">
        <?php if (!empty($content['g5_top'])) : ?>
          <div class="parallax-layer parallax--top panel-content cell">
            <?php print $content['g5_top']; ?>
          </div>
        <?php endif; ?>
        <?php if (!empty($content['g5_base'])) : ?>
          <div class="parallax-layer parallax--base panel-content cell">
            <?php print $content['g5_base']; ?>
          </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>

  <?php if (!empty($content['footer'])) : ?>
    <div class="footer cell">
      <?php print $content['footer']; ?>
    </div>
  <?php endif; ?>
</div>
