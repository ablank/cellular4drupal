<?php
/**
 * @file
 * Automated error page.
 */
/* Regions:
  - $page['console']: Help, warnings, & other system notifications
  - $page['header']: Page Header
  - $page['nav']: System Navigation
  - $page['sidebar_left']: Left Sidebar
  - $page['sidebar_right']: Right Sidebar
  - $page['content']: The main content of the current page.
  - $page['footer_top']: Footer Right Column
  - $page['footer']: Items for the footer region
  - $page['footer_bottom']: Footer Middle Column

  VARIABLES

  General Utility Variables:
  - $base_path: The base URL path of the Drupal installation. At the very
  least, this will always default to "/"
  - $directory: The directory the template is located in, e.g. modules/system
  or themes/bartik.
  - $is_front: TRUE if the current page is the front page.
  - $logged_in: TRUE if the user is registered and signed in.
  - $is_admin: TRUE if the user has permission to access administration pages.

  Site Identity:
  - $front_page: The URL of the front page. Use this instead of $base_path,
  when linking to the front page. This includes the language domain or
  prefix.
  - $logo: The path to the logo image, as defined in theme configuration.
  - $site_name: The name of the site, empty when display has been disabled
  in theme settings.
  - $site_slogan: The slogan of the site, empty when display has been disabled
  in theme settings.

  Navigation:
  - $main_menu (array): An array containing the Main menu links for the
  site, if they have been configured.
  - $secondary_menu (array): An array containing the Secondary menu links for
  the site, if they have been configured.
  - $full_menu_tree : An array of all links in the Main menu.
  - $breadcrumb: The breadcrumb trail for the current page.

  Page Layout:
  - $content_width : Grid class to set width of main content.
  - $content_class_single_sidebar : Grid class to set width of main content
  with one sidebar displayed.
  - $content_class_dual_sidebar : Grid class to set width of main content with
  two sidebars displayed.
  - $sidebar_width : Grid class to set width of sidebars.
  - $triptych_class : Grid class to set width of triptych elements.

  Page Content:
  - $title_prefix (array): An array containing additional output populated by
  modules, intended to be displayed in front of the main title tag that
  appears in the template.
  - $title: The page title, for use in the actual HTML content.
  - $title_suffix (array): An array containing additional output populated by
  modules, intended to be displayed after the main title tag that appears in
  the template.
  - $messages: HTML for status and error messages. Should be displayed
  prominently.
  - $tabs (array): Tabs linking to any sub-pages beneath the current page
  (e.g., the view and edit tabs when displaying a node).
  - $action_links (array): Actions local to the page, such as 'Add menu' on the
  menu administration interface.
  - $feed_icons: A string of all feed icons for the current page.
  - $node: The node object, if there is an automatically-loaded node
  associated with the page, and the node ID is the second argument
  in the page's path (e.g. node/12345 and node/12345/revisions, but not
  comment/reply/12345).

 */

?>

<div id="skipLinks" class="hidden">
  <a href="#content-main"><?php print t('Skip to main content'); ?></a>
  <a href="#nav"><?php print t('Skip to navigation'); ?></a>
</div>

<div id="page-wrap">
  <div id="header">
    <div id="logo">

      <?php
      if ($site_name) :
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

  <div id="app">
    <?php
    print render($title_prefix);
    // Error Details.
    print '<h1 id="page-title">' . $http_status . '</h1>';
    print render($title_suffix);

    if ($action_links) :
      print '<ul class="links">' . render($action_links) . '</ul>';
    endif;

    ?>
    <div id="content-wrap" class="clearfix">
      <div id="content" class="<?php print $page['content_class']; ?>">

        <div class="error-message">
          <?php
          // Error message.
          print $messages;

          ?>
        </div>
        <div class="search">
          <?php
          print render($page['search_box']);

          ?>
        </div>

      </div>
    </div>
    <!-- /content-wrap-->
  </div>
  <!-- /app-->

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
  <!-- /#footer -->

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
    <!-- /#footer-bottom -->
  <?php endif; ?>
</div>
<!-- /#page-wrap-->
