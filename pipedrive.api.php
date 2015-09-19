<?php
/**
 * @file
 * Pipedrive API / Drupal Integration.
 */

/**
 * Fired before the pipedrive field is saved / data are synced to pipedrive.
 *
 * @param string $type
 *   The pipedrive data type.
 * @param object $sync_data
 *   The object with the data to sync. Set the property "skip_sync" to TRUE to
 *   skip syncing.
 * @param string $entity_type
 *   The entity type of the given entity object.
 * @param object $entity
 *   The entity object the field is attached to.
 * @param array $context
 *   Context information about the invocation. Includes:
 *   - entity_type: The entity type as given in the parameter.
 *   - entity: The entity object as given in the parameter.
 *   - field: The pipedrive field triggering this processing.
 *   - instance: The pipedrive field instance triggering this processing.
 *   - langcode: The language code in use.
 */
function hook_pipedrive_field_sync($type, $sync_data, $entity_type, $entity, $context) {

}
