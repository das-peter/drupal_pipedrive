<?php
/**
 * @file
 * Pipedrive Admin Page.
 */

/**
 * Implements hook_form().
 */
function pipedrive_account_settings_form($form_state) {

  $form = array();

  $form['pipedrive_api_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Pipedrive API Token'),
    '#default_value' => variable_get('pipedrive_api_token', ''),
    '#description' => t('Your Pipedrive account API Key. Can be found at https://[subdomain].pipedrive.com/settings#api'),
    '#size' => 60,
    '#maxlength' => 256,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

