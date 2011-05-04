$(document).ready(function(){
  $('ul.menu li').hover(function(){
    $(this).addClass('over');
  }, function() {
    $(this).removeClass('over');
  });
});