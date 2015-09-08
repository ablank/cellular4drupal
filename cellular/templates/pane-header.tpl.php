<?php
/**
 * @file
 *
 * Theme implementation to display the header block on a Drupal page.
 *
 * This utilizes the following variables thata re normally found in
 * page.tpl.php:
 * - $front_page
 * - $logo
 * - $site_name
 * - $site_slogan
 *
 * Additional items can be added via theme_preprocess_pane_header(). See
 * template_preprocess_pane_header() for examples.
 */
?>

    <div id="header">

      <div class="logo">
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

    </div>

<div id="header">
  <div class="section clearfix">
    <div class="logo-title">

      <?php if (!empty($logo)): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
      <?php endif; ?>

      <div id="name-and-slogan">
        <?php if ($site_name): ?>
          <?php if ($title): ?>
            <div id="site-name"><strong>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </strong></div>
          <?php else: /* Use h1 when the content title is empty */ ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
            </h1>
          <?php endif; ?>
        <?php endif; ?>

        <?php if (!empty($site_slogan)): ?>
          <div id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>
      </div> <!-- /name-and-slogan -->
    </div> <!-- /logo-title -->

  </div> <!-- /section -->
</div> <!-- /header -->
