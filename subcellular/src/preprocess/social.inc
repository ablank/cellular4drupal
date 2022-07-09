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
function cellular_build_links($links, $parent) {
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
            )))) . "\n";
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
        'digg' => theme_get_setting('share_digg'),
        'stumbleupon' => theme_get_setting('share_stumbleupon'),
        'tumblr' => theme_get_setting('share_tumblr'),
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
        'facebook' => theme_get_setting('follow_facebook_url'),
        'google' => theme_get_setting('follow_google_plus_url'),
        'twitter' => theme_get_setting('follow_twitter_url'),
        'linkedin' => theme_get_setting('follow_linkedin_url'),
        'github' => theme_get_setting('follow_github_url'),
      );
      break;

    case 'share':
      $output = array(
        'facebook' => theme_get_setting('share_facebook_url'),
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
  $set = cellular_sm_settings('follow');
  $url = cellular_sm_urls('follow');

  $links = array();

  $set['fb'] == 1 ? $links['facebook'] = array(
    'title' => "Facebook",
    'url' => $url['facebook'],
  ) : NULL;
  $set['google'] == 1 ? $links['google'] = array(
    'title' => "Google",
    'url' => $url['google'],
  ) : NULL;
  $set['twitter'] == 1 ? $links['twitter'] = array(
    'title' => "Twitter",
    'url' => $url['twitter'],
  ) : NULL;
  $set['linkedin'] == 1 ? $links['linkedin'] = array(
    'title' => "LinkedIn",
    'url' => $url['linkedin'],
  ) : NULL;
  $set['github'] == 1 ? $links['github'] = array(
    'title' => "Github",
    'url' => $url['github'],
  ) : NULL;

  if (empty($links)) {
    $links = NULL;
  }

  return $links;
}

/**
 * Generate Social media share links.
 *
 * @return string
 *   Formatted HTML.
 */
function cellular_social_media_share() {
  global $base_url;
  $set = cellular_sm_settings('share');
  $links = array();

  $set['fb'] == 1 ? $links[] = 'facebook' : NULL;
  $set['google'] == 1 ? $links[] = 'google' : NULL;
  $set['twitter'] == 1 ? $links[] = 'twitter' : NULL;
  $set['linkedin'] == 1 ? $links[] = 'linkedin' : NULL;
  $set['pinterest'] == 1 ? $links[] = 'pinterest' : NULL;
  $set['reddit'] == 1 ? $links[] = 'reddit' : NULL;
  $set['digg'] == 1 ? $links[] = 'digg' : NULL;
  $set['stumbleupon'] == 1 ? $links[] = 'stumbleupon' : NULL;
  $set['tumblr'] == 1 ? $links[] = 'tumblr' : NULL;

  if (empty($links)) {
    $links = NULL;
  }

  return $links;
}
