// $Id: uc_fee.js,v 1.1.4.3 2009/11/16 19:12:13 mrfelton Exp $

/**
 * @file
 * Handle asynchronous requests to calculate fees.
 */

var pane = '';
if ($("input[name*=delivery_]").length) {
  pane = 'delivery'
}
else if ($("input[name*=billing_]").length) {
  pane = 'billing'
}

$(document).ready(function() {
  getFee();
  $("select[name*=delivery_country], "
    + "select[name*=delivery_zone], "
    + "input[name*=delivery_city], "
    + "input[name*=delivery_postal_code], "
    + "select[name*=billing_country], "
    + "select[name*=billing_zone], "
    + "input[name*=billing_city], "
    + "input[name*=billing_postal_code]").change(getFee);
  $("input[name*=copy_address]").click(getFee);
  $('#edit-panes-payment-current-total').click(getFee);
});


/**
 * Get fee calculations for the current cart and line items.
 */
function getFee() {
  var order = serializeOrder();

  if (!!order) {
    $.ajax({
      type: "POST",
      url: Drupal.settings.ucURL.calculateFee,
      data: 'order=' + Drupal.encodeURIComponent(order),
      dataType: "json",
      success: function(fees) {
        var key;
        var render = false;
        var i;
        var j;
        for (j in fees) {
          key = 'fee_' + fees[j].id;
          // Check that this fee is a new line item, or updates its amount.
          if (li_values[key] == undefined || li_values[key] != fees[j].amount) {
            set_line_item(key, fees[j].name, fees[j].amount, Drupal.settings.ucFeeWeight + fees[j].weight / 10, fees[j].summed, false);

            // Set flag to render all line items at once.
            render = true;
          }
        }
        var found;
        // Search the existing fee line items and match them to a returned fee.
        for (key in li_titles) {
          // The fee id is the second part of the line item id if the first
          // part is "fee".
          keytype = key.substring(0, key.indexOf('_'));
          if (keytype == 'fee') {
            found = false;
            li_id = key.substring(key.indexOf('_') + 1);
            for (j in fees) {
              if (fees[j].id == li_id) {
                found = true;
                break;
              }
            }
            // No fee was matched this time, so remove the line item.
            if (!found) {
              delete li_titles[key];
              delete li_values[key];
              delete li_weight[key];
              delete li_summed[key];
              // Even if no fees were added earlier, the display must be
              // updated.
              render = true;
            }
          }
        }
        if (render) {
          render_line_items();
        }
      }
    });
  }
}
