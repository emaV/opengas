<?php
// $Id: sheetnode_handler_field_range.inc,v 1.1.2.1 2009/09/24 05:08:56 kratib Exp $

class sheetnode_handler_field_range extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['reference'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['reference'] = array(
      '#type' => 'textfield',
      '#title' => t('Range reference'),
      '#default_value' => $this->options['reference'],
      '#description' => t('Use the format A1:C4 for a cell range, A for whole column, 1 for whole row.'),
    );
  }

  function render($values) {
    require_once(drupal_get_path('module', 'sheetnode') .'/socialcalc.inc');
    $sheet = $values->{$this->field_alias};
    if (empty($sheet)) return NULL;
    $sc = socialcalc_parse_sheet($sheet);

    // Parse the range reference.
    $range = preg_split('/:/', $this->options['reference']);
    $start = socialcalc_coord_to_cr($range[0]);
    $end   = socialcalc_coord_to_cr(isset($range[1]) ? $range[1] : $range[0]);
    if (empty($end[0])) $end[0] = $sc['attribs']['lastcol'];
    if (empty($end[1])) $end[1] = $sc['attribs']['lastrow'];

    // Build the range of values.
    $range = array();
    for ($r=$start[1]; $r<=$end[1]; $r++) {
      for ($c=$start[0]; $c<=$end[0]; $c++) {
        $coord = socialcalc_cr_to_coord($c, $r);
        $range[$coord] = isset($sc['cells'][$coord]) ? $sc['cells'][$coord]['datavalue'] : NULL;
      }
    }
    return theme('sheetnode_range', $range);
  }
}

