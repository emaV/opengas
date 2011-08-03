<?php
// $Id: mp_wallet.report.inc,v 1.1 2011/01/25 16:12:04 aronnovak Exp $

/**
 * @file
 * Generates time-interval grouped reports about various transactions for the administrator.
 * This part heavily depends on a view (sql). See mp_wallet.install, mp_wallet_install() when that view is created.
 */

function mp_wallet_report_deposit() {
  return mp_wallet_report_generate('deposit', 'value_seller');
}

function mp_wallet_report_sell() {
  return mp_wallet_report_generate('sell', 'value_buyer');
}

function mp_wallet_report_donation() {
  return mp_wallet_report_generate('donation', 'value_buyer');
}

function mp_wallet_report_withdraw() {
  return mp_wallet_report_generate('withdraw', 'value_buyer');
}

/**
 * Generates a table what groups the transaction values by user-selected periods.
 */
function mp_wallet_report_generate($type, $sum_field) {
  module_load_include('inc', 'mp_wallet', 'mp_wallet');
  $granularities = array(
    'total' => t('Total'),
    'year' => t('Year'),
    'month' => t('Month'),
    'week' => t('Week'),
    'day' => t('Day '),
  );
  $granularity_name = isset($_GET['granularity']) ? $_GET['granularity'] : 'week';
  if (!in_array($granularity_name, array_keys($granularities))) {
    $granularity_name = 'week';
  }

  $output = '<h3>' . t('Current granularity: @gran', array('@gran' => $granularities[$granularity_name])) . '</h3>';
  // Get the period where it does make sense to collect transactions
  $start = db_result(db_query("SELECT MIN(timestamp) FROM {mp_wallet_transactions} WHERE type='%s'", $type));
  $end = db_result(db_query("SELECT MAX(timestamp) FROM {mp_wallet_transactions} WHERE type='%s'", $type));
  $output .= '<div class="period-info">' . t('"@type"s were done from @start to @end, you can browse this interval below', array('@type' => $type, '@start' => date('Y/m/d', $start), '@end' => date('Y/m/d', $end))) . '</div>';

  // MySQL does the grouping by the desired period
  $result = pager_query("SELECT %s AS date_parts, SUM(%s) AS sum FROM {mp_wallet_transactions_reporting} WHERE type='%s' GROUP BY %s ORDER BY timestamp DESC", variable_get('mp_wallet_history_pager', 10), 0, NULL, $granularity_name, $sum_field, $type, $granularity_name);

  $header = array();
  if ($granularity_name != 'total') {
    $header[] = t('Year');
    if ($granularity_name != 'year') {
      $header[] = t('Month');
    }
    if ($granularity_name == 'week' || $granularity_name == 'day') {
      $header[] = t('Week');
    }
    if ($granularity_name == 'day') {
      $header[] = t('Day');
    }
  }
  $header[] = t('Total amount');

  while ($ival = db_fetch_array($result)) {
    if ($granularity_name == 'total') {
      $rows[] = array((string) $ival['sum'] . ' (' . (string) mp_wallet_convert_to_real($ival['sum']) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');
    }
    else {
      $rows[] = array_merge(explode('|', $ival['date_parts']), array((string) $ival['sum'] . ' (' . (string) mp_wallet_convert_to_real($ival['sum']) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')'));
    }
  }

  $output .= theme('table', $header, $rows);
  $output .= theme('pager', 0, variable_get('mp_wallet_history_pager', 10));
  $placeholders = array();
  foreach ($granularities as $k => $v) {
    if ($k == $granularity_name) {
      $placeholders += array('!' . $k => $granularities[$k]);
    }
    else {
      $placeholders += array('!' . $k => l($granularities[$k], 'admin/store/reports/wallet/' . $type, array('query' => 'granularity=' . $k)));
    }
  }
  $output .= t("Switch granularity: !total, !year, !month, !week, !day", $placeholders);
  return $output;
}

/**
 * Shows various stats about the wallet circulation
 */
function mp_wallet_report_stat() {
  module_load_include('inc', 'mp_wallet', 'mp_wallet');
  $header = array(
    t('Name'),
    t('Value'),
  );
  $rows = array();

  $val = db_result(db_query("SELECT SUM(%s) AS sum FROM {mp_wallet_transactions_reporting} WHERE type='%s'", 'value_seller', 'deposit'));
  $rows[] = array(t('Total deposits'), $val  . ' (' . (string) mp_wallet_convert_to_real($val) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');

  $val = db_result(db_query("SELECT SUM(%s) AS sum FROM {mp_wallet_transactions_reporting} WHERE type='%s'", 'value_seller', 'withdraw'));
  $rows[] = array(t('Total withdraws'), $val  . ' (' . (string) mp_wallet_convert_to_real($val) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');

  $val = mp_wallet_get_balance(variable_get('mp_wallet_site_wallet_uid', 1));
  $rows[] = array(t('Total fees'), $val  . ' (' . (string) mp_wallet_convert_to_real($val) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');

  $val = db_result(db_query("SELECT ROUND(SUM(balance), %d) FROM {mp_wallet_balances} WHERE uid <> %d", variable_get('mp_wallet_precision', 3), variable_get('mp_wallet_site_wallet_uid', 1)));
  $rows[] = array(t('Total @name in circulation', array('@name' => variable_get('mp_wallet_credit_name', 'credits'))), $val  . ' (' . (string) mp_wallet_convert_to_real($val) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');

  $val = db_result(db_query("SELECT ROUND(AVG(balance), %d) FROM {mp_wallet_balances}", variable_get('mp_wallet_precision', 3)));
  $rows[] = array(t('Average @name balance of users', array('@name' => variable_get('mp_wallet_credit_name', 'credits'))), $val  . ' (' . (string) mp_wallet_convert_to_real($val) . ' ' . variable_get('uc_paypal_wpp_currency', 'USD') . ')');

  $total = db_result(db_query("SELECT COUNT(*) FROM {mp_wallet_transactions} WHERE type <> 'commission'"));
  $rows[] = array(t('Total no. of transactions'), $total);

  $result = db_query("SELECT ROUND((COUNT(*) / (SELECT COUNT(*) FROM {mp_wallet_transactions})) * 100, 1) AS percentage, type FROM {mp_wallet_transactions} GROUP BY type");
  while ($type = db_fetch_array($result)) {
    $rows[] = array(t('Percentage of "@name"s', array('@name' => $type['type'])), $type['percentage']);
  }

  $output .= theme('table', $header, $rows);

  return $output;
}

