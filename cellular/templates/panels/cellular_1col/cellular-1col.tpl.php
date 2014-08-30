<?php
/**
 * @file
 * Template for a single column panel layout.
 */
/* Variables:
 * - $css_id: An optional CSS id to use for the layout.
 *   $content['middle']: The only panel in the layout.
 */
?>

<div class="cell" <?php if (!empty($css_id)): print "id=\"$css_id\"";
endif;
?>>

  <div class="panel-content">
<?php print $content['middle']; ?>
  </div>
</div>
