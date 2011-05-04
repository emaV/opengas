<?php
// $Id: uc_fee.admin.inc,v 1.1.2.10 2009/11/16 19:12:13 mrfelton Exp $

/**
 * @file
 * fee administration menu items.
 *
 */

// Builds a paged list and overview of existing product fees.
function uc_fee_admin_form() {
  
  $header = _uc_fee_admin_header();
  $form = array();

  //FIXME: Do we need to limit the columns we ask for?
  $result = pager_query("SELECT f.fid, f.fid, f.name, f.weight, f.type, f.price, f.is_active FROM {uc_fees} AS f GROUP BY f.fid, f.name, f.weight, f.type, f.price". tablesort_sql($header), 30, 0, "SELECT COUNT(fid) FROM {uc_fees}");
  while ($fee = db_fetch_object($result)) {
    $form['fees'][$fee->fid] = array(
      'name' => array(
        '#value' => $fee->name,
      ),
      'weight' => array(
        '#type' => 'weight',
        '#default_value' => $fee->weight,
        '#attributes' => array('class' => 'uc-fee-table-weight'),
      ),
      'type' => array(
        '#value' => theme('uc_fee_type', $fee),
      ),
      'price' => array(
        '#value' => theme('uc_fee_price', $fee),
      ),
      'is_active' => array(
        '#value' => ($fee->is_active)? 'yes' : 'no',
      ),
      /*'max_applications' => array(
        '#value' => $fee->max_applications,
      ),
      'do_end_processing' => array(
        '#value' => $fee->do_end_processing,
      ),
      'is_exclusive' => array(
        '#value' => $fee->is_exclusive,
      ),*/
      'ops' => array(
        '#value' => l(t('edit'), 'admin/store/fees/'. $fee->fid .'/edit') .' '.
                    l(t('conditions'), CA_UI_PATH .'/uc_fee_'. $fee->fid .'/edit/conditions') .' '.
                    l(t('delete'), 'admin/store/fees/'. $fee->fid .'/delete') .' ',
                    
      ),
    );
  }

  if (!empty($form['fees'])) {
    $form['fees']['#tree'] = TRUE;

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save changes'),
      '#weight' => 10,
    );
  }

  return $form;
}

// Displays a paged list and overview of existing product fees.
function theme_uc_fee_admin_form($form) {
  $header = _uc_fee_admin_header();

  if (count(element_children($form['fees'])) > 0) {
    foreach (element_children($form['fees']) as $fid) {
      $row = array(
        drupal_render($form['fees'][$fid]['name']),
        drupal_render($form['fees'][$fid]['weight']),
        drupal_render($form['fees'][$fid]['type']),
        drupal_render($form['fees'][$fid]['price']),
        drupal_render($form['fees'][$fid]['is_active']),
        /*drupal_render($form['fees'][$fid]['max_applications']),
        drupal_render($form['fees'][$fid]['do_end_processing']),
        drupal_render($form['fees'][$fid]['is_exclusive']),*/
        drupal_render($form['fees'][$fid]['ops']),
      );

      $rows[] = array(
        'data' => $row,
        'class' => 'draggable',
      );
    }
  }
  else {
    $rows[] = array(
      array('data' => t('No fees have been added yet.'), 'colspan' => 5),
    );
  }

  drupal_add_tabledrag('uc-fee-table', 'order', 'sibling', 'uc-fee-table-weight');
  $output = theme('table', $header, $rows, array('id' => 'uc-fee-table'));
  $output .= drupal_render($form);

  return $output;
}

function uc_fee_admin_form_submit($form, &$form_state) {

  foreach ($form_state['values']['fees'] as $fid => $fee) {
    db_query("UPDATE {uc_fees} SET weight = %d WHERE fid = %d", $fee['weight'], $fid);
  }
  drupal_set_message(t('The changes have been saved.'));
}

function _uc_fee_admin_header() {
  return array(
    array('data' => t('Name'), 'field' => 'f.name'),
    array('data' => t('Order'), 'field' => 'f.weight', 'sort' => 'asc'),
    array('data' => t('Type'), 'field' => 'f.type'),
    array('data' => t('Price'), 'field' => 'f.price'),
    array('data' => t('Active'), 'field' => 'f.is_active'),
    /*array('data' => t('Max applications'), 'field' => 'f.max_applications'),
    array('data' => t('End processing'), 'field' => 'f.do_end_processing'),
    array('data' => t('Exclusive'), 'field' => 'f.is_exclusive'),*/
    t('Operations'),
  );
}


/**
 * Form builder for product fees.
 *
 * @ingroup forms
 * @see uc_fee_form_validate()
 * @see uc_fee_form_submit()
 */
function uc_fee_form($form_state, $fee = NULL) {
  // If a fee is specified, add its ID as a hidden value.

  if (!empty($fee)) {
    $form['fid'] = array('#type' => 'hidden', '#value' => $fee->fid);
    drupal_set_title(t('Edit fee: %name', array('%name' => $fee->name)));
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('This name will appear to customers on product add to cart forms.'),
    '#default_value' => $fee->name,
    '#required' => TRUE,
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('<b>Optional.</b> Enter the description that will display beneath the fee in the checkout and order panes.'),
    '#default_value' => $fee->description,
    '#maxlength' => 255,
  );
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t("This determines how the fee will be applied. Possibile options are:") .'<br/><b>'. t("Absolute:") .'</b>'. t(" The fee is an absolute price and will be added to the base product price as is.") .'<br/><b>'. t("Percentage:") .'</b>'. t(" The fee works as a percentage multiplier on the base price of the product eg. '10' = 10% (base_price x 1.1)"),
    '#options' => array(UC_FEE_TYPE_ABSOLUTE => t('Absolute'), UC_FEE_TYPE_PERCENTAGE => t('Percentage')),
    '#default_value' => $fee->type? $fee->type : UC_FEE_TYPE_ABSOLUTE,
  );
  $form['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Price'),
    '#default_value' => $fee->price,
    '#description' => t("The amount as a currency valur or percentage, depending on the value of 'Type' (above)."),
    '#size' => 6,
    '#required' => TRUE,
  );
  $form['max_applications'] = array(
    '#title' => t('Max Applications'),
    '#type' => 'textfield',
    '#description' => t('This fee can be applied up to this many times in a single order.  Set to 0 for unlimited.'),
    '#default_value' => 1,
    '#size' => 4,
    '#required' => TRUE,
    '#default_value' => isset($fee->max_applications)? $fee->max_applications : 0,
  );
  $form['do_end_processing'] = array(
    '#title' => t('End Processing'),
    '#type' => 'checkbox',
    '#description' => t('If set and this fee matches, no further fees will be processed.'),
    '#default_value' => $fee->do_end_processing,
  );
  $form['is_exclusive'] = array(
    '#title' => t('Exclusive'),
    '#type' => 'checkbox',
    '#description' => t('If checked, this fee will not be processed if any other fee before this have matched.  If no other fee have matched and this one matches, no further fees will be processed.'),
    '#default_value' => $fee->is_exclusive,
  );
  $form['weight'] = array(
    '#title' => t('Weight'),
    '#type' => 'weight',
    '#description' => t('Determines the order in which fees are applied.'),
    '#required' => TRUE,
    '#default_value' => isset($fee->weight)? $fee->weight : 0,
  );
  $form['is_active'] = array(
    '#title' => t('Active'),
    '#type' => 'checkbox',
    '#description' => 'If not active, this fee will not be applied regardless of any conditions or product level settings.',
    '#default_value' => isset($fee->is_active)? $fee->is_active : 1,
  );
  $form['display_on_product'] = array(
    '#title' => t('Display on product form'),
    '#type' => 'checkbox',
    '#description' => 'Display this fee on product forms where applicable',
    '#default_value' => isset($fee->display_on_product)? $fee->display_on_product : 1,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#suffix' => l(t('Cancel'), 'admin/store/fees'),
  );

  return $form;
}

/**
 * Submit function for uc_fee_add_form().
 */
function uc_fee_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['fid'])) {
    db_query("UPDATE {uc_fees} SET name = '%s', description = '%s',  price = %f, type = %d, max_applications = %d, do_end_processing = %d, is_exclusive = %d, weight = %d, is_active = %d, display_on_product = %d WHERE fid = %d",
      $form_state['values']['name'],
      $form_state['values']['description'],
      $form_state['values']['price'],
      $form_state['values']['type'],
      $form_state['values']['max_applications'],
      $form_state['values']['do_end_processing'],
      $form_state['values']['is_exclusive'],
      $form_state['values']['weight'],
      $form_state['values']['is_active'],
      $form_state['values']['display_on_product'],
      $form_state['values']['fid']);
  }
  else {
    db_query("INSERT INTO {uc_fees} (name, description, price, type, max_applications, do_end_processing, is_exclusive, weight, is_active, display_on_product) VALUES ('%s', '%s', %f, %d, %d, %d, %d, %d, %d, %d)",
      $form_state['values']['name'],
      $form_state['values']['description'],
      $form_state['values']['price'],
      $form_state['values']['type'],
      $form_state['values']['max_applications'],
      $form_state['values']['do_end_processing'],
      $form_state['values']['is_exclusive'], 
      $form_state['values']['weight'],
      $form_state['values']['is_active'],
      $form_state['values']['display_on_product'],
      $form_state['values']['fid']);
  }

  $form_state['redirect'] = 'admin/store/fees';
}

// Confirms the deletion of the given fee.
function uc_fee_delete_confirm($form_state, $fee) {
  // If we got a bunk fee, kick out an error message.
  if (empty($fee)) {
    drupal_set_message(t('There is no fee with that ID.'), 'error');
    drupal_goto('admin/store/fees');
  }

  $form['fid'] = array('#type' => 'value', '#value' => $fee->fid);
  $form['#redirect'] = 'admin/store/fees';

  $count = db_result(db_query("SELECT COUNT(*) FROM {uc_product_fees} WHERE fid = %d", $fee->fid));

  $output = confirm_form($form, t('Are you sure you want to delete the fee %name?', array('%name' => $fee->name)),
              'admin/store/fees', format_plural($count, 'There is @count product with this fee.', 'There are @count products with this fee.'),
              t('Delete'), t('Cancel'));

  return $output;
}

function uc_fee_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_query("DELETE FROM {uc_class_fees} WHERE fid = %d", $form_state['values']['fid']);
    db_query("DELETE FROM {uc_product_fees} WHERE fid = %d", $form_state['values']['fid']);
    db_query("DELETE FROM {uc_fees} WHERE fid = %d", $form_state['values']['fid']);
    drupal_set_message(t('Product fee deleted.'));
  }
}

// Form to associate fees with products or classes.
function uc_object_fees_form($form_state, $object, $type) {
  switch ($type) {
    case 'class':
      $class = $object;
      $id = $class->pcid;
      if (empty($class->name)) {
        drupal_goto('admin/store/products/classes/'. $id);
      }
      drupal_set_title(check_plain($class->name));
      $object_fees = uc_class_get_fees($id);
      break;
    case 'product':
    default:
      $product = $object;
      $id = $product->nid;
      if (empty($product->title)) {
        drupal_goto('node/'. $id);
      }
      drupal_set_title(check_plain($product->title));
      $object_fees = uc_product_get_fees($id, TRUE);
  }

  foreach ($object_fees as $fee) {
    $used_fids[] = $fee->fid;
  }
  
  $form['#tree'] = TRUE;
  if (count($object_fees) > 0) {
    foreach ($object_fees as $fee) {
      $form['uc_fees']['enable_fee_override_'. $fee->fid] = array(
        '#type' => 'checkbox',
        '#title' => t($fee->name),
        '#default_value' => is_null($fee->default_price) ? 0 : 1
      );
      uc_fee_node_settings_form($form, $fee);
    }
    drupal_add_js(array('ucUsedFees' =>  array_values($used_fids)), 'setting');
    drupal_add_js(drupal_get_path('module', 'uc_fee') .'/uc_fee.admin.js');
  }
  
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );
  $form['id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );
  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );

  return $form;
}


/**
 * Helper function for hook_form_alter() renders the settings per node-type.
 */
function uc_fee_node_settings_form(&$form, $fee) {
  $form['uc_fees'][$fee->fid] = array(
    '#type' => 'fieldset',
    '#title' => t($fee->name .' - override settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('id' => 'uc-fee-'. $fee->fid),
  );
  $form['uc_fees'][$fee->fid]['exclude'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude'),
    '#description' => t('Do not apply fee to this product, regardless of any fee conditions.'),
    '#default_value' => !$fee->is_active,
  );
  $form['uc_fees'][$fee->fid]['price'] = array(
    '#type' => 'textfield',
    '#title' => t('Price'),
    '#description' => t('Set a custom price for this fee, that is applicable to this product only.') .'<br>'. t('The global value for this fee is currently set to @price', array(
      '@price' => theme('uc_fee_price', $fee),
    )),
    '#default_value' => is_null($fee->price) ? $fee->default_price : $fee->price,
    '#size' => 6,
    '#field_prefix' => $fee->type == UC_FEE_TYPE_ABSOLUTE? variable_get('uc_currency_sign', '$') : '%',
  );
}

function uc_object_fees_form_submit($form, &$form_state) {
  if ($form_state['values']['type'] == 'product') {
    $fee_table = '{uc_product_fees}';
    $id = 'nid';
    $sql_type = '%d';
  }
  elseif ($form_state['values']['type'] == 'class') {
    $fee_table = '{uc_class_fees}';
    $id = 'pcid';
    $sql_type = "'%s'";
  }

  foreach ($form_state['values']['uc_fees'] as $fid => $fee) {
    if (substr($fid, 0, 19) == 'enable_fee_override') {
      continue;
    }
    if ($form_state['values']['uc_fees']['enable_fee_override_'. $fid] == 0) {
      if ($form['uc_fees']['enable_fee_override_'. $fid]['#default_value'] != $form_state['values']['uc_fees']['enable_fee_override_'. $fid]) {
        $remove_fids[] = $fid;
      }
    }
    else {
      $price = ($fee['exclude'] == 1)? "NULL" : (float)$fee['price'];
      $is_active = ($fee['exclude'] == 1)? 0 : 1;
      db_query("DELETE FROM $fee_table WHERE fid = %d AND $id = $sql_type", $fid, $form_state['values']['id']);
      db_query("INSERT INTO $fee_table ($id, fid, price, is_active) VALUES ($sql_type, %d, %f, %d)", $form_state['values']['id'], $fid, $price, $is_active);
      $changed = TRUE;
    }
  }
  if (count($remove_fids) > 0) {
    $values = array($form_state['values']['id'], implode(', ', $remove_fids));
    db_query("DELETE FROM $fee_table WHERE $id = $sql_type AND fid IN (%s)", $values);
    drupal_set_message(format_plural(count($remove_fids), '@count fee override has been removed.', '@count fee overrides have been removed.'));
  }

  if ($changed) {
    drupal_set_message(t('The changes have been saved.'));
  }

  if ($form_state['values']['type'] == 'product') {
    $form_state['redirect'] = 'node/'. $form_state['values']['id'] .'/edit/fees';
  }
  else {
    $form_state['redirect'] = 'admin/store/products/classes/'. $form_state['values']['id'] .'/fees';
  }
}
