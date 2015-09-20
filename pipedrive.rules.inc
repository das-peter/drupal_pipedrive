<?php
/**
 * @file
 * Pipedrive rules integration file.
 */

/**
 * Implements hook_rules_event_info().
 */
function pipedrive_rules_event_info() {
  $items = array();

  // The easiest way to handle the different data types is by creating a
  // dedicated event for each type.
  foreach (pipedrive_data_types() as $data_type => $data_type_plural) {
    $items['pipedrive_field_sync_' . $data_type] = array(
      'label' => t('Before syncing a pipedrive !type field', array('!type' => ucfirst($data_type))),
      'group' => t('Pipedrive'),
      'variables' => array(
        'pipedrive_entry' => array('type' => 'pipedrive_' . $data_type, 'label' => 'Pipedrive ' . ucfirst($data_type) . ' Data'),
        'entity' => array('type' => 'entity', 'label' => 'Entity'),
      ),
    );
  }

  return $items;
}

/**
 * Implements hook_rules_data_info().
 */
function pipedrive_rules_data_info() {
  // Define the data structure of the currently available pipedrive data types.
  $data_info = array();
  $data_info['pipedrive_activity'] = array(
    'label' => t('Pipedrive Activity'),
    'wrap' => TRUE,
    'property info' => array(
      'id' => array(
        'type' => 'integer',
        'label' => t('ID'),
      ),
      'subject' => array(
        'type' => 'text',
        'label' => t('Subject'),
        'required' => TRUE,
        'sanitized' => TRUE,
      ),
      'done' => array(
        'type' => 'bool',
        'label' => t('Done'),
      ),
      'type' => array(
        'type' => 'text',
        'label' => t('Type'),
        'required' => TRUE,
        'sanitized' => TRUE,
        'options list' => 'pipedrive_activity_type_options',
      ),
      'due_date' => array(
        'type' => 'date',
        'label' => t('Due date'),
      ),
      'duration' => array(
        'type' => 'duration',
        'label' => t('Duration'),
      ),
      'user_id' => array(
        'type' => 'pipedrive_user',
        'label' => t('User'),
      ),
      'deal_id' => array(
        'type' => 'pipedrive_deal',
        'label' => t('Deal'),
      ),
      'person_id' => array(
        'type' => 'pipedrive_person',
        'label' => t('Person'),
      ),
      'org_id' => array(
        'type' => 'pipedrive_organization',
        'label' => t('Organization'),
      ),
      'note' => array(
        'type' => 'text',
        'label' => t('Note'),
      ),
      'skip_sync' => array(
        'type' => 'bool',
        'label' => t('Skip syncing process to pipedrive'),
      ),
    ),
  );

  // @TODO Add support for DealFields.
  $data_info['pipedrive_deal'] = array(
    'label' => t('Pipedrive Deal'),
    'wrap' => TRUE,
    'property info' => array(
      'id' => array(
        'type' => 'integer',
        'label' => t('ID'),
      ),
      'title' => array(
        'type' => 'text',
        'label' => t('Title'),
        'required' => TRUE,
        'sanitized' => TRUE,
      ),
      'value' => array(
        'type' => 'decimal',
        'label' => t('Value'),
      ),
      'currency' => array(
        'type' => 'text',
        'label' => t('Currency'),
      ),
      'status' => array(
        'type' => 'duration',
        'label' => t('Duration'),
        'options list' => 'pipedrive_deal_status_options',
      ),
      'lost_reason' => array(
        'type' => 'text',
        'label' => t('Lost Reasion'),
      ),
      'add_time' => array(
        'type' => 'date',
        'label' => t('Add time'),
      ),
      'visible_to' => array(
        'type' => 'integer',
        'label' => t('Visbile to'),
        'options list' => 'pipedrive_visibility_options',
      ),
      'user_id' => array(
        'type' => 'pipedrive_user',
        'label' => t('User'),
      ),
      'stage_id' => array(
        'type' => 'pipedrive_stage',
        'label' => t('Stage'),
      ),
      'person_id' => array(
        'type' => 'pipedrive_person',
        'label' => t('Person'),
      ),
      'org_id' => array(
        'type' => 'pipedrive_organization',
        'label' => t('Organization'),
      ),
      'skip_sync' => array(
        'type' => 'bool',
        'label' => t('Skip syncing process to pipedrive'),
      ),
    ),
  );
  pipedrive_rules_data_info_dynamic_fields('deal', $data_info['pipedrive_deal']);

  // @TODO Add support for OrganizationFields.
  $data_info['pipedrive_organization'] = array(
    'label' => t('Pipedrive Organization'),
    'wrap' => TRUE,
    'property info' => array(
      'id' => array(
        'type' => 'integer',
        'label' => t('ID'),
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('name'),
        'required' => TRUE,
        'sanitized' => TRUE,
      ),
      'visible_to' => array(
        'type' => 'integer',
        'label' => t('Visbile to'),
        'options list' => 'pipedrive_visibility_options',
      ),
      'owner_id' => array(
        'type' => 'pipedrive_user',
        'label' => t('Owner'),
      ),
      'skip_sync' => array(
        'type' => 'bool',
        'label' => t('Skip syncing process to pipedrive'),
      ),
    ),
  );
  pipedrive_rules_data_info_dynamic_fields('organization', $data_info['pipedrive_organization']);

  // @TODO Add support for PersonsFields.
  $data_info['pipedrive_person'] = array(
    'label' => t('Pipedrive Person'),
    'wrap' => TRUE,
    'property info' => array(
      'id' => array(
        'type' => 'integer',
        'label' => t('ID'),
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('name'),
        'required' => TRUE,
        'sanitized' => TRUE,
      ),
      'owner_id' => array(
        'type' => 'pipedrive_user',
        'label' => t('Owner'),
      ),
      'org_id' => array(
        'type' => 'pipedrive_organization',
        'label' => t('Organization'),
      ),
      'email' => array(
        'type' => 'text',
        'label' => t('E-Mail'),
      ),
      'phone' => array(
        'type' => 'text',
        'label' => t('Phone'),
      ),
      'visible_to' => array(
        'type' => 'integer',
        'label' => t('Visbile to'),
        'options list' => 'pipedrive_visibility_options',
      ),
      'add_time' => array(
        'type' => 'date',
        'label' => t('Add time'),
      ),
      'skip_sync' => array(
        'type' => 'bool',
        'label' => t('Skip syncing process to pipedrive'),
      ),
    ),
  );
  pipedrive_rules_data_info_dynamic_fields('person', $data_info['pipedrive_person']);

  // Set the property getter / setter.
  foreach ($data_info as $type => &$info) {
    if (!empty($info['property info'])) {
      foreach ($info['property info'] as $property => &$property_info) {
        $property_info += array(
          'getter callback' => 'entity_property_verbatim_get',
          'setter callback' => 'entity_property_verbatim_set',
          'raw getter callback' => 'entity_property_verbatim_get',
        );
      }
    }
  }

  return $data_info;
}

function pipedrive_rules_data_info_dynamic_fields($type, &$info) {
  $type_map = pipedrive_datatype_map();
  // Fetch dynamic fields.
  $fields = pipedrive_get_dynamic_fields($type);
  foreach ($fields as $field) {
    // Only add if a related property type was found and property wasn't defined
    // manually.
    if (isset($type_map[$field['field_type']]) && !isset($info['property info'][$field['key']])) {
      $info['property info'][$field['key']] = array(
        'type' => $type_map[$field['field_type']],
        'label' => $field['name'],
      );
      // Add required flag.
      if (!empty($field['mandatory_flag'])) {
        $info['property info'][$field['key']]['required'] = TRUE;
      }
      // Handle options lists.
      if (!empty($field['options'])) {
        $info['property info'][$field['key']]['options list'] = 'pipedrive_rules_data_info_dynamic_fields_options';
        foreach ($field['options'] as $option) {
          $info['property info'][$field['key']]['options data'][$option['id']] = $option['label'];
        }
      }
    }
  }
}

/**
 * Dynamic options list callback for rules data types.
 */
function pipedrive_rules_data_info_dynamic_fields_options($name, $info, $op) {
  return $info['options data'];
}