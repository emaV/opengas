<?php
// $Id: mp_wallet.admin.inc,v 1.1 2011/01/25 16:12:04 aronnovak Exp $

/**
 * @file
 *   mp_wallet configuration
 */

/**
 * Settings for the wallet
 */
function mp_wallet_settings_form() {
  module_load_include('inc', 'mp_wallet', 'mp_wallet');
  $form['#attributes'] = array('enctype' => 'multipart/form-data');
  $form['mp_wallet_site_wallet_uid'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_site_wallet_uid', 'admin'),
    '#title' => t('Site-wallet user (drupal user UID)'),
  );
  $form['mp_wallet_credit_name'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_credit_name', t('points')),
    '#title' => t('Credit name'),
  );
  $form['mp_wallet_credit_name_singular'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_credit_name_singular', t('point')),
    '#title' => t('Credit name in singular form'),
  );
  $icon = variable_get('mp_wallet_credit_icon_path', '');
  $form['mp_wallet_credit_icon'] = array(
    '#type' => 'file',
    '#title' => t('Credit icon image'),
    '#suffix' => !empty($icon) ? theme('image', $icon) : '',
  );
  $form['mp_wallet_use_icon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use credit icon instead of text'),
    '#default_value' => variable_get('mp_wallet_use_icon', FALSE),
  );
  $form['mp_wallet_credit_rate'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_credit_rate', 1),
    '#title' => t('Credit exchange rate'),
    '#description' => t('Exhange rate between virtual money inside the site and the real-money transactions. For example if the rate is 0.5 and the user withdraws 10 virtual units, (before fee calculation), it\'s 5 @real.', array('@real' => variable_get('uc_paypal_wpp_currency', 'USD'))),
  );
  $form['mp_wallet_precision'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_precision', 3),
    '#title' => t('Numerical precision'),
    '#description' => t('Round the values to N decimal places.'),
  );
  $form['mp_wallet_precision_real'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_precision_real', 3),
    '#title' => t('Numerical precision for real-money transactions'),
    '#description' => t('Round the values to N decimal places.'),
  );
  $form['mp_wallet_show_real_to_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show real currency on end-user interface'),
    '#description' => t('Show the real currency (for example in USD) when doing transactions. Regardless of this setting, the user will see the amount in real currency when depositing and withdrawing.'),
    '#default_value' => variable_get('mp_wallet_show_real_to_user', TRUE),
  );
  $form['mp_wallet_real_currency'] = array(
    '#value' => t('Real currency of the site: @real. You can edit it at !link', array('@real' => variable_get('uc_paypal_wpp_currency', 'USD'), '!link' => l(t('Payment gateways / PayPal Payments Pro'), 'admin/store/settings/payment/edit/gateways'))),
    '#title' => t('Real currency'),
  );

  $form['explanation']['#value'] = '<div class="explanation">' . t('1 @real = @virtual @name', array('@real' => variable_get('uc_paypal_wpp_currency', 'USD'), '@virtual' => mp_wallet_convert_to_virtual(1), '@name' => variable_get('mp_wallet_credit_name', t('points')))) .
    '<br />' . t('1 @name = @real_v @real', array('@name' => variable_get('mp_wallet_credit_name_singular', t('point')), '@real_v' => mp_wallet_convert_to_real(1), '@real' => variable_get('uc_paypal_wpp_currency', 'USD'))) . '</div>';

  $form['deposit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Deposit settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['deposit']['mp_wallet_min_deposit'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum amount of @name to deposit', array('@name' => variable_get('mp_wallet_credit_name', t('points')))),
    '#default_value' => variable_get('mp_wallet_min_deposit', 2),
  );
  $form['deposit']['mp_wallet_max_deposit'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum amount of @name to deposit', array('@name' => variable_get('mp_wallet_credit_name', t('points')))),
    '#default_value' => variable_get('mp_wallet_max_deposit', 1000),
    '#description' => t('The purpose of this setting is mainly to prevent accidentally big deposits'),
  );
  $form['deposit'] = array_merge($form['deposit'], mp_wallet_fee_settings('deposit', t('deposits')));


  $form['withdraw'] = array(
    '#type' => 'fieldset',
    '#title' => t('Withdraw settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['withdraw']['mp_wallet_min_withdraw'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum amount of @name to withdraw', array('@name' => variable_get('mp_wallet_credit_name', t('points')))),
    '#default_value' => variable_get('mp_wallet_min_withdraw', 2),
  );
  $form['withdraw'] = array_merge($form['withdraw'], mp_wallet_fee_settings('withdraw', t('withdrawals')));

  $form['donate'] = array(
    '#type' => 'fieldset',
    '#title' => t('Donate settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['donate']['mp_wallet_min_donate'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum amount of @name to donate', array('@name' => variable_get('mp_wallet_credit_name', t('points')))),
    '#default_value' => variable_get('mp_wallet_min_donate', 1),
  );
  $form['donate'] = array_merge($form['donate'], mp_wallet_fee_settings('donation', t('donations')));

  // Provide internal transaction fee handling per product class basis
  $result = db_query('SELECT pcid, name FROM {uc_product_classes} UNION SELECT "%s", "%s"', 'product', t('Default Ubercart Product Content Type'));
  while ($c = db_fetch_array($result)) {
    $form['mp_wallet_class_'. $c['pcid']] = array(
      '#type' => 'fieldset',
      '#title' => t('@name product class settings', array('@name' => $c['name'])),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['mp_wallet_class_'. $c['pcid']] = array_merge($form['mp_wallet_class_'. $c['pcid']], mp_wallet_fee_settings('class_'. $c['pcid'], $c['name']));
  }
  $form['#submit'][] = 'mp_wallet_settings_save_icon';
  return system_settings_form($form);
}

/**
 * Saves the uploaded credit icon to its dedicated directory.
 * @todo: The function does not take care of cleaning up the directory.
 */
function mp_wallet_settings_save_icon(&$form, $form_state) {
  $icon_location = file_directory_path() .'/mp_wallet';
  if (!is_writeable($icon_location) || !is_dir($icon_location)) {
    $icon_location = file_create_path($icon_location);
    if (!file_exists($icon_location) && is_writable(file_directory_path())) {
      mkdir($icon_location);
    }
    if (!is_writeable($cache_location)) {
      $icon_location = FALSE;
    }
  }
  
  if ($icon_location) {
    $file = file_save_upload('mp_wallet_credit_icon', array(), $icon_location, FILE_EXISTS_REPLACE);
    if (is_object($file)) {
      file_set_status($file, FILE_STATUS_PERMANENT);
      $icon = $icon_location . '/' . $file->filename;
      variable_set('mp_wallet_credit_icon_path', $icon);
      // Overwrite UC currency sign
      variable_set('uc_currency_sign', mp_wallet_credit_representation(1));
      variable_set('uc_sign_after_amount', TRUE);
    }
  }
}

/**
 * Validates mp_wallet_settings_form().
 */
function mp_wallet_settings_form_validate($form, $form_state) {
  $user = user_load($form_state['values']['mp_wallet_site_wallet_uid']);
  if (!is_object($user) || !is_numeric($form_state['values']['mp_wallet_site_wallet_uid'])) {
    form_set_error('mp_wallet_site_wallet_uid', t('The field should contain a numeric userID'));
  }
  if (empty($form_state['values']['mp_wallet_credit_rate'])) {
    form_set_error('mp_wallet_site_wallet_uid', t("The rate can't be empty nor zero."));
  }
}

/**
 * Generates fee setting form part for the given type
 * It includes base, percentage, minimum and maximum fees for the given product or transaction type.
 */
function mp_wallet_fee_settings($prefix, $name) {
  $form['mp_wallet_' . $prefix . '_fee_base'] = array(
    '#title' => t('Base fee for @name', array('@name' => $name)),
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_' . $prefix . '_fee_base', 0),
  );
  $form['mp_wallet_' . $prefix . '_fee_percentage'] = array(
    '#title' => t('Percentage fee for @name', array('@name' => $name)),
    '#description' => t('Example value: 15, which means 15%.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_' . $prefix . '_fee_percentage', 0),
  );
  $form['mp_wallet_' . $prefix . '_fee_min'] = array(
    '#title' => t('Minimum fee for @name', array('@name' => $name)),
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_' . $prefix . '_fee_min', 0),
  );
  $form['mp_wallet_' . $prefix . '_fee_max'] = array(
    '#title' => t('Maximum fee for @name', array('@name' => $name)),
    '#type' => 'textfield',
    '#default_value' => variable_get('mp_wallet_' . $prefix . '_fee_max', 0),
  );
  return $form;
}

