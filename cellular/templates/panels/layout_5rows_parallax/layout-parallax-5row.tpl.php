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
?> class="parallax-panels panels cell <?php print ($classes); ?>">

  <?php if (!empty($content['header'])) : ?>
    <div id="header">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>
  <div id="app" class="cell">
    <?php if (!empty($content)) : ?>
      <div id="content-wrap" class="cell-100">
        <div id="content">

          <?php if (!empty($content['g1_top']) || !empty($content['g1_base'])): ?>
            <div class="parallax panel-content g1 cell-100">
              <?php print $content['g1_top']; ?>
            </div>

            <?php if ($content['g1_base']) : ?>
              <div class="panel-content g1 cell-100">
                <?php print $content['g1_base']; ?>
              </div>
            <?php endif; ?>
          <?php endif; ?>

          <?php if (!empty($content['g2_top']) || !empty($content['g2_base'])): ?>
            <div class="parallax panel-content g2 cell-100">
              <?php print $content['g2_top']; ?>
            </div>

            <?php if ($content['g2_base']) : ?>
              <div class="panel-content g2 cell-100">
                <?php print $content['g2_base']; ?>
              </div>
            <?php endif; ?>
          <?php endif; ?>

          <?php if (!empty($content['g3_top']) || !empty($content['g3_base'])): ?>
            <div class="parallax panel-content g3 cell-100">
              <?php print $content['g3_top']; ?>
            </div>
            <?php if ($content['g3_base']) : ?>
              <div class="panel-content g3 cell-100">
                <?php print $content['g3_base']; ?>
              </div>
            <?php endif; ?>
          <?php endif; ?>

          <?php if (!empty($content['g4_top']) || !empty($content['g4_base'])): ?>
            <div class="parallax panel-content g4 cell-100">
              <?php print $content['g4_top']; ?>
            </div>

            <?php if ($content['g4_base']) : ?>
              <div class="panel-content g4 cell-100">
                <?php print $content['g4_base']; ?>
              </div>
            <?php endif; ?>
          <?php endif; ?>

          <?php if (!empty($content['g5_top']) || !empty($content['g5_base'])): ?>
            <div class="parallax panel-content g5 cell-100">
              <?php print $content['g5_top']; ?>
            </div>
            <?php if ($content['g5_base']) : ?>
              <div class="panel-content g5 cell-100">
                <?php print $content['g5_base']; ?>
              </div>
            <?php endif; ?>
          <?php endif; ?>
        </div>
      </div>
    <?php endif; ?>
  </div>

  <?php if (!empty($content['footer'])) : ?>
    <div id="footer">
      <?php print $content['footer']; ?>
    </div>
  <?php endif; ?>
</div>
