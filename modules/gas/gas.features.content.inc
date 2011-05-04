<?php

/**
 * Implementation of hook_content_default_fields().
 */
function gas_content_default_fields() {
  $fields = array();

  // Exported field: field_collection
  $fields['sheetnode-field_collection'] = array(
    'field_name' => 'field_collection',
    'type_name' => 'sheetnode',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'datetime',
    'required' => '0',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => 'UTC',
    'tz_handling' => 'site',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'medium',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'j M Y - H:i',
      'input_format_custom' => '',
      'increment' => '30',
      'text_parts' => array(),
      'year_range' => '-1:+1',
      'label_position' => 'above',
      'label' => 'Ritiro',
      'weight' => '-2',
      'description' => 'Data ritiro ordine.',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_expiration
  $fields['sheetnode-field_expiration'] = array(
    'field_name' => 'field_expiration',
    'type_name' => 'sheetnode',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'datetime',
    'required' => '0',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
      'hour' => 'hour',
      'minute' => 'minute',
    ),
    'timezone_db' => 'UTC',
    'tz_handling' => 'site',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'medium',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'j M Y - H:i',
      'input_format_custom' => '',
      'increment' => '30',
      'text_parts' => array(),
      'year_range' => '-1:+1',
      'label_position' => 'above',
      'label' => 'Scadenza',
      'weight' => '-3',
      'description' => 'Data di scadenza dell\'ordine.',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Ritiro');
  t('Scadenza');

  return $fields;
}
