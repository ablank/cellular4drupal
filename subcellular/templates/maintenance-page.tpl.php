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
$maintenance_title = !empty($site_name) ? $site_name : 'This site';
$maintenance_title .= ' is currently down for maintenance';

$maintenance_message = 'We apologize for the inconvenience- check back in a few minutes!';
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

      <?php if (!empty($tabs)): ?>
        <div id="page-tabs">
          <?php print render($tabs); ?>
        </div>

      <?php endif; ?>
      <div id="content" class="cell container">
        <h1 id="page-title"><?php print t($maintenance_title); ?></h1>

        <div id="content-main" class="cell">
          <p><?php print $content; ?></p>
        </div>
      </div>

      <div id="footer">

      </div>
    </div>
    </div>
  </body>
</html>
