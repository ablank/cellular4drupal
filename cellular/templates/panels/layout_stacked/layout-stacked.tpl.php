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

$id = !empty($css_id) ? " id=\"$css_id\"" : '';
?>
<div<?php print "$id class=\"panels cell $classes\" $attributes"; ?>>
  <?php if (!empty($content['header'])): ?>
    <div<?php print drupal_attributes($region_attributes['header']) ?>>
      <?php print $content['header'] ?>
    </div>
  <?php endif; ?>

  <?php
  //dpm($stack);
  foreach ($stack as $stack_idx => $stacks):
    foreach ($stacks as $stack_region => $region):
      foreach ($region as $region_idx => $region_name):
        $regions = array();
        // $key = region name, i.e. 'split'
        // $region = array of regions i.e. '0 => split_left_0'
        //  print_r($region_name);

        for ($i = 0; $i < count($region_name); $i+=1) {
          // Iterate over each stack to see if it needs to be printed.
          if (!empty($content[$region_name[$i]])) {
            $regions[] = $region_name[$i];
          }
        }

        // Iterate over each region.
        if (!empty($regions)):
          ?>

          <div class="cell stack_<?php print $key; ?>">
            <?php foreach ($regions as $idx => $region_content): ?>
              <div<?php print drupal_attributes($region_attributes[$region_content]); ?>>
                <?php print $content[$region_content]; ?>
              </div>
            <?php endforeach; ?>
          </div>

        <?php endif; ?>
      <?php endforeach; ?>
    <?php endforeach; ?>
  <?php endforeach; ?>

  <?php if (!empty($content['footer'])): ?>
    <div<?php print drupal_attributes($region_attributes['footer']) ?>>
      <?php print $content['footer'] ?>
    </div>
  <?php endif; ?>
</div>