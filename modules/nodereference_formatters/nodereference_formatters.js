// $Id: nodereference_formatters.js,v 1.1.2.1 2009/04/14 20:20:37 nk Exp $
Drupal.behaviors.nodereference_formatters = function (context) {
  $('a.nodereference-cluetip').cluetip({
    width: '700px', 
    showTitle: false,
    sticky: true, 
    activation: 'hover', 
    attribute: 'href',  // DO NOT change this line unless you know what you are doing.
    // mouseOutClose: true, // Might be bit buggy in some combinations.
    closePosition: 'bottom', 
    closeText: 'X', 
    fx: { 
      open: 'slideDown', 
      openSpeed: '1000'
    },
    onShow: function() { tb_init('a.thickbox') },
    ajaxSettings: {type: 'POST' },
  });
}