<?php
/**
 * @file
 * Page Template.
 */
/* VARIABLES
  Regions:
  - $page['console']// Help, warnings, & other system notifications
  - $page['header_top']
  - $page['header']
  - $page['header_bottom']
  - $page['sidebar_left']
  - $page['sidebar_right']
  - $page['content_top']
  - $page['content']// Main page content
  - $page['content_bottom']
  - $page['footer_top']: Footer Top
  - $page['footer']: Footer
  - $page['footer_bottom']: Footer Bottom

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
  - $breadcrumb: The breadcrumb trail for the current page.

  Social Media
 * Set in theme settings
  - $social_media_share : links for users to share current page with their own
  social media network.
  - $social_media_follow : links for users to subscribe to your
  social media outlets.

  Page Layout
 * Set in theme settings
  - $content_width : Grid class to set width of main content.
  - $content_class_single_sidebar : Grid class to set width of main content with
  one sidebar displayed.
  - $content_class_dual_sidebar : Grid class to set width of main content with
  two sidebars displayed.
  - $sidebar_width : Grid class to set width of sidebars.

  Page Content:
  - $node: The node object, if there is an automatically-loaded node
  associated with the page, and the node ID is the second argument
  in the page's path (e.g. node/12345 and node/12345/revisions, but not
  comment/reply/12345).
  - $messages: HTML for status and error messages. Should be displayed
  prominently.
  - $action_links (array): Actions local to the page, such as 'Add menu' on the
  menu administration interface.
  - $title: The page title, for use in the actual HTML content.
  - $title_prefix (array): An array containing additional output populated by
  modules, intended to be displayed in front of the main title tag that
  appears in the template.
  - $title_suffix (array): An array containing additional output populated by
  modules, intended to be displayed after the main title tag that appears in
  the template.
  - $tabs (array): Tabs linking to any sub-pages beneath the current page
  (e.g., the view and edit tabs when displaying a node).
  - $feed_icons: A string of all feed icons for the current page.
 */

/*
  Custom page templates can be created for content types by adding the template:
 * /templates/page--content-type.tpl.php
 *
 * Render cck fields:
  $field = field_view_field('node', $node, 'field_name', array(
  'label' => 'hidden'));
  print render($field);
  unset($field);
 */

?>
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
        print $site_name;
      endif;

      ?>
    </div>

    <?php if (!empty($main_menu)) : ?>
      <div id="nav">
        <?php print render($main_menu); ?>
      </div>
    <?php endif; ?>
    <?php
    if ($page['header']) :
      print render($page['header']);
    endif;

    ?>

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

    <?php
    // Breadcrumb Navigation.
    if ($breadcrumb && !$is_front) :
      print $breadcrumb;
    endif

    ?>

    <?php if (!empty($tabs)): ?>
      <div id="page-tabs">
        <?php print render($tabs); ?>
      </div>

    <?php endif; ?>
    <div id="content-wrap" class="cell center">

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
        <div id="sidebar-left" class="<?php
        // Class of sidebar from theme settings.
        if ($page['sidebar_class']):
          print $page['sidebar_class'];
        endif;

        ?>">
               <?php print render($page['sidebar_left']); ?>
        </div>
        <!-- /#sidebar-left -->

      <?php endif; ?>
      <?php if ($page['content_top']) : ?>
        <div id="content-top" class="cell">
          <?php print render($page['content_top']); ?>
        </div>

      <?php endif; ?>
      <div id="content" class="<?php
      // Class of sidebar from theme settings.
      if (!empty($page['content_class'])):
        print $page['content_class'];
      endif;

      ?>">
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
        <div id="sidebar-right" class="<?php
        // Class of sidebar from theme settings.
        if ($page['sidebar_class']):
          print $page['sidebar_class'];
        endif;

        ?>">
               <?php print render($page['sidebar_right']); ?>
        </div>
        <!-- /#sidebar-right -->

      <?php endif; ?>
    </div>
    <!-- /#content-wrap-->
  </div>
  <!-- /#app-->
  <?php
// Social Media share links.
  if ($page['social_media_share']) :
    print $page['social_media_share'];
  endif;
// Social Media follow links.
  if ($page['social_media_follow']):
    print $page['social_media_follow'];
  endif;

  ?>
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

      <?php if (!empty($page['copyright'])): ?>
        <small id="copyright"><?php print $page['copyright']; ?></small>

      <?php endif; ?>
    </div>
    <!-- /#footer-bottom -->
  </div>
  <!-- /#footer -->

</div>
<!-- /#page-wrap-->
