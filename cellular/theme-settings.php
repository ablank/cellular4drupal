<?php

/* * ************
  Cellular:: theme-settings.php

  Form layout for theme settings controls

 * ************** */

function cellular_form_system_theme_settings_alter(&$form, $form_state) {

    // $inc_path = drupal_get_path('theme', 'cellular') . '/inc/';
    $ipath = drupal_get_path('theme', 'cellular') . '/config/';

    $form['c'] = array(
        '#type' => 'vertical_tabs',
        '#description' => t('Layout'),
        '#weight' => -10,
        '#attached' => array(),
    );

    require_once($ipath . 'personalize.inc');
    require_once($ipath . 'style.inc');
    require_once($ipath . 'js.inc');
    require_once($ipath . 'social.inc');
}
