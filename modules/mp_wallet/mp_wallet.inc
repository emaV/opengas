<?php
// $Id: mp_wallet.inc,v 1.1 2011/01/25 16:12:04 aronnovak Exp $

/**
 * @file
 *  Contains business logic for the wallet, placing transactions
 *  and getting logs about the cashflow in the site.
 */

/**
 * Places an internal sell transaction between marketplace users.
 *
 *  @param $buyer
 *    Buyer user object
 *
 *  @param $order
 *    Ubercart order object
 *
 *  @return
 *    TRUE if the transaction is successful, the error message otherwise. Examine with === !
 */
function mp_wallet_internal_transaction($buyer, $order) {
  try {

    $buyer = is_object($buyer) ? $buyer->uid : $buyer;

    // Ensure if the buyer has balance
    $has_balance = db_result(db_query('SELECT COUNT(*) FROM {mp_wallet_balances} WHERE uid = %d', $buyer));
    if (!$has_balance) {
      $entry = array('uid' => $buyer, 'balance' => 0);
      $results[] = drupal_write_record('mp_wallet_balances', $entry);
    }

    $site_wallet = variable_get('mp_wallet_site_wallet_uid', 1);

    if ($buyer == $site_wallet) {
      throw new Exception(t('This account can\'t be used for shopping'));
    }

    db_query("SET autocommit = 0");
    db_query("START TRANSACTION");

    $results = array();
    $products = array();
    // Group products by sellers
    foreach ($order->products as $product) {
      $seller = db_result(db_query("SELECT uid FROM {node} WHERE nid=%d", $product->nid));

      if ($seller == $site_wallet) {
        throw new Exception(t('This account can\'t be used for shopping'));
      }

      if (!empty($seller)) {
        $products[$seller][] = $product;
      }
    }

    foreach ($products as $seller => $seller_products) {
  
      $values = mp_wallet_get_transaction_values($seller_products);

      $results[] = mp_wallet_collect_commission(abs($values['buyer'] - $values['seller']));

      // Buyer part
      $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance - %f WHERE uid = %d', $values['buyer'], $buyer);
      $enough = db_result(db_query('SELECT balance >= 0 FROM {mp_wallet_balances} WHERE uid = %d', $buyer));
      if (!$enough) {
        throw new Exception(t('Not enough balance'));
      }

      // Seller part
      $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance + %f WHERE uid = %d', $values['seller'], $seller);

      if (db_affected_rows() == 0) {
        // Seller does not have a balance entry yet
        $entry = array('uid' => $seller, 'balance' => $values['seller']);
        $results[] = drupal_write_record('mp_wallet_balances', $entry);
      }

      // Record transaction
      $entry = array(
        'buyer' => $buyer,
        'seller' => $seller,
        'value_buyer' => $values['buyer'],
        'value_seller' => $values['seller'],
        'balance_buyer' => mp_wallet_get_balance($buyer),
        'balance_seller' => mp_wallet_get_balance($seller),
        'order_id' => $order->order_id,
        'timestamp' => time(),
      );
      $results[] = drupal_write_record('mp_wallet_transactions', $entry);
    }
    foreach ($results as $result) {
      if (!$result) {
        throw new Exception('Unknown error while completing the transaction');
      }
    }

    db_query('COMMIT');
    db_query('SET autocommit = 1');
    return TRUE;
  }
  catch (Exception $e) {
    db_query('ROLLBACK');
    db_query('SET autocommit = 1');
    return $e->getMessage();
  }
}

function mp_wallet_donate($user, $recipient, $amount) {
  try {

    $user = is_object($user) ? $user->uid : $user;
    $recipient = is_object($recipient) ? $recipient->uid : $recipient;

    $site_wallet = variable_get('mp_wallet_site_wallet_uid', 1);

    if ($recipient == $site_wallet) {
      throw new Exception(t('This account is not available.'));
    }

    db_query("SET autocommit = 0");
    db_query("START TRANSACTION");

    $results = array();

    // Donater part
    $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance - %f WHERE uid = %d', $amount, $user);
    $enough = db_result(db_query('SELECT balance >= 0 FROM {mp_wallet_balances} WHERE uid = %d', $user));
    if (!$enough) {
      throw new Exception(t('Not enough balance'));
    }

    // Recipient part
    $commission = mp_wallet_get_fees($amount, 'donation');
    $results[] = mp_wallet_collect_commission($commission);
    $recipient_amount = round($amount - $commission, variable_get('mp_wallet_precision', 3));
    $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance + %f WHERE uid = %d', $recipient_amount, $recipient);

    if (db_affected_rows() == 0) {
      // Seller does not have a balance entry yet
      $entry = array('uid' => $recipient, 'balance' => $recipient_amount);
      $results[] = drupal_write_record('mp_wallet_balances', $entry);
    }

    // Record transaction
    $entry = array(
      'buyer' => $user,
      'type' => 'donation',
      'seller' => $recipient, // seller is who receives the money, donation: such sell, where there is no product :)
      'value_buyer' => $amount,
      'value_seller' => $recipient_amount,
      'balance_buyer' => mp_wallet_get_balance($user),
      'balance_seller' => mp_wallet_get_balance($recipient),
      'timestamp' => time(),
    );
    $results[] = drupal_write_record('mp_wallet_transactions', $entry);
    foreach ($results as $result) {
      if (!$result) {
        throw new Exception('Unknown error while completing the transaction');
      }
    }

    db_query('COMMIT');
    db_query('SET autocommit = 1');
    return TRUE;
  }
  catch (Exception $e) {
    db_query('ROLLBACK');
    db_query('SET autocommit = 1');
    return $e->getMessage();
  }
}

/**
 * Withdraw money from a wallet to a real payment processor account.
 *
 *  @param $buyer
 *    Buyer user object
 *
 *  @param $order
 *    Ubercart order object
 *
 *  @return
 *    TRUE if the transaction is successful, the error message otherwise. Examine with === !
 */
function mp_wallet_withdraw($user, $amount, $callback, $callback_args) {
  try {

    $user = is_object($user) ? $user->uid : $user;

    db_query("SET autocommit = 0");
    db_query("START TRANSACTION");

    $amount = round($amount, variable_get('mp_wallet_precision', 3));

    $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance - %f WHERE uid = %d', $amount, $user);
    $enough = db_result(db_query('SELECT balance >= 0 FROM {mp_wallet_balances} WHERE uid = %d', $user));
    if (!$enough) {
      throw new Exception(t('Not enough balance'));
    }
    $external = call_user_func_array($callback, $callback_args);
    if (!$external) {
      throw new Exception(t('Error at the external service'));
    }

    // Record transaction
    $entry = array(
      'type' => 'withdraw',
      'buyer' => $user, // The user buys real money and he pays w/ the virtual one
      'seller' => 0,
      'value_buyer' => $amount,
      'value_seller' => 0,
      'balance_buyer' => mp_wallet_get_balance($user),
      'balance_seller' => 0,
      'external_transaction_type' => $external['type'],
      'external_id' => $external['id'],
      'timestamp' => time(),
    );
    $results[] = drupal_write_record('mp_wallet_transactions', $entry);

    db_query('COMMIT');
    db_query('SET autocommit = 1');
    return TRUE;
  }
  catch (Exception $e) {
    db_query('ROLLBACK');
    db_query('SET autocommit = 1');
    return $e->getMessage();
  }
}

/**
 * Add money to a wallet.
 *
 *  @param $user
 *    User object
 *
 *  @param $amount
 *    Amount of virtual credits to add
 *  @param $type
 *    External transaction type, like 'paypal'
 *  @param $id
 *    External transaction id
 *
 *  @return
 *    TRUE if the transaction is successful, the error message otherwise. Examine with === !
 */
function mp_wallet_deposit($user, $amount, $type, $id) {
  try {

    $user = is_object($user) ? $user->uid : $user;

    db_query("SET autocommit = 0");
    db_query("START TRANSACTION");
    $amount = round($amount, variable_get('mp_wallet_precision', 3));
    $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance + %f WHERE uid = %d', $amount, $user);
    if (db_affected_rows() == 0) {
      // User does not have a balance entry yet
      $entry = array('uid' => $user, 'balance' => $amount);
      $results[] = drupal_write_record('mp_wallet_balances', $entry);
    }

    // Record transaction
    $entry = array(
      'type' => 'deposit',
      'buyer' => 0,
      'seller' => $user, // The user sells his real money and gets virtual money to his wallet, that's why he is the seller
      'value_buyer' => 0,
      'value_seller' => $amount,
      'balance_buyer' => 0,
      'balance_seller' => mp_wallet_get_balance($user),
      'external_transaction_type' => $type,
      'external_id' => $id,
      'timestamp' => time(),
    );
    $results[] = drupal_write_record('mp_wallet_transactions', $entry);
    foreach ($results as $result) {
      if (!$result) {
        throw new Exception('Unknown error while completing the transaction');
      }
    }

    db_query('COMMIT');
    db_query('SET autocommit = 1');
    return TRUE;
  }
  catch (Exception $e) {
    db_query('ROLLBACK');
    db_query('SET autocommit = 1');
    return $e->getMessage();
  }
}

/**
 * Adds the given amount to the site wallet user balance and records the commission earning as a transaction into the transaction log
 *
 * @param $amount
 *   The commission amount in virtual currency
 */
function mp_wallet_collect_commission($amount) {
  // Do not pollute the database when the transaction is free
  if ($amount == 0) {
    return TRUE;
  }
  $user = variable_get('mp_wallet_site_wallet_uid', 1);
  $results = array();
  if ($user) {
    $results[] = db_query('UPDATE {mp_wallet_balances} SET balance = balance + %f WHERE uid = %d', $amount, $user);
    if (db_affected_rows() == 0) {
      // User does not have a balance entry yet
      $entry = array('uid' => $user, 'balance' => $amount);
      $results[] = drupal_write_record('mp_wallet_balances', $entry);
    }
    $entry = array(
      'type' => 'commission',
      'buyer' => 0,
      'seller' => $user,
      'value_buyer' => 0,
      'value_seller' => $amount,
      'balance_buyer' => 0,
      'balance_seller' => mp_wallet_get_balance($user),
      'external_id' => $id,
      'timestamp' => time(),
    );
    $results[] = drupal_write_record('mp_wallet_transactions', $entry);
    foreach ($results as $result) {
      if (!$result) {
        return FALSE;
      }
    }
    return TRUE;
  }
  // Site wallet user does not exist, it's a fatal error...
  return FALSE;
}

/**
 * Determines the current balance of a user
 *
 * @param $user
 *   Either a user object or a user ID
 *
 * @return
 *   Available balance
 *
 */
function mp_wallet_get_balance($user) {
  return (float) db_result(db_query("SELECT balance FROM {mp_wallet_balances} WHERE uid=%d", is_object($user) ? $user->uid : $user));
}

/**
 * Retrieves transactions in the given timerange
 * @param $user
 *   User object
 * @param $start
 *   Unix timestamp of the start of range
 * @param $end
 *   Unix timestamp of the end of range
 *
 * @return
 *   Array of transaction arrays
 */
function mp_wallet_get_transactions($user, $start = FALSE, $end = FALSE) {
  $start = $start ? $start : (time() - 1209600);
  $end = $end ? $end : (time() + 5);
  $result = pager_query("SELECT * FROM {mp_wallet_transactions} WHERE (timestamp BETWEEN %d AND %d) AND (buyer = %d OR seller=%d) ORDER BY timestamp DESC", variable_get('mp_wallet_history_pager', 10), 0, NULL, $start, $end, $user->uid, $user->uid);
  $transactions = array();
  while ($tr = db_fetch_array($result)) {
    $transactions[] = $tr;
  }
  return $transactions;
}

/**
 * Fee handling: computes the amount what has to be payed by the buyer and the amount what the seller recieves.
 */
function mp_wallet_get_transaction_values($products) {
  $sum = 0;
  $total_fee = 0;
  foreach ($products as $product) {
    if (!isset($product->price)) {
      $product->price = $product->sell_price;
    }
    if (!isset($product->qty)) {
      $product->qty = 1;
    }
    if (!isset($product->type)) {
      $product->type = db_result(db_query("SELECT type FROM {node} WHERE nid=%d", $product->nid));
    }
    $sum += $product->price * $product->qty;
    $total_fee += mp_wallet_get_fees($product);
  }
  return array('buyer' => round($sum, variable_get('mp_wallet_precision', 3)), 'seller' => round($sum - $total_fee, variable_get('mp_wallet_precision', 3)));
}

/**
 * Calculate fees for a given transaction
 */
function mp_wallet_get_fees($amount, $type = FALSE) {
  $product = is_object($amount);
  if ($product) {
    $type = 'class_'. $amount->type;
    $amount = $amount->price * $amount->qty;
  }
  $base = variable_get('mp_wallet_'. $type .'_fee_base', FALSE);
  if ($base === FALSE && $product) {
    $base = variable_get('mp_wallet_class_product_fee_base', FALSE);
  }
  $percentage = variable_get('mp_wallet_'. $type .'_fee_percentage', FALSE);
  if ($percentage === FALSE && $product) {
    $percentage = variable_get('mp_wallet_class_product_fee_percentage', FALSE);
  }
  $fee = $base + (($amount * $percentage) / 100.0);

  $min = variable_get('mp_wallet_'. $type .'_fee_min', FALSE);
  if ($min === FALSE && $product) {
    $min = variable_get('mp_wallet_class_product_fee_min', FALSE);
  }
  $max = variable_get('mp_wallet_'. $type .'_fee_max', FALSE);
  if ($max === FALSE && $product) {
    $max = variable_get('mp_wallet_class_product_fee_max', FALSE);
  }

  if ($min > 0) {
    $fee = max($min, $fee);
  }

  if ($max > 0) {
    $fee = min($max, $fee);
  }
  return $fee;
}

/**
 * Converts the amount to real-world money currency
 */
function mp_wallet_convert_to_real($amount) {
  return round((float) ($amount * variable_get('mp_wallet_credit_rate', 1)), variable_get('mp_wallet_precision_real', 3));
}

/**
 * Converts the amount to the internal, virtual currency
 */
function mp_wallet_convert_to_virtual($amount) {
  return round((float) ($amount / variable_get('mp_wallet_credit_rate', 1)), variable_get('mp_wallet_precision', 3));
}

/**
 * Withdraws the given amount to the user
 */
function mp_wallet_withdraw_by_paypal($user, $amount) {
  $payment_id = db_result(db_query("SELECT MAX(payment_id) FROM {mp_seller_payments}"));
  $sellers = array();
  $ids = mp_wallet_get_ids($user);
  if (!valid_email_address($ids['paypal'])) {
    throw new Exception(t('The PayPal identifier has to be a valid email address.'));
  }
  $sellers[] = array('email' => $ids['paypal'], 'commission' => $amount, 'uid' => $user->uid, 'payment_id' => $payment_id);
  module_load_include('inc', 'mp_wallet', 'mp_wallet_paypal_masspay');
  $ack = mp_wallet_make_masspay($sellers);

  if ('Success' == $ack) {
    return array('id' => $payment_id, 'type' => 'w_paypal');
  }
  return FALSE;
}

/**
 * Get the list of payment processor ids of the given user
 *
 * @param $user
 *   User object
 * @return
 *   Array keyed by type
 *   Example:
 *   Array
 *   (
 *     [paypal] => "paypalaccount@example.com"
 *   )
 *
 */
function mp_wallet_get_ids($user) {
  $result = db_query("SELECT id, type FROM {mp_wallet_ids} WHERE uid = %d", $user->uid);
  $ids = array();
  while ($i = db_fetch_array($result)) {
    $ids[$i['type']] = $i['id'];
  }
  return $ids;
}

/**
 * Stores the payment processor ids for the given user
 *
 * @param $user
 *   User object
 * @param $ids
 *   For $ids formats, see mp_wallet_get_ids()
 *
 */
function mp_wallet_store_ids($user, $ids) {
  foreach ($ids as $type => $id) {
    db_query("REPLACE INTO {mp_wallet_ids} VALUES (%d, '%s', '%s')", $user->uid, $type, $id);
  }
}

