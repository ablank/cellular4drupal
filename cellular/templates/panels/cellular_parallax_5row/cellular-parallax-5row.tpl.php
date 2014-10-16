<?php
/**
 * @file
 * Template for 2 column (30%/70%) panel layout.
 */

?>

<div<?php if (!empty($css_id)): print " id=\"$css_id\"";
endif; ?> class="parallax-panels panels cell <?php print($classes); ?>">

  <?php if ($content['g1_top'] || $content['g1_base']): ?>

    <div class="parallax panel-content g1">
      <?php print $content['g1_top']; ?>
    </div>

    <?php if ($content['g1_base']) : ?>
      <div class="panel-content g1">
        <?php print $content['g1_base']; ?>
      </div>
    <?php endif; ?>

  <?php endif; ?>

  <?php if ($content['g2_top'] || $content['g2_base']): ?>

    <div class="parallax panel-content g2">
      <?php print $content['g2_top']; ?>
    </div>

    <?php if ($content['g2_base']) : ?>
      <div class="panel-content g2">
        <?php print $content['g2_base']; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>

  <?php if ($content['g3_top'] || $content['g3_base']): ?>
    <div class="parallax panel-content g3">
      <?php print $content['g3_top']; ?>
    </div>
    <?php if ($content['g3_base']) : ?>
      <div class="panel-content g3">
        <?php print $content['g3_base']; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>

  <?php if ($content['g4_top'] || $content['g4_base']): ?>
    <div class="parallax panel-content g4">
      <?php print $content['g4_top']; ?>
    </div>

    <?php if ($content['g4_base']) : ?>
      <div class="panel-content g4">
        <?php print $content['g4_base']; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>

  <?php if ($content['g5_top'] || $content['g5_base']): ?>
    <div class="parallax panel-content g5">
      <?php print $content['g5_top']; ?>
    </div>
    <?php if ($content['g5_base']) : ?>
      <div class="panel-content g5">
        <?php print $content['g5_base']; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>

</div>
