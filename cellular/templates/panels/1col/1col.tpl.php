<?php

/**
 * @file
 * @file
 * Template for a single column panel layout.
 */

/* Variables:
 * $css_id: An optional CSS id to use for the layout.
 *
 *  $content['middle']
 */

?>

<div<?php
if (!empty($css_id)):
  print " id=\"$css_id\"";

endif;

?> class="panels cell <?php print ($classes); ?>">

  <?php
  if ($content['body']):
    print $content['body'];

  endif;?>

</div>
