<?php
/**
 * @file
 * Theme-settings: Set copyright & favicons.
 */
$form[0]['meta'] = array(
  '#type' => 'fieldset',
  '#title' => t('Meta'),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);
/*
  $form[0]['meta']['dev'] = array(
  '#type' => 'checkbox',
  '#title' => t('Development mode'),
  '#description' => t("Print the page variables array in the messages area, using Devel if available."),
  '#default_value' => theme_get_setting('dev'),
  );
 */

$form[0]['meta']['cookie_time'] = array(
  '#type' => 'textfield',
  '#title' => t('Cookie Expiration'),
  '#description' => t('Number of days before the theme cookie expires. A <code>first-visit</code> class is added to <code>&lt;body&gt;</code> and <code>Drupal.settings.cellular.first_visit = true</code>.'),
  '#default_value' => theme_get_setting('cookie_time'),
);

$form[0]['meta']['libpath'] = array(
  '#type' => 'textfield',
  '#title' => t('Cellular Library'),
  '#description' => t('Site relative path to the <a href="@lib">Cellular Library</a>', array(
    '@lib' => 'https://github.com/ablank/cellular.library',
  )),
  '#default_value' => theme_get_setting('libpath'),
);

$form[0]['meta']['favicons'] = array(
  '#type' => 'fieldset',
  '#title' => t('Favicons'),
  '#description' => t("Favicons are used by browsers to provide a graphic identity for your site."),
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);

$form[0]['meta']['favicons']['favicon'] = array(
  '#type' => 'textfield',
  '#title' => t('Favicon'),
  '#description' => t("Default favicon.ico file"),
  '#default_value' => theme_get_setting('favicon'),
);

$form[0]['meta']['favicons']['favicon_32'] = array(
  '#type' => 'textfield',
  '#title' => t('32px Favicon'),
  '#description' => t("Favicon image in .PNG format used by newer browsers"),
  '#default_value' => theme_get_setting('favicon_32'),
);

$form[0]['meta']['favicons']['apple_icons'] = array(
  '#type' => 'fieldset',
  '#title' => t('Apple-touch-icons'),
  '#description' => t("Apple-touch-icons used by smartphones & tablets. All images should use the .PNG format. Icons that are to be rendered without the default gloss should use the suffix '-precomposed' in the  file name."),
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form[0]['meta']['favicons']['apple_icons']['apple_icon_57'] = array(
  '#type' => 'textfield',
  '#title' => t('57px apple-touch-icon'),
  '#description' => t("Defult apple-touch-icon, used by 1st gen iphone."),
  '#default_value' => theme_get_setting('apple_icon_57'),
);

$form[0]['meta']['favicons']['apple_icons']['apple_icon_72'] = array(
  '#type' => 'textfield',
  '#title' => t('72px apple-touch-icon'),
  '#description' => t("Icon used by 1st gen ipad."),
  '#default_value' => theme_get_setting('apple_icon_72'),
);

$form[0]['meta']['favicons']['apple_icons']['apple_icon_114'] = array(
  '#type' => 'textfield',
  '#title' => t('114px apple-touch-icon'),
  '#description' => t("Icon used by iPhone Retina."),
  '#default_value' => theme_get_setting('apple_icon_114'),
);

$form[0]['meta']['favicons']['apple_icons']['apple_icon_144'] = array(
  '#type' => 'textfield',
  '#title' => t('144px apple-touch-icon'),
  '#description' => t("Icon used by iPad Retina."),
  '#default_value' => theme_get_setting('apple_icon_144'),
);
