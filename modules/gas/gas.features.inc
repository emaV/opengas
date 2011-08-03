<?php

/**
 * Implementation of hook_rules_defaults().
 */
function gas_rules_defaults() {
  return array(
    'rules' => array(
      'rules_sheetnode_google_form_submit' => array(
        '#type' => 'rule',
        '#set' => 'event__sheetnode_google_import_form_form_submit',
        '#label' => 'sheetnode google form submit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'GAS',
          'gas' => 'gas',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '1' => array(
            '#type' => 'action',
            '#settings' => array(
              'string' => '<?php echo !empty($_GET[\'gids\']) ? drupal_query_string_encode(array(\'gids\' => $_GET[\'gids\'])) : "";?>',
              '#argument map' => array(
                'string' => 'gids',
              ),
              '#eval input' => array(
                'rules_input_evaluator_php' => array(
                  'string' => array(),
                ),
              ),
            ),
            '#name' => 'rules_add_var_string',
            '#info' => array(
              'label' => 'Add a new string variable (gids)',
              'label callback' => FALSE,
              'module' => 'Rules',
              'base' => 'rules_action_save_variable',
              'arguments' => array(
                'var_name' => array(
                  'type' => 'value',
                  'default value' => 'string',
                ),
                'string' => array(
                  'type' => 'string',
                  'label' => 'string',
                ),
              ),
              'new variables' => array(
                'gids' => array(
                  'label' => 'gids',
                  'label callback' => FALSE,
                  'type' => 'string',
                ),
              ),
            ),
            '#weight' => -10,
          ),
          '2' => array(
            '#weight' => -10,
            '#info' => array(
              'label' => 'Add a new string variable (redirect)',
              'label callback' => FALSE,
              'module' => 'Rules',
              'base' => 'rules_action_save_variable',
              'arguments' => array(
                'var_name' => array(
                  'type' => 'value',
                  'default value' => 'string',
                ),
                'string' => array(
                  'type' => 'string',
                  'label' => 'string',
                ),
              ),
              'new variables' => array(
                'redirect' => array(
                  'label' => 'redirect',
                  'label callback' => FALSE,
                  'type' => 'string',
                ),
              ),
            ),
            '#name' => 'rules_add_var_string',
            '#settings' => array(
              'string' => '<?php echo $form_state[\'redirect\'];?>',
              '#argument map' => array(
                'string' => 'redirect',
              ),
              '#eval input' => array(
                'rules_input_evaluator_php' => array(
                  'string' => array(
                    '0' => 'form',
                    '1' => 'form_state',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
          '5' => array(
            '#weight' => 1,
            '#info' => array(
              'label' => 'Page redirect (edit)',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'path',
                '1' => 'query',
                '2' => 'fragment',
              ),
            ),
            '#name' => 'rules_action_drupal_goto',
            '#settings' => array(
              'path' => '[redirect:string-raw]/edit',
              'query' => '[gids:string]',
              'fragment' => '',
              'force' => 0,
              'immediate' => 0,
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'path' => array(
                    '0' => 'redirect',
                  ),
                  'query' => array(
                    '0' => 'gids',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function gas_views_api() {
  return array(
    'api' => '2',
    'path' => drupal_get_path('module', 'gas'),
  );
}
