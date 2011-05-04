<?php
// $Id: uc_fee.ca.inc,v 1.1.4.3 2009/05/26 07:27:30 mrfelton Exp $

/**
 * @file
 * This file contains the Conditional Actions hooks and functions necessary to make the
 * fee related entity, conditions, events, and actions work.
 */

/*******************************************************************************
 * Conditional Actions Hooks
 ******************************************************************************/

/**
 * Implementation of hook_ca_entity().
 */
function uc_fee_ca_entity() {
  $entities['fee'] = array(
    '#title' => t('Fee'),
    '#type' => 'object',
  );

  return $entities;
}

/**
 * Implementation of hook_ca_trigger().
 *
 * Register an event for each fee in {uc_fees}.
 */
function uc_fee_ca_trigger() {
  $triggers = array();

  $triggers['calculate_fees'] = array(
    '#title' => t('Calculate fees'),
    '#category' => t('Fees'),
    '#arguments' => array(
      'order' => array('#entity' => 'uc_order', '#title' => t('Order')),
      'fee' => array('#entity' => 'fee', '#title' => t('Fee')),
      'user' => array('#entity' => 'user', '#title' => t('User account')),
    ),
  );

  return $triggers;
}

/**
 * Implementation of hook_ca_condition().
 */
/*function uc_fee_ca_condition() {
  $order_arg = array(
    '#entity' => 'uc_order',
  );
  
  $fee_arg = array(
    '#entity' => 'fee',
  );
  
  $conditions['uc_order_condition_has_products_with_fee'] = array(
    '#title' => t("Check an order's products' should trigger fee"),
    '#category' => t('Order: Product'),
    '#description' => t('Returns TRUE if the order has any products that should trigger the fee.'),
    '#callback' => 'uc_order_condition_has_products_with_fee',
    '#arguments' => array(
      'order' => $order_arg,
      'fee' => $fee_arg,
    ),
  );
  return $conditions;
}
*/

/**
 * Implementation of hook_ca_action().
 */
function uc_fee_ca_action() {
  $actions = array();

  $fees = uc_fee_get_fees();
  foreach ($fees as $fee) {
    $actions['uc_fee_action_apply_fee_'. $fee->fid] = array(
      '#title' => t('Charge a fee: '. $fee->name),
      '#category' => t('Fees'),
      '#callback' => 'uc_fee_action_apply_fee',
      '#arguments' => array(
        'order' => array('#entity' => 'uc_order', '#title' => t('Order')),
        'fee' => array('#entity' => 'fee', '#title' => t('Fee'))
      ),
    );
  }

  return $actions;
}

/**
 * Conditional Actions callback to add a fee.
 *
 * @param $order
 *   The order object being considered.
 * @param $fee
 *   The fee.
 * @return
 *   The line item array representing the fee.
 */
function uc_fee_action_apply_fee($order, $fee) {
  $amount = 0;
  $applications = 0;
  if (is_array($order->products)) {
    foreach ($order->products as $product) {
      // do not apply the fee more than the amount of times specified in max_applications
      if ($fee->max_applications && $applications >= $fee->max_applications) {
        break;
      }
      $product_fee = uc_fee_load($fee->fid, $product->nid, 'product');
      if (!$product_fee->is_active) {
        continue;
      }
      //TODO: should ask the user if they want to use qty or not
      $remaining_applications =  $fee->max_applications - $application_count;
      $this_applications = $fee->max_applications? min($product->qty, $remaining_applications) : $product->qty;
      
      switch ($product_fee->type) {
        case UC_FEE_TYPE_ABSOLUTE:
          $price = $product_fee->price;
          break;
          
        case UC_FEE_TYPE_PERCENTAGE:
          $price = $product->price * ($product_fee->price / 100);
          break;
      }
      $amount += $price * $this_applications;
      $applications += $this_applications;
    }
  }
  if ($amount) {
    $line_item = (object)array('id' => $fee->fid, 'name' => $fee->name, 'amount' => $amount, 'weight' => $fee->weight);
    return $line_item;
  }
}

/**
 * Implementation of hook_ca_predicate().
 *
 * Create a predicate for each event corresponding to a fee.
 */
function uc_fee_ca_predicate() {
  $predicates = array();

  $fees = uc_fee_get_fees();
  foreach ($fees as $fee) {
    $predicates['uc_fee_'. $fee->fid] = array(
      '#title' => $fee->name,
      '#class' => 'fee',
      '#trigger' => 'calculate_fees',
      '#status' => 1,
      '#actions' => array(
        array(
          '#name' => 'uc_fee_action_apply_fee_'. $fee->fid,
          '#title' => t('Apply @fee', array('@fee' => $fee->name)),
          '#argument_map' => array(
            'order' => 'uc_order',
            'fee' => 'fee',
          ),
        ),
      ),
    );
  }
  return $predicates;
}


/******************************************************************************
 * Condition Callbacks and Forms                                              *
 ******************************************************************************/
/*
function uc_order_condition_has_products_with_fee($order, $fee, $settings) {
  $products = array();
  foreach ($order->products as $product) {
    //$message = (t('<pre>@return</pre>', array('@return' => print_r(uc_fee_load($fee->fid, $product->nid, 'product'), TRUE)))); 
    //watchdog('FEE', $message);
    $product_fee = uc_fee_load($fee->fid, $product->nid, 'product');
    if ($product_fee->price) {
      return TRUE;
    }
  }
}*/

