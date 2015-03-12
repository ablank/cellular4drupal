<?php
/**
 * @file
 * Generate social media links.
 */

/**
 * Generate links for social media.
 *
 * @param array $links
 *   Array of links to add.
 * @param array $parent
 *   Media block array used to wrap links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_build_links(array $links, array $parent) {
  $output = '';
  foreach ($links as $link) {
    if (!empty($link['tag'])) {
      // Use preformatted html if set.
      $output .= "\n " . $link['tag'] . "\n";
    }
    else {
      // Or create link using key's attributes:
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
      // Add script if provided.
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
 * Collect Social Media share settings.
 *
 * @param string $type
 *   String used to select the array to return ("follow" || "share").
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_settings($type) {
  switch ($type) {
    case 'follow':
      $output = array(
        'title' => theme_get_setting('sm_follow_title'),
        'fb' => theme_get_setting('follow_facebook'),
        'google' => theme_get_setting('follow_google_plus'),
        'twitter' => theme_get_setting('follow_twitter'),
        'linkedin' => theme_get_setting('follow_linkedin'),
        'github' => theme_get_setting('follow_github'),
      );
      break;

    case 'share':
      $output = array(
        'title' => theme_get_setting('sm_share_title'),
        'fb' => theme_get_setting('share_facebook'),
        'google' => theme_get_setting('share_google_plus'),
        'twitter' => theme_get_setting('share_twitter'),
        'linkedin' => theme_get_setting('share_linkedin'),
        'pinterest' => theme_get_setting('share_pinterest'),
        'reddit' => theme_get_setting('share_reddit'),
      );
      break;
  }

  return $output;
}

/**
 * Collect Social Media URLs.
 *
 * @param string $type
 *   String ("follow" || "share") used to select the array to return.
 *
 * @return array
 *   Settings for selected social media group.
 */
function cellular_sm_urls($type) {
  switch ($type) {
    case 'follow':
      $output = array(
        'fb' => theme_get_setting('follow_facebook_url'),
        'google' => theme_get_setting('follow_google_plus_url'),
        'twitter' => theme_get_setting('follow_twitter_url'),
        'linkedin' => theme_get_setting('follow_linkedin_url'),
        'github' => theme_get_setting('follow_github_url'),
      );
      break;

    case 'share':
      $output = array(
        'fb' => theme_get_setting('share_facebook_url'),
        'google' => theme_get_setting('share_google_plus_url'),
        'twitter' => theme_get_setting('share_twitter_url'),
        'linkedin' => theme_get_setting('share_linkedin_url'),
        'pinterest' => theme_get_setting('share_pinterest_url'),
        'reddit' => theme_get_setting('share_reddit_url'),
      );
  }

  return $output;
}

/**
 * Generate Social media follow links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_follow() {
  if (theme_get_setting('social_media_follow') == 1) {
    $set = cellular_sm_settings('follow');
    $url = cellular_sm_urls('follow');

    $output = '';
    $block_title = $set['title'];
    $media_block = array(
      'title' => !empty($block_title) ? "<h3>$block_title</h3>\n" : '',
      'id' => 'social-media-follow',
      'link_class' => 'social icon',
      'link_text' => 'Share this page on ',
    );

    $links = array();
    $set['fb'] == 1 ? $links['facebook'] = array(
      'url' => $url['fb'],
      'class' => 'facebook',
      'name' => 'Facebook',
    ) : NULL;
    $set['google'] == 1 ? $links['google+'] = array(
      'url' => $url['google'],
      'class' => 'google',
      'name' => 'Google+',
    ) : NULL;
    $set['twitter'] == 1 ? $links['twitter'] = array(
      'url' => $url['twitter'],
      'class' => 'twitter-bird',
      'name' => 'Twitter',
    ) : NULL;
    $set['linkedin'] == 1 ? $links['linkedin'] = array(
      'url' => $url['linkedin'],
      'class' => 'linkedin',
      'name' => 'LinkedIn',
    ) : NULL;
    $set['github'] == 1 ? $links['github'] = array(
      'url' => $url['github'],
      'class' => 'github-octo',
      'name' => 'Github',
    ) : NULL;

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
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_share() {
  if (theme_get_setting('social_media_share') == 1) {
    global $base_url;
    $set = cellular_sm_settings('share');
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

    $links = array();
    $set['google'] == 1 ? $links['google+'] = array(
      'name' => 'Google+',
      'script' => NULL,
      'url' => 'http://plus.google.com/share?url=' . $page['url'],
      'class' => 'google',
    ) : NULL;
    $set['twitter'] == 1 ? $links['twitter'] = array(
      'name' => 'Twitter',
      'script' => NULL,
      'url' => 'https://twitter.com/share',
      'class' => 'twitter-bird',
    ) : NULL;
    $set['linkedin'] == 1 ? $links['linkedin'] = array(
      'name' => 'LinkedIn',
      'url' => 'http://www.linkedin.com/shareArticle?mini=true&url=' .
      $page['url'] . '&title=' . $page['title'] . '&source=' . $base_url,
      'class' => 'linkedin',
    ) : NULL;
    $set['pinterest'] == 1 ? $links['pinterest'] = array(
      'name' => 'Pinterest',
      'url' => 'http://pinterest.com/pin/create/bookmarklet/?media=&url=' .
      $page['url'] . '&is_video=false&description=' . $page['title'],
      'class' => 'pinterest',
    ) : NULL;
    $set['reddit'] == 1 ? $links['reddit'] = array(
      'name' => 'Reddit',
      'url' => 'http://www.reddit.com/submit?url=' . $page['url'],
      'class' => 'reddit',
    ) : NULL;

    if ($set['fb'] == 1) {
      // Set variables to appease PAReview.
      $fbscript = '(function(d, s, id) {
          var js, fjs = d.getElementsByTagName(s)[0];
          if (d.getElementById(id)) return;
          js = d.createElement(s); js.id = id;
          js.src = "//connect.facebook.net/en_US/all.js#xfbml=1";
          fjs.parentNode.insertBefore(js, fjs);
          }(document, \'script\', \'facebook-jssdk\'));';
      $fbtag = '<div class="fb-like" data-href="' . $page['url'] . '"
          data-layout="button" data-action="like" data-show-faces="false"
          data-share="true"></div><div id="fb-root"></div>';

      $links['facebook'] = array(
        // Facebook javascript.
        'script' => $fbscript,
        // Set fb markup.
        'tag' => $fbtag,
        // Push script to end of body.
        'weight' => 1000,
      );
    }

    $content = cellular_build_links($links, $media_block);

    if (!empty($content)) {
      $output .= "\n<div id=\"" . $media_block['id'] . "\">\n";
      $output .= $media_block['title'] . $content . "\n</div>\n";
    }

    return $output;
  }
}
