CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Usage


INTRODUCTION
------------

Maintainer: Steven Monetti <https://www.drupal.org/user/741388>
Project Page: https://www.drupal.org/sandbox/smonetti/2496101

This module enables integration with Pipedrive.com service, and the usage of their API.


INSTALLATION
------------

See http://drupal.org/getting-started/install-contrib for instructions on
how to install or update Drupal modules.

The Libraries module is required.

1. Download the Pipedrive PHP library (https://github.com/TTRGroup/pipedrive-api-php/archive/master.zip)
2. Unzip under sites/all/libraries/pipedrive so that Pipedrive.php is located at sites/all/libraries/pipedrive/src/Benhawker/Pipedrive/Pipedrive.php
3. Enable the module
4. Configure the module at admin/config/services/pipedrive. The API Key can be found under your Pipedrive account at https://[subdomain].pipedrive.com/settings#api.


USAGE
------------

You can now use the Pipedrive class by calling pipedrive_load_library(). Eg:

$pipedrive = pipedrive_load_library();

$person = $pipedrive->persons()->add(array(
    "name" => "John Doe",
    "email" => "john@example.com",
    "phone" => "555-333-2222"
));

API Documentation: https://developers.pipedrive.com/v1
PHP SDK Documentation: https://github.com/TTRGroup/pipedrive-api-php