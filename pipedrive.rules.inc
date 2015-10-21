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
        'property info' => &$data_info['pipedrive_organization']['property info'],
        'auto creation' => 'entity_property_create_array',
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
        'type' => 'text',
        'label' => t('Status'),
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
        'property info' => &$data_info['pipedrive_person']['property info'],
        'auto creation' => 'entity_property_create_array',
      ),
      'org_id' => array(
        'type' => 'pipedrive_organization',
        'label' => t('Organization'),
        'property info' => &$data_info['pipedrive_organization']['property info'],
        'auto creation' => 'entity_property_create_array',
      ),
      'skip_sync' => array(
        'type' => 'bool',
        'label' => t('Skip syncing process to pipedrive'),
      ),
    ),
  );
  pipedrive_rules_data_info_dynamic_fields('deal', $data_info['pipedrive_deal']);

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
        'property info' => &$data_info['pipedrive_deal']['property info'],
        'auto creation' => 'entity_property_create_array',
      ),
      'person_id' => array(
        'type' => 'pipedrive_person',
        'label' => t('Person'),
        'property info' => &$data_info['pipedrive_person']['property info'],
        'auto creation' => 'entity_property_create_array',
      ),
      'org_id' => array(
        'type' => 'pipedrive_organization',
        'label' => t('Organization'),
        'property info' => &$data_info['pipedrive_organization']['property info'],
        'auto creation' => 'entity_property_create_array',
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

/**
 * Implements hook_rules_action_info().
 */
function pipedrive_rules_action_info() {
  return array(
    'pipedrive_fetch' => array(
      'label' => t('Fetch data from pipedrive'),
      'parameter' => array(
        'type' => array(
          'type' => 'text',
          'label' => t('Pipedrive data type'),
          'options list' => 'pipedrive_data_type_options',
          'description' => t('Specifies the type of pipedrive data that should be fetched.'),
          'restriction' => 'input',
        ),
        'id' => array('type' => 'text', 'label' => t('Identifier')),
      ),
      'group' => t('Pipedrive'),
      'base' => 'pipedrive_rules_action_pipedrive_fetch',
      'provides' => array(
        'pipedrive_fetched' => array('type' => 'unknown', 'label' => t('Fetched pipedrive data')),
      ),
    ),
    'pipedrive_save' => array(
      'label' => t('Save pipedrive data'),
      'parameter' => array(
        'data' => array(
          'type' => array(
            'pipedrive_organization',
            'pipedrive_person',
            'pipedrive_deal',
            'pipedrive_activity',
          ),
          'label' => t('Pipedrive data'),
          'description' => t('Specifies the pipedrive data, which should be synced.'),
          'restriction' => 'selector',
          'wrapped' => TRUE,
        ),
      ),
      'group' => t('Pipedrive'),
      'base' => 'pipedrive_rules_action_pipedriv_save',
    ),
  );
}

/**
 * Info alteration callback for the entity fetch action.
 */
function pipedrive_rules_action_pipedrive_fetch_info_alter(&$element_info, RulesAbstractPlugin $element) {
  if (isset($element->settings['type'])) {
    $element_info['provides']['pipedrive_fetched']['type'] = 'pipedrive_' . array_search($element->settings['type'], pipedrive_data_types());
  }
}

/**
 * Fetches data from pipedrive.
 */
function pipedrive_rules_action_pipedrive_fetch($type, $id, $settings, $state, $element) {
  try {
    // Load library and use it to fetch the data.
    $pipedrive = pipedrive_load_library();
    $data = $pipedrive->{$type}()->getById($id);
    if (!empty($data['success'])) {
      $object_data = (object) $data['data'];
      pipedrive_prepare_fetched_data($object_data);

      return array('pipedrive_fetched' => $object_data);
    }
    return array('pipedrive_fetched' => NULL);
  }
  catch (\Benhawker\Pipedrive\Exceptions\PipedriveException $e) {
    throw new RulesEvaluationException($e->getMessage(), array(), $element);
  }
}

/**
 * Sync pipedrive data.
 *
 * @param EntityStructureWrapper $wrapper
 *   The wrapped pipedrive data.
 */
function pipedrive_rules_action_pipedriv_save($wrapper, $settings, $state, $element) {
  try {
    // Load library and use it to save the sync data.
    $pipedrive = pipedrive_load_library();
    $types = pipedrive_data_types();
    $type = str_replace('pipedrive_', '', $wrapper->type());
    if (isset($types[$type])) {
      $sync_data = $wrapper->value();
      pipedrive_prepare_sync_data($sync_data);
      if (!empty($sync_data->id)) {
        $synced = $pipedrive->{$types[$type]}()
          ->update($sync_data->id, (array) $sync_data);
      }
      else {
        $synced = $pipedrive->{$types[$type]}()
          ->add((array) $sync_data);
      }
    }
  }
  catch (\Benhawker\Pipedrive\Exceptions\PipedriveException $e) {
    throw new RulesEvaluationException($e->getMessage(), array(), $element);
  }
}