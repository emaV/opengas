<?php
// $Id: sheetnode_google.import.inc,v 1.1.2.1 2010/11/22 09:29:36 kratib Exp $

require_once(drupal_get_path('module', 'sheetnode') .'/socialcalc.inc');

function _sheetnode_google_import_form() {
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Google username'),
  );
  $form['password'] = array(
    '#type' => 'password',
    '#title' => t('Google password'),
  );
  $form['fetch'] = array(
    '#type' => 'submit',
    '#value' => t('Fetch private spreadsheets'),
    '#ahah' => array(
      'path' => 'sheetnode/google/fetch',
      'method' => 'replace',
      'wrapper' => 'sheetnode-google-spreadsheet-key',
    ),
  );
  $form['google'] = array(
    '#type' => 'markup',
    '#value' => '',
    '#prefix' => '<div id="sheetnode-google-spreadsheet-key">',
    '#suffix' => '</div>',
  );
  $form['google']['error'] = array('#type' => 'markup', '#value' => '<p>');
  $form['google']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#disabled' => TRUE,
  );
  return $form;
}

function &_sheetnode_google_import_fetch(&$form, $form_state) {
  require_once('Zend/Gdata/Spreadsheets.php');
  require_once('Zend/Gdata/ClientLogin.php');

  $form['google']['error'] = array('#type' => 'markup', '#value' => '');
  try {
    $service = Zend_Gdata_Spreadsheets::AUTH_SERVICE_NAME;
    $client = Zend_Gdata_ClientLogin::getHttpClient($form_state['values']['username'], $form_state['values']['password'], $service);
    $spreadsheetService = new Zend_Gdata_Spreadsheets($client);
    $feed = $spreadsheetService->getSpreadsheetFeed();
  }
  catch (Exception $e) {
    $feed = array();
    $form['google']['error'] = array(
      '#type' => 'markup',
      '#value' => rtrim($e->getMessage(), '.') .'.',
      '#prefix' => '<div class="messages error">',
      '#suffix' => '</div>',
    );
  }
  $options = array();
  foreach ($feed->entries as $entry) {
    $id = array_pop(explode('/', $entry->id->text));
    $options[$id] = $entry->title->text;
  }
  $form['google']['key'] = array(
    '#type' => 'select',
    '#title' => t('Private spreadsheets'),
    '#options' => $options,
  );
  $form['google']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#weight' => 99,
    '#disabled' => empty($options),
  );
  return $form['google'];
}

function _sheetnode_google_import_form_validate($form, $form_state) {
  require_once('Zend/Gdata/Spreadsheets.php');
  require_once('Zend/Gdata/ClientLogin.php');

  if (empty($form_state['values']['key'])) {
    form_set_error('key', t('Please enter or select a Google Spreadsheet that you want to import.'));
  }
  if (!empty($form_state['values']['username'])) {
    try {
      $service = Zend_Gdata_Spreadsheets::AUTH_SERVICE_NAME;
      $client = Zend_Gdata_ClientLogin::getHttpClient($form_state['values']['username'], $form_state['values']['password'], $service);
    }
    catch (Exception $e) {
      form_set_error('username', rtrim($e->getMessage(), '.') .'.');
    }
  }
}

function _sheetnode_google_import_form_submit($form, &$form_state) {
  require_once('Zend/Gdata/Spreadsheets.php');
  require_once('Zend/Gdata/ClientLogin.php');

  set_time_limit(0);

  global $user;
  module_load_include('inc', 'node', 'node.pages');

  try {
    if (!empty($form_state['values']['username'])) {
      $service = Zend_Gdata_Spreadsheets::AUTH_SERVICE_NAME;
      $client = Zend_Gdata_ClientLogin::getHttpClient($form_state['values']['username'], $form_state['values']['password'], $service);
    }
    else {
      $client = NULL;
    }
    $spreadsheetService = new Zend_Gdata_Spreadsheets($client);
    $query = new Zend_Gdata_Spreadsheets_DocumentQuery();
    $query->setSpreadsheetKey($form_state['values']['key']);
    $spreadsheet = $spreadsheetService->getSpreadsheetEntry($query);
    $query = new Zend_Gdata_Spreadsheets_DocumentQuery();
    $query->setSpreadsheetKey($form_state['values']['key']);
    $worksheets = $spreadsheetService->getWorksheetFeed($query);
  }
  catch (Exception $e) {
    $msg = 'An error occurred when importing the spreadsheet. The error was:<br />%error';
    $arg = array('%error' => rtrim($e->getMessage(), '.') .'.');
    drupal_set_message(t($msg, $arg), 'error');
    watchdog('sheetnode', $msg, $arg, WATCHDOG_ERROR);
    return;
  }

  // Create spreadsheet URL.
  $key = array_pop(explode('/', $spreadsheet->id->text));
  $domain = array();
  $url = 'http://spreadsheets.google.com/';
  if (preg_match('/@(.*)$/', $form_state['values']['username'], $domain) && $domain[1] != 'gmail.com') {
    $url .= 'a/'. $domain[1] .'/';
  }
  $url .= 'ccc?key='. $key;

  // Create a book if there are more than one sheet.
  $numsheets = intval($worksheets->getTotalResults()->getText());
  if ($numsheets > 1 && module_exists('book')) {
    $node = array('type' => 'book');
    $form_state_book = array();
    $form_state_book['values']['title'] = $spreadsheet->title->text;
    $body = t('Imported from Google Spreadsheet <a href="@url">!sheet</a>.', array('@url' => $url, '!sheet' => $spreadsheet->title->text));
    $form_state_book['values']['body'] = $body;
    $form_state_book['values']['name'] = $user->name;
    $form_state_book['values']['op'] = t('Save');
    $form_state_book['values']['book']['bid'] = 'new';
    $form_state_book['values']['book']['plid'] = -1;
    $form_state_book['values']['book']['weight'] = 0;
    drupal_execute('book_node_form', $form_state_book, (object)$node);
    $book = node_load($form_state_book['nid']);
  }

  // Import all sheets.
  $s = 0;
  foreach ($worksheets->entries as $worksheet) {
    $node = array('type' => 'sheetnode');
    $form_state_node = array();
    $form_state_node['values']['title'] = (isset($book) ? '' : $spreadsheet->title->text .' > ') . $worksheet->title->text;
    $body = isset($book) ? '' : t('Imported from Google Spreadsheet <a href="@url">!sheet</a>.', array('@url' => $url, '!sheet' => $spreadsheet->title->text));
    $form_state_node['values']['body'] = $body;
    $form_state_node['values']['name'] = $user->name;
    $form_state_node['values']['sheetsave'] = _sheetnode_google_import_do($spreadsheetService, $spreadsheet, $worksheet);
    $form_state_node['values']['op'] = t('Save');
    if (isset($book)) { // insert inside the book
      $form_state_node['values']['book']['bid'] = $book->nid;
      $form_state_node['values']['book']['plid'] = $book->book['mlid'];
      $form_state_node['values']['book']['weight'] = $s;
    }

    // Allow other modules to modify the new node's creation parameters.
    // Hook signature: hook_sheetnode_alter(&$form_state_node, $form, $form_state);
    drupal_alter('sheetnode', $form_state_node, $form, $form_state);

    drupal_execute('sheetnode_node_form', $form_state_node, (object)$node);
    $s++;
  }

  // If more than one sheet, create a book to hold them
  if (isset($book)) {
    $form_state['redirect'] = 'node/'. $book->nid;
  }
  else {
    $form_state['redirect'] = 'node/'. $form_state_node['nid'];
  }
}

function _sheetnode_google_import_do($spreadsheetService, $spreadsheet, $worksheet) {
  $sc = array(); // SocialCalc array structure

  try {
    $sc['attribs']['lastrow'] = $worksheet->getRowCount()->text+1;
    $sc['attribs']['lastcol'] = $worksheet->getColumnCount()->text+1;
    
    $worksheet_key = array_pop(explode('/', $worksheet->id->text));
    $spreadsheet_key = array_pop(explode('/', $spreadsheet->id->text));
    $row = 0;
    $page = 100; // TODO: Compute a number instead of choosing an arbitrary one
                 // We're paging because attempting to retrieve large sheets in one go
                 // exhausts the memory.
    $cell = array();
    while ($row < $sc['attribs']['lastrow']-1) {
      $query = new Zend_Gdata_Spreadsheets_CellQuery();
      $query->setSpreadsheetKey($spreadsheet_key);
      $query->setWorksheetId($worksheet_key);
      $query->setMinRow($row);
      $query->setMaxRow(min($sc['attribs']['lastrow']-1, $row+$page));
      $feed = $spreadsheetService->getCellFeed($query);

      foreach ($feed as $entry) {
        $cells[] = array(
          'col' => $entry->getCell()->getColumn(),
          'row' => $entry->getCell()->getRow(),
          'value' => $entry->getCell()->getInputValue(),
          'numeric' => $entry->getCell()->getNumericValue(),
          'content' => $entry->content->text,
        );
      }

      $row += $page;
    }
  }
  catch (Exception $e) {
    $msg = 'An error occurred when opening the worksheet. The error was:<br />%error';
    $arg = array('%error' => rtrim($e->getMessage(), '.') .'.');
    drupal_set_message(t($msg, $arg), 'error');
    watchdog('sheetnode', $msg, $arg, WATCHDOG_ERROR);
    return '';
  }

  if ($cells) foreach ($cells as $cell) {
    try {
      $c = array();
      $c['pos'] = array($cell['col'], $cell['row']);
      $value = $cell['value'];
      $numeric = $cell['numeric'];
      $content = $cell['content'];
      if ($value[0] == '=') { // formula
        $c['datatype'] = 'f';
        $c['valuetype'] = $numeric ? 'n' : 't';
        $c['datavalue'] = $content;
        // Import the Google formula, where cells are referenced as R[delta_row]C[delta_col].
        global $_sheetnode_google_import_col, $_sheetnode_google_import_row;
        $_sheetnode_google_import_col = $c['pos'][0];
        $_sheetnode_google_import_row = $c['pos'][1];
        $formula = preg_replace_callback('/R(?:(\[)?(-?\d+)\]?)?C(?:(\[)?(-?\d+)\]?)?/', '_sheetnode_google_import_formula_replace_coords', $value);
        $formula = str_replace(';', ',', $formula);
        $c['formula'] = substr($formula, 1);
        if ($numeric) _sheetnode_google_import_infer_valueformat($sc, $c, $numeric, trim($content));
      } else if ($numeric) { // number
        $c['datatype'] = 'v';
        $c['valuetype'] = 'n';
        $c['datavalue'] = $numeric;
        _sheetnode_google_import_infer_valueformat($sc, $c, $numeric, trim($value));
      } else { // text, probably :-)
        $html = _filter_url($value, NULL);
        if ($html != $value) {
          $c['valuetype'] = 'th';
          $c['datavalue'] = $html;
        }
        else {
          $c['valuetype'] = 't';
          $c['datavalue'] = $value;
        }
        $c['datatype'] = 't';
      }
      $sc['cells'][socialcalc_cr_to_coord($c['pos'][0],$c['pos'][1])] = $c;
    }
    catch (Exception $e) {
      $msg = 'An error occurred when importing cell %cell. The error was:<br />%error';
      $arg = array('%cell' => $cell->title->text, '%error' => rtrim($e->getMessage(), '.') .'.');
      drupal_set_message(t($msg, $arg), 'warning');
      watchdog('sheetnode', $msg, $arg, WATCHDOG_WARNING);
    }
  }

  $socialcalc = array(
    'sheet' => $sc,
    'edit' => socialcalc_default_edit($sc),
    'audit' => socialcalc_default_audit($sc),
  );
  return socialcalc_save($socialcalc);
}

function _sheetnode_google_import_formula_replace_coords($matches) {
  global $_sheetnode_google_import_col, $_sheetnode_google_import_row;
  $col = $_sheetnode_google_import_col;
  $row = $_sheetnode_google_import_row;
  if (@$matches[4]) {
    if (@$matches[3] == '[') {
      $col += $matches[4];
    }
    else {
      $col = $matches[4];
    }
  }
  if (@$matches[2]) {
    if (@$matches[1] == '[') {
      $row += $matches[2];
    }
    else {
      $row = $matches[2];
    }
  }
  return socialcalc_cr_to_coord($col, $row);
}

/**
 * Helper function to infer a numeric format given a formatted number.
 * Possible formats: number, date, time, percentage
 */
function _sheetnode_google_import_infer_valueformat(&$sc, &$c, $value, $display) {
  if (preg_match('/^-?[\d.]+$/', $display)) { // Regular number
    return;
  }
  if (preg_match('/^-?[\d.,]+$/', $display)) { // Formatted number
    $valueformat = '#,##0.00';
  }
  else if (preg_match('/^-?[\d.,]+%$/', $display)) { // Percent
    $valueformat = '0.00%';
  }
  else if (preg_match('/^-?[\d.,]+([^\d.,]+)$/', $display, $matches)) { // Currency right
    $valueformat = '#,##0.00' . $matches[1];
  }
  else if (preg_match('/^-?([^\d.,]+)[\d.,]+$/', $display, $matches)) { // Currency left
    $valueformat = $matches[1] . '#,##0.00';
  }
  else if (preg_match('/^\d{1,2}([-\/\s])\d{1,2}\1\d{2,4}((?:\s+\d{2}:\d{2}:\d{2}){0,1})$/', $display, $matches)) { // Datetime mm-dd-yyyy hh:mm:ss
    $valueformat = 'mm'. $matches[1] .'dd'. $matches[1] .'yyyy';
    if (@$matches[2]) {
      $valueformat .= ' hh:mm:ss';
    }
  }
  else if (preg_match('/^\d{2,4}([-\/\s])\d{1,2}\1\d{1,2}((?:\s+\d{2}:\d{2}:\d{2}){0,1})$/', $display, $matches)) { // Datetime yyyy-mm-dd hh:mm:ss
    $valueformat = 'yyyy'. $matches[1] .'mm'. $matches[1] .'dd';
    if (@$matches[2]) {
      $valueformat .= ' hh:mm:ss';
    }
  }
  else if (preg_match('/^\d{1,2}-\w{3}-\d{2,4}$/', $display)) { // Date d-mmm-yyyy
    $valueformat = 'd-mmm-yyyy';
  }
  else if (preg_match('/^\w+\s+\d{1,2},\s*\d{2,4}$/', $display)) { // Date mmmm d, yyyy
    $valueformat = 'mmmm d, yyyy';
  }
  else if (preg_match('/^\d{1,2}:\d{1,2}(:\d{1,2}){0,1}((?:\s*\w{1,2}){0,1})$/', $display, $matches)) { // Time
    $valueformat = 'hh:mm';
    if (@$matches[1]) {
      $valueformat .= ':ss';
    }
    if (@$matches[2]) {
      $valueformat .= ' AM/PM';
    }
  }
  else if (preg_match('/^-?[\d.]+E[+-]?\d+$/', $display)) { // Scientific
    $valueformat = '0.00e+000';
  }
  else return;

  // Create the value format and attach it to the cell.
  if (!isset($sc['valueformathash'][$valueformat])) {
    $index = count(@$sc['valueformats'])+1;
    $sc['valueformats'][$index] = $valueformat;
    $sc['valueformathash'][$valueformat] = $index;
  }
  $c['nontextvalueformat'] = $sc['valueformathash'][$valueformat];
}

