<?php
/**
 * @file
 * Display a static page while Drupal is offline.
 */
dpm($variables);
?>
<!DOCTYPE html>
<html lang="en" dir="ltr">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
  </head>
  <body>

    <div id="page-wrap">

      <div id="header">
        <div id="logo">
          <?php
          if (!empty($site_name)) :
            print $site_name;
          endif; ?>
        </div>

        <?php if (!empty($main_menu)) : ?>
          <div id="nav">
            <?php print render($main_menu); ?>
          </div>
        <?php endif; ?>
      </div>

      <div id="app">

        <?php
        print render($title_prefix);
        if ($title) :
          print '<h1 id="page-title">' . $title . '</h1>';
        endif;
        print render($title_suffix); ?>

        <div id="content-wrap" class="cell center">
          <div id="content" class="cell-100">
            <?php
            if ($show_messages && $messages) : ?>
            <div id="console">
              <?php // Show errors/messages
              if ($show_messages && $messages) :
                print $messages;
              endif; ?>
            </div>
          <?php endif; ?>

         <?php // Show Maintenance message
          print "<h3>$content</h3>";
          ?>

          </div>
        </div>
      </div>

      <div id="footer">

      </div>

    </div>
    <!-- /#page-wrap-->
  </body>
</html>
