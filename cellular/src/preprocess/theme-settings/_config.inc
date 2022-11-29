<?php

/**
 * @file
 * JQuery CDN & version settings.
 */

/*
 * jQuery CDN options.
 */
$cdn = array(
  'provider' => array(
    'jquery' => t('jQuery.com'),
    'google' => t('Google'),
    'microsoft' => t('Microsoft'),
    'cloudflare' => t('Cloudflare'),
  ),
  'jquery' => array(
    '3.1.0' => '3.1.0',
    '2.2.4' => '2.2.4',
    '2.1.4' => '2.1.4',
    '1.12.4' => '1.12.4',
    '1.11.1' => '1.11.1',
    '1.10.2' => '1.10.2',
    '1.9.1' => '1.9.1',
    '1.8.3' => '1.8.3',
    '1.7.2' => '1.7.2',
    '1.6.4' => '1.6.4',
    '1.5.2' => '1.5.2',
    '1.4.4' => t('1.4.4 : default'),
  ),
  'jqueryui' => array(
    // @ v.1.11 individual widget js isn't availanle :(
    '1.10.4' => t('1.10.4'),
    '1.9.2' => t('1.9.2'),
    '1.8.24' => t('1.8.24'),
  ),
);

// Available jQuery.ui themes:
$ui_themes = array(
  'custom' => t('CUSTOM'),
  'base' => t('Base'),
  'black-tie' => t('Black-Tie'),
  'blitzer' => t('Blitzer'),
  'cupertino' => t('Cupertino'),
  'dark-hive' => t('Dark-Hive'),
  'dot-luv' => t('Dot-Luv'),
  'eggplant' => t('Eggplant'),
  'excite-bike' => t('Excite-Bike'),
  'flick' => t('Flick'),
  'hot-sneaks' => t('Hot-Sneaks'),
  'humanity' => t('Humanity'),
  'le-frog' => t('Le-Frog'),
  'mint-choc' => t('Mint-Choc'),
  'overcast' => t('Overcast'),
  'pepper-grinder' => t('Pepper-Grinder'),
  'redmond' => t('Redmond'),
  'smoothness' => t('Smoothness'),
  'south-street' => t('South-Street'),
  'start' => t('Start'),
  'sunny' => t('Sunny'),
  'swanky-purse' => t('Swanky-Purse'),
  'trontastic' => t('Trontastic'),
  'ui-darkness' => t('UI-Darkness'),
  'ui-lightness' => t('UI-Lightness'),
  'vader' => t('Vader'),
);
