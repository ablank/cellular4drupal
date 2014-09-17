<?php

/**
 * @file
 * Alter specific forms.
 */

/**
 * Cellular hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id) {

  switch ($form_id) {
    // Site Search block:
    case 'search_block_form':

      $form['#attributes'] = array(
        'id' => 'site-search',
        'class' => array(),
      );
      $form['search_block_form'] = array(
        '#type' => 'textfield',
        '#size' => 25,
        // '#value' => t('Search'),
        '#default_value' => 'Search keywords: ',
        '#attributes' => array('title' => 'Search this site'),
      );

      $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Search'),
        '#attributes' => array(
          'id' => 'site-search-submit',
          'class' => array('icon', 'search'),
        ),
      );

      break;

    // User Login block:
    case 'user_login_block':
      $field_size = 20;
      $orient = theme_get_setting('login_block_orientation');
      $form['#attributes'] = array('class' => array($orient));

      $form['#title_display'] = 'invisible';

      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#attributes' => array('value' => t('Username')),
        '#size' => $field_size,
      );
      $form['pass'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#attributes' => array('value' => t('Password')),
        '#size' => $field_size,
      );
      $form['actions']['submit'][] = array(
        // Change the text on the submit button:
        '#value' => t('Log in'),
        '#attributes' => array(
          'class' => array(
            $orient === 'vertical' ? 'clearfix' : NULL,
          ),
        ),
      );

      // Remove Request New Password and other links from Block form:
      $ureg = theme_get_setting('login_block_register');
      $upass = theme_get_setting('login_block_password');

      if (isset($ureg) || isset($upass)) {
        $ulmarkup = '<div id="login-links">';
        if ($ureg == 1) {
          $ulmarkup .= l(t('Register'), "user/register", array(
            'attributes' => array(
              'class' => array(
                'register',
              ),
            ),
            )
          );
        }
        if ($upass == 1) {
          $ulmarkup .= l(t('Forgotten Password?'), "user/password", array(
            'attributes' => array(
              'class' => array(
                'password',
              ),
            ),
          ));
        }
        $ulmarkup .= '</div>';
      }
      else {
        $ulmarkup = NULL;
      }

      $form['links']['#markup'] = $ulmarkup;
      // Register New User Account:
      /*
         $form['links']['#markup'][] = t('Register')
       . ' <a href="/user/register">'
       . t('Register') . '</a>';
      */

      // Forgot Password:
      /*
       $form['links']['#markup'][] = t('Forgotten Password?')
       . ' <a href="/user/password">'
       . t('Forgotten Password?') . '</a>';
       */

      // Register New User Account &&  Forgot Password:
      /*
       $form['links']['#markup'] = '<hr/>'
       . ' <a class="user-register" href="/user/register">'
         . t('Register') . '</a>' . '<hr/>'
         . ' <a class="user-password" href="/user/password">'
         . t('Forgotten Password?') . '</a>';
      */

      break;
  }
  // dsm($form);
}

/**
 * Cellular hook__form_comment_form_alter().
 */
function cellular_form_comment_form_alter(&$form, &$form_state, &$form_id) {

  // Set field sizes.
  $field_size = 32;
  $form['author']['name']['#size'] = $field_size;
  $form['subject']['#size'] = $field_size;
  // Remove text format option.
  $form['comment_body']['#after_build'][] = 'cellular_form_strip_access';
  // Customize Submit & Preview buttons.
  $form['actions']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
    '#weight' => 19,
    '#attributes' => array('class' => array('submit', 'preview')),
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 20,
    '#attributes' => array(
      'id' => 'comment-form-submit',
      'class' => array('submit', 'right'),
    ),
  );
}
