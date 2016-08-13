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
 * Render fields:
  $field = field_view_field('node', $node, 'field_name', array(
  'label' => 'hidden'));
  print render($field);
  unset($field);
 */
?>
<?php print $page['skiplinks']; ?>

<div id="page-wrap" class="cell">

  <div id="header" class="cell">
    <?php if (!empty($page['header_top'])) : ?>
      <div id="header-top" class="cell-100">
        <?php print render($page['header_top']); ?>
      </div>
    <?php endif; ?>
    <div class="cell container">
      <?php
      if (!empty($page['logo'])) :
        print $page['logo'];
      endif;
      ?>

      <?php if (!empty($main_menu)) : ?>
        <div id="main-menu">
          <?php print render($main_menu); ?>
        </div>
      <?php endif; ?>
    </div>

    <?php if (!empty($page['header_bottom'])) : ?>
      <div id="header-bottom" class="cell-100">
        <div class="container">
          <?php print render($page['header_bottom']); ?>
        </div>
      </div>
    <?php endif; ?>

  </div>

  <div id="content" class="cell container">
    <?php
    if ($title) :
      print render($title_prefix);
      print '<h1 id="page-title">' . $title . '</h1>';
      print render($title_suffix);
    endif;
    ?>
    <?php if (!empty($tabs['#primary']) || !empty($tabs['#secondary'])): ?>
      <div id="page-tabs">
        <?php print render($tabs); ?>
      </div>
    <?php endif; ?>
    <?php
    // Breadcrumb Navigation.
    if ($breadcrumb && !$is_front) :
      print $breadcrumb;
    endif;
    ?>
    <?php
    if ($action_links) :
      print '<ul class="links">' . render($action_links) . '</ul>';
    endif;
    ?>
    <?php if ($page['console'] || ($show_messages && $messages)) : ?>
      <div id="console" class="cell-100">
        <?php
        print render($page['console']);
        if ($show_messages && $messages) :
          print $messages;
        endif;
        ?>
      </div>
    <?php endif; ?>

    <div id="content">
      <?php if ($page['content_top']) : ?>
        <div id="content-top" class="cell-100">
          <?php print render($page['content_top']); ?>
        </div>
      <?php endif; ?>
      <?php
      // Main Page Content.
      print render($page['content']);
      ?>
      <?php if ($page['content_bottom']) : ?>
        <div id="content-bottom" class="cell-100">
          <?php print render($page['content_bottom']); ?>
        </div>
      <?php endif; //#content-bottom  ?>
    </div>
  </div>

  <?php if ($page['footer_top'] || $page['footer'] || $page['footer_bottom'] || $page['copyright']) : ?>
    <div id="footer" class="cell">
      <?php if ($page['footer_top']) : ?>
        <div id="footer-top" class="cell-100">
          <div class="container">
            <?php print render($page['footer_top']); ?>
          </div>
        </div>
      <?php endif; ?>
      <?php if ($page['footer']) : ?>
        <div class="cell-100 container">
          <?php print render($page['footer']); ?>
        </div>
      <?php endif; ?>
      <div id="footer-bottom" class="cell-100">
        <div class="container">
          <?php if ($page['footer_bottom']) : ?>
          </div>
          <?php print render($page['footer_bottom']); ?>
        <?php endif; //#footer-bottom   ?>
      </div>
      <?php if (!empty($page['copyright'])): ?>
        <small id="copyright"><?php print $page['copyright']; ?></small>
      <?php endif; //#copyright  ?>
    </div>
  <?php endif; //#footer  ?>
</div>