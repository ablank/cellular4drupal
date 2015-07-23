<?php
/**
 * @file
 * Panels everywhere page template.
 */

?>

<div id="page-wrap">
  <div id="app" class="cell">
<?php if ($page['content']): ?>
      <div id="content-wrap" class="cell">
        <div id="content" class="cell">

          <?php
          // Main Page Content.
          print render($page['content']);
          ?>

        </div>
<?php endif; // #content     ?>
    </div>
  </div>
</div>
