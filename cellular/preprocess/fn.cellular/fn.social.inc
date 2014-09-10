<?php
/**
 * @file
 * Generate social media links.
 */

/**
 * Generate links.
 */
function cellular_build_links(array $links, array $parent) {
  $output = '';
  foreach ($links as $link) {
    if (!empty($link['tag'])) {
      // Use preformatted tag if set.
      $output .= "\n " . $link['tag'] . "\n";
    }
    else {
      // Print link with attributes.
      if (!empty($link['url'])) {
        $text = $parent['link_text'] . $link['name'];
        $output .= l(t($text), $link['url'], array(
          'attributes' => array(
            'class' => array(
              $parent['link_class'],
              $link['class'],
        ))));
      }
    }

    if (!empty($link['script'])) {
      // Add script if needed.
      drupal_add_js($link['script'], array(
        'type' => 'inline',
        'group' => JS_THEME,
        'weight' => isset($link['weight']) ? $link['weight'] : 100,
      ));
    }
  }
  return $output;
}

/**
 * Generate Social media follow links.
 */
function cellular_social_media_follow() {
  if (theme_get_setting('social_media_follow') == 1) {
    $output = '';
    $block_title = theme_get_setting('sm_follow_title');
    $media_block = array(
      'title' => !empty($block_title) ? "<h3>$block_title</h3>\n" : '',
      'id' => 'social-media-follow',
      'description' => t('Follow our current posts'),
      'link_class' => 'social icon',
      'link_text' => 'Share this page on ',
    );

    $links = array(
      'facebook' => theme_get_setting('follow_facebook') == 1 ? array(
        'url' => theme_get_setting('follow_facebook_url'),
        'class' => 'facebook',
        'name' => t('Facebook'),
        ) : NULL,
      'google+' => theme_get_setting('follow_google_plus') == 1 ? array(
        'url' => theme_get_setting('follow_google_plus_url'),
        'class' => 'google',
        'name' => t('Google+'),
        ) : NULL,
      'twitter' => theme_get_setting('follow_twitter') == 1 ? array(
        'url' => theme_get_setting('follow_twitter_url'),
        'class' => 'twitter-bird',
        'name' => t('Twitter'),
        ) : NULL,
      'linkedin' => theme_get_setting('follow_linkedin') == 1 ? array(
        'url' => theme_get_setting('follow_linkedin_url'),
        'class' => 'linkedin',
        'name' => t('LinkedIn'),
        ) : NULL,
      'github' => theme_get_setting('follow_github') == 1 ? array(
        'url' => theme_get_setting('follow_github_url'),
        'class' => 'github-octo',
        'name' => t('Github'),
        ) : NULL,
    );

    $content = cellular_build_links($links, $media_block);
    if (!empty($content)) {
      $output .= "\n<div id=\"" . $media_block['id'] . "\">\n";
      $output .= $media_block['title'] . $content . "\n</div>\n";
    }

    return $output;
  }
}

/**
 * Generate Social media share links.
 */
function cellular_social_media_share() {
  if (theme_get_setting('social_media_share') == 1) {
    global $base_url;
    $output = '';
    $page = array(
      'url' => $base_url . '/' . current_path(),
      'title' => drupal_get_title(),
    );
    $block_title = theme_get_setting('sm_share_title');
    $media_block = array(
      'title' => !empty($block_title) ? "<h3>$block_title</h3>\n" : '',
      'id' => 'social-media-share',
      'link_class' => 'social icon',
      'link_text' => 'Share this page on ',
    );

    $links = array(
      'google+' => theme_get_setting('share_google_plus') == 1 ? array(
        'name' => 'Google+',
        'script' => NULL,
        'url' => 'http://plus.google.com/share?url=' . $page['url'],
        'class' => 'google',
        ) : NULL,
      'twitter' => theme_get_setting('share_twitter') == 1 ? array(
        'name' => 'Twitter',
        'script' => NULL,
        'url' => 'https://twitter.com/share',
        'class' => 'twitter-bird',
        ) : NULL,
      'linkedin' => theme_get_setting('share_linkedin') == 1 ? array(
        'name' => '',
        'script' => NULL,
        'url' => 'http://www.linkedin.com/shareArticle?mini=true&url=' .
        $page['url'] . '&title=' . $page['title'] . '&source=' . $base_url,
        'class' => 'linkedin',
        ) : NULL,
      'pinterest' => theme_get_setting('share_pinterest') == 1 ? array(
        'name' => 'Pinterest',
        'script' => NULL,
        'url' => 'http://pinterest.com/pin/create/bookmarklet/?media=&url=' .
        $page['url'] . '&is_video=false&description=' . $page['title'],
        'class' => 'pinterest',
        ) : NULL,
      'reddit' => theme_get_setting('share_reddit') == 1 ? array(
        'name' => 'Reddit',
        'script' => NULL,
        'url' => 'http://www.reddit.com/submit?url=' . $page['url'],
        'class' => 'reddit',
        ) : NULL,
    );

    $facebook = theme_get_setting('share_facebook') == 1 ? array(
      // Facebook javascript.
      'script' => '(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/all.js#xfbml=1";
  fjs.parentNode.insertBefore(js, fjs);
  }(document, \'script\', \'facebook-jssdk\'));',
      // Set fb markup.
      'tag' => '<div class="fb-like" data-href="' . $page['url'] . '"
  data-layout="button" data-action="like" data-show-faces="false"
  data-share="true">
  </div><div id="fb-root"></div>',
      'weight' => 1000,
      ) : NULL;

    if (!empty($facebook)) {
      $links[] = $facebook;
    }

    $content = cellular_build_links($links, $media_block);
    
    if (!empty($content)) {
      $output .= "\n<div id=\"" . $media_block['id'] . "\">\n";
      $output .= $media_block['title'] . $content . "\n</div>\n";
    }

    return $output;
  }
}