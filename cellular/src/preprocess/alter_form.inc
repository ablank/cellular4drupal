<?php

/**
 * @file
 * Alter forms.
 */

/**
 * Implements hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id) {
//dpm($form_state);
  //$form['#validate'][] = 'cellular_form_validate';

  switch ($form['#id']) {
    /* Search page. */
    case 'search-form':
      $form['#attributes']['class'][] = 'site-search';
      break;

    /* Search block. */
    case 'search-block-form':
      $form['#attributes']['class'][] = 'site-search';
      $form[$form_id]['#title'] = t('Search this site');
      $form[$form_id]['#default_value'] = t('Keywords');
      $form[$form_id]['#type'] = 'textfield';
      $form[$form_id]['#size'] = CELLULAR_INPUT_SIZE;
      // Submit button.
      $form['actions']['submit']['#type'] = 'submit';
      $form['actions']['submit']['#value'] = t('Search');
      break;

    /* User Login block. */
    case 'user-login-form':
      $orient = theme_get_setting('login_block_orientation');
      $form['#attributes']['class'][] = $orient;

      switch ($orient) {
        case 'horizontal':
          break;

        case 'vertical':
        default:
          $form['actions']['submit']['#attributes']['class'][] = 'clearfix';
          break;
      }

      // Username
      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => t('Username'),
        '#size' => CELLULAR_INPUT_SIZE,
      );
      // Password
      $form['pass'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#default_value' => t('Password'),
        '#size' => CELLULAR_INPUT_SIZE,
      );
      // Submit button
      $form['actions']['submit']['#attributes']['value'] = t('Log in');

      /* Request New Password & Register New Account Links. */
      $login_links = NULL;
      $user_reg = theme_get_setting('login_block_register');
      $user_pass = theme_get_setting('login_block_password');

      if (!empty($user_reg) || !empty($user_pass)) {
        $login_links = '<div class="login-links">';
        if (!empty($user_reg)) {
          $login_links .= l(t('Register'), "user/register", array(
            'attributes' => array(
              'class' => array('register'),
          )));
        }
        if (!empty($user_pass)) {
          $login_links .= l(t('Forgotten Password?'), "user/password", array(
            'attributes' => array(
              'class' => array('password'),
          )));
        }
        $login_links .= '</div>';
      }
      $form['links']['#markup'] = $login_links;
      break;

    /* Comment Form. */
    case 'comment-form':

      $form['comment_body']['und'][0]['#title_display'] = 'invisible';
      $form['comment_body']['und'][0]['#default_value'] = '';
      // Hide unwanted form fields.
      $form['author']['#access'] = FALSE;
      $form['subject']['#access'] = FALSE;
      $form['actions']['preview']['#access'] = FALSE;
      // Customize Submit button.
      $form['actions']['submit']['#value'] = t('Submit');
      $form['actions']['submit']['#attributes']['class'][] = 'right';


      // Remove text format option descriptions.
      $form['comment_body']['#after_build'][] = 'cellular_form_format_opt';
      break;
  }
}
