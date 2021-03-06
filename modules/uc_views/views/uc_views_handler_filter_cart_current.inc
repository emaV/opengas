<?php
// $Id: uc_views_handler_filter_cart_current.inc,v 1.1.2.1 2010/11/18 17:31:43 longwave Exp $

/**
 * Filter handler for the current cart.
 */
class uc_views_handler_filter_cart_current extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t("Is the current user's cart");
  }

  function query() {
    $this->ensure_my_table();
    $where = "$this->table_alias.$this->real_field ";
$this->accept_null = TRUE; dpm($this);
    if (empty($this->value)) {
      $where .= '<> "***CURRENT_CART_ID***"';
      if ($this->accept_null) {
        $where = '(' . $where . " OR $this->table_alias.$this->real_field IS NULL)";
      }
    }
    else {
      $where .= '= "***CURRENT_CART_ID***"';
      if ($this->accept_null) {
        $where = '(' . $where . " OR $this->table_alias.$this->real_field IS NULL)";
      }

    }
    $this->query->add_where($this->options['group'], $where);
  }
}
