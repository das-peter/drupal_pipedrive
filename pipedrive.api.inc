<?php
use Benhawker\Pipedrive\Pipedrive;

/**
 * Loads the Pipedrive Library
 * @link https://developers.pipedrive.com/v1 Pipedrive API Documentation @endlink
 * @return Pipedrive
 */
function pipedrive_load_library()
{
    $library = libraries_load('pipedrive');

    $pipedrive = new Pipedrive(variable_get('pipedrive_api_token'));

    return $pipedrive;
}