<?php
/**
 * @file
 * Automated error page.
 */
?>

<?php print $page['skiplinks']; ?>

<div id="page-wrap" class="cell">

  <div id="header" class="cell">
    <div class="cell container">
      <?php
      if (!empty($page['logo'])) :
        print $page['logo'];
      endif;
      ?>

      <?php if (isset($main_menu)) : ?>
        <div id="main-menu">
          <?php print render($main_menu); ?>
        </div>
      <?php endif; ?>
    </div>
    <?php print render($page['header']); ?>
  </div>

  <div id="content" class="cell container">
    <?php
    print render($title_prefix);
    print "<h1>Oops!</h1>\n<em>There was a bit of a snag...</em>";
    print '<h2 id="page-title">' . $http_status . '</h2>';
    print render($title_suffix);

    if ($action_links) :
      print '<ul class="links">' . render($action_links) . '</ul>';
    endif;
    ?>
    <div id="content-main">

      <div class="error-message">
        <?php print $messages; ?>
      </div>
      <?php print render($page['content']); ?>
      <div class="search">
        <?php print render($page['search_box']); ?>
      </div>
    </div>
  </div>

  <?php
  if ($page['footer_top']) :
    print render($page['footer_top']);
  endif;
  ?>
  <div id="footer" class="cell">

    <?php
    if ($page['footer']) :
      print render($page['footer']);
    endif;
    ?>
  </div>

  <?php if ($page['footer_bottom'] || $page['copyright']) : ?>
    <div id="footer-bottom" class="cell">
      <?php
      if ($page['footer_bottom']) :
        print render($page['footer_bottom']);
      endif;
      ?>

      <?php if ($page['copyright']): ?>
        <div id="copyright"><?php print $page['copyright']; ?></div>
      <?php endif; ?>
    </div>
  <?php endif; ?>
</div>
