<?php
/*/ 
 * Implementation of hook_form
 *
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

/**
 * Implementation of hook_form_submit() for pipedrive_account_settings_form
 *
 */
function pipedrive_account_settings_form_submit($form, &$form_state) {

  // Write the variable table
  variable_set('pipedrive_api_token', $form_state['values']['pipedrive_api_token']);


  // Inform the administrator that the default project / experiement entry is ready to be enabled.
  drupal_set_message(t('Your API Token has been saved'), 'status');

  // Redirect back
  $form_state['redirect'] = 'admin/config/services/pipedrive';
}
?>