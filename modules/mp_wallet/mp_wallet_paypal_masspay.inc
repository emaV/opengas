<?php
// $Id: mp_wallet_paypal_masspay.inc,v 1.1 2011/01/25 16:12:04 aronnovak Exp $

/**
 * @file
 * PayPal Mass Payment related codes
 * Dev docs: https://cms.paypal.com/us/cgi-bin/?cmd=_render-content&content_ID=developer/howto_api_masspay
 */

/**
 * Sends money to recipients via PayPal
 * Based on mp_masspay / mp_masspay_make_masspay
 */
function mp_wallet_make_masspay($sellers) {
  $paypal_user = variable_get('uc_paypal_api_username', '');
  $paypal_pw = variable_get('uc_paypal_api_password', '');
  $paypal_sig = variable_get('uc_paypal_api_signature', '');
  if (empty($paypal_user) || empty($paypal_pw) || empty($paypal_sig)) {
    throw new Exception(t('The PayPal withdrawing is not properly configured, contact the site administrator.'));
  }

  $nvp_request = array(
    'METHOD' => 'MassPay',
    'RECEIVERTYPE' => 'EmailAddress',
  );
  $number = 0;
  foreach ($sellers as $seller) {
    $nvp_request += array('L_EMAIL'. $number => $seller['email']);
    $nvp_request += array('L_AMT'. $number => str_replace(',', '.', $seller['commission'])); // we have to provide . as a decimal separator, but php's setting can be different, force .
    $nvp_request += array('L_UNIQUEID'. $number => $seller['payment_id']);
    $number++;
  }

  $nvp_request += array('CURRENCYCODE' => variable_get('uc_paypal_wpp_currency', 'USD'));
  $nvp_request += array('EMAILSUBJECT' => 'Payment for your sales.');

  $nvp_response = uc_paypal_api_request($nvp_request, variable_get('uc_paypal_wpp_server', 'https://api-3t.sandbox.paypal.com/nvp'));
  if ($nvp_response['ACK'] == 'Success') {
    watchdog('mp_wallet', 'Masspay responds success.');
  }
  else {
    watchdog('mp_wallet', 'Failed to make MassPay NVP request.'
      . 'Error Code: ' . $nvp_response['L_ERRORCODE0'] . ' '
      . 'Error Message: ' . $nvp_response['L_LONGMESSAGE0']);
  }
  return $nvp_response['ACK'];
}
