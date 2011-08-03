// Provides AJAX on-the-fly calculation at several operations to know the fees and so on.
Drupal.behaviors.mpWallet = function (context) {

  // Withdraw : Hide payment processor identifiers form
  $('#mp_wallet_identifiers_change_text').click(function(){
    $(this).hide();
    $('#mp_wallet_withdraw_form_wrapper').hide();
    $('.messages').hide();
    $('#mp_wallet_identifiers_form_wrapper').fadeIn();
  });
  $('#mp_wallet_identifiers_form_wrapper #mp_wallet_identifiers_form_cancel').click(function(){
    $('#mp_wallet_identifiers_form_wrapper').hide();
    $('.messages').hide();
    $('#mp_wallet_withdraw_form_wrapper').fadeIn();
    $('#mp_wallet_identifiers_change_text').fadeIn();
  });
  $('#mp_wallet_identifiers_form_alone_wrapper #mp_wallet_identifiers_form_cancel').click(function(){
    window.location = Drupal.settings.basePath+'modal/close';
  });

  function doCalc() {
    if ($('#edit-amount', context).val() != '' && $('#edit-amount', context).val() > 0) {
      $.get(Drupal.settings.mpWallet.convert+"/"+$('#edit-amount', context).val() ,function(data) {
	      $('div.amount-calculation', context).html(data);
      });
    }
    else {
      $('div.amount-calculation', context).html('');
    }
  }

  $("#edit-amount", context).bind('keyup', function() {
    doCalc();
  });
  $("#edit-amount", context).bind('click', function() {
    doCalc();
  });
  $("#edit-amount", context).bind('change', function() {
    doCalc();
  });
  doCalc();
}

