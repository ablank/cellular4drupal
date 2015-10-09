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

  <?php if (!empty($content['header'])): ?>
    <div class="header cell">
      <?php print $content['header']; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['cell_0'])): ?>
    <div class="content cell">
      <?php print $content['cell_0']; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['cell_50_left_0']) || !empty($content['cell_50_right_0'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_50_left_0'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_left_0']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_50_right_0'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_right_0']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>


  <?php if (!empty($content['cell_33_left_0']) || !empty($content['cell_33_center_0']) || !empty($content['cell_33_right_0'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_33_left_0'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_left_0']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_center_0'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_center_0']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_right_0'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_right_0']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>



  <?php if (!empty($content['cell_1'])): ?>
    <div class="content cell">
      <?php print $content['cell_1']; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['cell_50_left_1']) || !empty($content['cell_50_right_1'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_50_left_1'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_left_1']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_50_right_1'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_right_1']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>


  <?php if (!empty($content['cell_33_left_1']) || !empty($content['cell_33_center_1']) || !empty($content['cell_33_right_1'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_33_left_1'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_left_1']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_center_1'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_center_1']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_right_1'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_right_1']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>



  <?php if (!empty($content['cell_2'])): ?>
    <div class="content cell">
      <?php print $content['cell_2']; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['cell_50_left_2']) || !empty($content['cell_50_right_2'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_50_left_2'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_left_2']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_50_right_2'])): ?>
        <div class="content cell-50">
          <?php print $content['cell_50_right_2']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>


  <?php if (!empty($content['cell_33_left_2']) || !empty($content['cell_33_center_2']) || !empty($content['cell_33_right_2'])): ?>
    <div class="cell">
      <?php if (!empty($content['cell_33_left_2'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_left_2']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_center_2'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_center_2']; ?>
        </div>
      <?php endif; ?>
      <?php if (!empty($content['cell_33_right_2'])): ?>
        <div class="content cell-33">
          <?php print $content['cell_33_right_2']; ?>
        </div>
      <?php endif; ?>
    </div>
  <?php endif; ?>

<?php if (!empty($content['footer'])): ?>
  <div class="footer cell">
    <?php print $content['footer']; ?>
  </div>
<?php endif; ?>

</div>
