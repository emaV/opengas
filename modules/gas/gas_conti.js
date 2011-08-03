Drupal.behaviors.contiNav = function (context) {

  var table = '.conti';

  $('table' + table + ':not(.contiNav-processed)', context)
    .addClass('contiNav-processed')
    .each(function() {
      $("td.user input", this)
        .unbind()
        .focus(function() {
          var table = $(this).parents('table')[0];
          var col = $(this).parents('td').prevAll().length + 1;

          $('table.contiNav-processed tr').removeClass('active');
          $('table.contiNav-processed td').removeClass('active');
          $('table.contiNav-processed th').removeClass('active');

          $(this).parents('tr').addClass('active');
          $("td:nth-child(" + col + ")", table).addClass('active');
          $("th:nth-child(" + col + ")", table).addClass('active');

        })
        .keydown(function(event) {
          var id;
          if(event.keyCode == '40') {
            var col = $(this).parents('td').prevAll().length + 1;
            id = $(this).parents('tr').next().find("td:nth-child(" + col + ") input").attr('id');
          }
          if(event.keyCode == '38') {
            var col = $(this).parents('td').prevAll().length + 1;
            id = $(this).parents('tr').prev().find("td:nth-child(" + col + ") input").attr('id');
          }
          if(event.keyCode == '39') {
            if(this.selectionStart == this.value.length) {
              id = $(this).parents('td').next().find('input').attr('id');
            }
          }
          if(event.keyCode == '37') {
            if(this.selectionStart == 0) {
              id = $(this).parents('td').prev().find('input').attr('id');
            }
          }
          if(id) {
            $('#' + id).focus();
          }
        });
      });
}
