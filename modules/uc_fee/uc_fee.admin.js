// $Id: uc_fee.admin.js,v 1.1.4.2 2008/11/28 09:01:07 mrfelton Exp $

if (Drupal.jsEnabled) {
	$(document).ready(function() {
    for (var j in Drupal.settings.ucUsedFees) {
      var current  = Drupal.settings.ucUsedFees[j];
 
      // override checkbox
      var temp = this.getElementById('edit-uc-fees-enable-fee-override-'+current);
      if (temp.checked) {
        $('#uc-fee-'+current).show(0);
      }
      else {
        $('#uc-fee-'+current).hide(0);
      }
      
      $('#edit-uc-fees-enable-fee-override-'+current).click(function(){
        var id = this.id.substring(33);
        if (this.checked) {
          $('#uc-fee-'+id).show(0);
        }
        else {
          $('#uc-fee-'+id).hide(0);
        }
      });
     
      // exclude checkbox
      var temp2 = this.getElementById('edit-uc-fees-'+current+'-exclude');
      if (temp2.checked) {
        $('#edit-uc-fees-'+current+'-price').attr('disabled', 'disabled');
      }
      else {
        $('#edit-uc-fees-'+current+'-price').attr('disabled', '');
      }
      
      $('#edit-uc-fees-'+current+'-exclude').click(function(){
        var id = this.id.substr(13,1);
        if (this.checked) {
          $('#edit-uc-fees-'+id+'-price').attr('disabled', 'disabled');
        }
        else {
          $('#edit-uc-fees-'+id+'-price').attr('disabled', '');
        }
      });
      
    };
	});
}