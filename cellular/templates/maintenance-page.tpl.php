<?php
/**
 * @file
 * Display a single Drupal page while offline.
 */
/* All the available variables are mirrored in html.tpl.php and page.tpl.php.
 * Some may be blank but they are provided for consistency.
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml"
      xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>"
      dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
  </head>
  <body class="<?php print $classes; ?>">
    <div id="page-wrap">

      <div id="skipLinks" class="hidden">
        <a href="#content"><?php print t('Skip to main content'); ?></a>
        <a href="#nav"><?php print t('Skip to navigation'); ?></a>
      </div>

      <?php if ($page['header_top']) : ?>
        <div id="header-top">
          <?php print render($page['header_top']); ?>
        </div>
      <?php endif; ?>

      <div id="header">

        <div id="logo">
          <?php
          if (!empty($site_name)) :
            print "<h2>" . $site_name . "</h2>";
          endif;

          ?>
        </div>

        <?php if (isset($main_menu)) : ?>
          <div id="nav">
            <?php print render($main_menu); ?>
          </div>
        <?php endif; ?>

        <?php print render($page['header']); ?>

      </div>
      <!-- /#header -->

      <?php if ($page['header_bottom']) : ?>
        <div id="header-bottom">
          <?php print render($page['header_bottom']); ?>
        </div>
      <?php endif; ?>

      <div id="app">

        <?php
        print render($title_prefix);
        if ($title) :
          print '<h1 id="page-title">' . $title . '</h1>';
        endif;
        print render($title_suffix);

        ?>

        <?php if (!empty($tabs)): ?>
          <div id="page-tabs">
            <?php print render($tabs); ?>
          </div>
        <?php endif; ?>

        <div id="content-wrap" class="clearfix">

          <?php
          if ($action_links) :
            print '<ul class="links">' . render($action_links) . '</ul>';
          endif;

          if ($page['console'] || ($show_messages && $messages)) :

            ?>
            <div id="console">
              <?php
              print render($page['console']);
              if ($show_messages && $messages) :
                print $messages;
              endif;

              ?>
            </div>
          <?php endif; ?>

          <?php if ($page['sidebar_left']) : ?>
            <div id="sidebar-left" class="<?php print $page['sidebar_class']; ?>">
              <?php print render($page['sidebar_left']); ?>
            </div>

            <!-- /#sidebar-left -->
          <?php endif; ?>

          <?php if ($page['content_top']) : ?>
            <div id="content-top" class="cell">
              <?php print render($page['content_top']); ?>
            </div>
          <?php endif; ?>

          <div id="content" class="<?php print $page['content_class']; ?>">

            <?php
            // Breadcrumb Navigation.
            if (theme_get_setting('breadcrumb_display' && !$is_front)) :
              print $breadcrumb;
            endif;

            ?>

            <?php
            // Main Page Content.
            print render($page['content']);

            ?>

            <?php if ($page['content_bottom']) : ?>
              <div id="content-bottom" class="cell">
                <?php print render($page['content_bottom']); ?>
              </div>
            <?php endif; ?>

          </div>
          <!-- /#content -->

          <?php if ($page['sidebar_right']) : ?>
            <div id="sidebar-right" class="<?php print $page['sidebar_class']; ?>">
              <?php print render($page['sidebar_right']); ?>
            </div>
            <!-- /#sidebar-right -->
          <?php endif; ?>

        </div>
        <!-- /#content-wrap-->
      </div>
      <!-- /#app-->

      <div id="footer" class="cell">

        <?php if ($page['footer_top']) : ?>
          <div id="footer-top" class="cell">
            <?php print render($page['footer_top']); ?>
          </div>
        <?php endif; ?>

        <?php
        if ($page['footer']) :
          print render($page['footer']);
        endif;

        ?>

        <div id="footer-bottom" class="cell">
          <?php if ($page['footer_bottom']) : ?>
            <?php print render($page['footer_bottom']); ?>
          <?php endif; ?>

          <?php if ($page['copyright']): ?>
            <p id="copyright"><?php print $page['copyright']; ?></p>
          <?php endif; ?>
        </div>
        <!-- /#footer-bottom -->
      </div>
      <!-- /#footer -->
    </div>
    <!-- /#page-wrap-->
  </body>
</html>
