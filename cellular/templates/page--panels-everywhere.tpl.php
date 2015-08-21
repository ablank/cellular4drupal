<?php
/**
 * @file
 * Panels everywhere page template.
 */

?>

<div id="page-wrap">
  <div id="app" class="cell">
    <?php
    if ($page['content']):
      print render($page['content']);
    endif; ?>
  </div>
</div>
