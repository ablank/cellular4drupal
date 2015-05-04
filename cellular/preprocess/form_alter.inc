<?php
/**
 * @file
 * Alter specific forms.
 */

/**
 * Implements hook_form_alter().
 */
function cellular_form_alter(&$form, &$form_state, $form_id) {

  switch ($form_id) {
    // Site Search block:
    case 'search_block_form':
    case 'search_form':

      $form['#attributes'] = array(
        'class' => array('site-search'),
      );

      $form[$form_id]['#title'] = t('Search this site');
      $form[$form_id]['#type'] = 'textfield';
      $form[$form_id]['#size'] = 25;
      $form[$form_id]['#default_value'] = t('Search keywords');
      // Submit button.
      $form['actions']['submit']['#type'] = 'submit';
      $form['actions']['submit']['#value'] = t('Search');
      // $form['actions']['submit']['#attributes']['class'] = array('search-submit');

      break;

    // User Login block:FF
    case 'user_login_block':
      $field_size = 20;
      $orient = theme_get_setting('login_block_orientation');

      $form['#attributes']['class'][] = $orient;

      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => t('Username'),
        '#size' => $field_size,
      );
      $form['pass'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#default_value' => t('Password'),
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
      $user_reg = theme_get_setting('login_block_register');
      $user_pass = theme_get_setting('login_block_password');

      if (isset($user_reg) || isset($user_pass)) {
        $output = '<div id="login-links">';
        if (!empty($user_reg)) {
          $output .= l(t('Register'), "user/register", array(
            'attributes' => array(
              'class' => array('register'),
          )));
        }
        if (!empty($user_pass)) {
          $output .= l(t('Forgotten Password?'), "user/password", array(
            'attributes' => array(
              'class' => array('password'),
          )));
        }
        $output .= '</div>';
      }
      else {
        $output = NULL;
      }

      $form['links']['#markup'] = $output;
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
}

/**
 * Implements hook__form_comment_form_alter().
 */
function cellular_form_comment_form_alter(&$form, $form_state, $form_id) {
  // Set field sizes.
  $field_size = 32;
  // Remove text format option.
  $form['comment_body'][LANGUAGE_NONE][0]['#default_value'] = t('Add your comment');
  $form['comment_body']['#after_build'][] = 'cellular_form_format_opt';

  $form['author']['name']['#size'] = $field_size;
  $form['subject']['#size'] = $field_size;
  // Customize Submit & Preview buttons.
  $form['actions']['preview']['#value'] = t('Preview');
  $form['actions']['preview']['#weight'] = 19;
  $form['actions']['preview']['#attributes']['class'][] = 'left';

  $form['actions']['submit']['#value'] = t('Save');
  $form['actions']['submit']['#weight'] = 20;
  $form['actions']['submit']['#attributes']['class'][] = 'right';
}
