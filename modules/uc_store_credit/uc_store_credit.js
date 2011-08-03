
/**
 * @file
 * Automatically updates the store credit total when line items are updated.
 */

var uc_store_credit_hide_method = 0;
var uc_store_credit_user_total = 0;
var uc_store_credit_cart_total = 0;
var uc_store_credit_line_item_rate = 100;
var uc_store_credit_subtotal_string = 'Subtotal';
var uc_store_credit_next_method = '';

$(document).ready(
  function() {
    $('#edit-panes-payment-current-total').click(
      function() {
        var line_item_total = 0;

        // Loop through the line items and total their value, excluding the
        // subtotal line item since the cart total is calculated separately.
        $.each(li_titles,
          function(a, b) {
            if (li_titles[a] != '' && li_titles[a] != uc_store_credit_subtotal_string && li_summed[a] == 1) {
              line_item_total += li_values[a];
            }
          }
        );

        // Get the whole total by adding the adjusted line item total to the
        // cart total.
        var new_total = uc_store_credit_cart_total + line_item_total * uc_store_credit_line_item_rate;

        // Update the contents of the span on the payment method line to use
        // the new total.
        $('#store-credit-total').html(new_total);

        // Disable/hide the payment method if it is no longer available.
        if (new_total > uc_store_credit_user_total && uc_store_credit_hide_method > 0) {
          $("input:radio[@value=store_credit]").attr('disabled', 'disabled');

          if (uc_store_credit_hide_method == 2) {
            $("input:radio[@value=store_credit]").parent().hide(0);
          }

          // Select the first payment method.
          $("input:radio[@value=" + uc_store_credit_next_method + "]").attr('checked', 'checked').click();
        }
      }
    );
  }
);
