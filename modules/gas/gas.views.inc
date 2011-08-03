<?php
/**
 * Implementation of hook_views_plugins().
 */
function gas_views_plugins() {
  $path = drupal_get_path('module', 'gas');
  require_once "./$path/theme.inc";
  return array(
    'style' => array(
      'gas_catalog' => array(
        'title' => t('GAS catalog form'),
        'help' => t('Displays rows in a table.'),
        'handler' => 'gas_plugin_style_catalog',
        'path' => $path, 
        'parent' => 'table',
        'theme' => 'views_gas_catalog',
        'theme file' => 'theme.inc',
        'theme path' => $path,
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
      'gas_conti' => array(
        'title' => t('GAS conti'),
        'help' => t('Displays rows in a table.'),
        'handler' => 'gas_plugin_style_conti',
        'path' => $path,
        'parent' => 'table',
        'theme' => 'views_gas_conti',
        'theme file' => 'theme.inc',
        'theme path' => $path,
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
      'gas_ordini' => array(
        'title' => t('GAS edit ordini'),
        'help' => t('Edit form for listino orders.'),
        'handler' => 'gas_plugin_style_ordini',
        'path' => $path,
        'parent' => 'table',
        'theme' => 'views_gas_ordini',
        'theme file' => 'theme.inc',
        'theme path' => $path,
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
    ),
  );
}
