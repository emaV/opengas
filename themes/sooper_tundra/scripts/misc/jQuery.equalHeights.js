/****
* Sooperthemes equalHeights invocation:
***/

$(function(){ $('.preblocks').equalHeights(1,'.preblocks .content'); });
$(function(){ $('.postblocks').equalHeights(1,'.postblocks .content'); });
$(function(){ $('#slidedown').equalHeights(1,'#slidedown .content'); });

/*-------------------------------------------------------------------- 
 * JQuery Plugin: "EqualHeights" & "EqualWidths"
 * by:	Scott Jehl, Todd Parker, Maggie Costello Wachs (http://www.filamentgroup.com)
 * Modified by Jurriaan Roelofs for sooperthemes.com. Added a parameter to set target element to measure and set height on. Always target the inner-most wrapper of your boxes.
 * Copyright (c) 2007 Filament Group
 * Licensed under GPL (http://www.opensource.org/licenses/gpl-license.php)
 * Version: 2.0, 07.24.2008
--------------------------------------------------------------------*/

$.fn.equalHeights = function(px, element) {
	$(this).each(function(){
		var currentTallest = 0;
		$(element).each(function(i){
			if ($(this).height() > currentTallest) { currentTallest = $(this).height(); }
		});
		if (!px || !Number.prototype.pxToEm) currentTallest = currentTallest.pxToEm(); //use ems unless px is specified
		// for ie6, set height since min-height isn't supported
		if ($.browser.msie && $.browser.version == 6.0) { $(element).css({'height': currentTallest}); }
		$(element).css({'min-height': currentTallest}); 
	});
	return this;
};


/*-------------------------------------------------------------------- 
   Scott Jehl (scott@filamentgroup.com) 
   Maggie Wachs (maggie@filamentgroup.com)
   http://www.filamentgroup.com
 * Copyright (c) 2008 Filament Group
 * Dual licensed under the MIT (filamentgroup.com/examples/mit-license.txt) and GPL (filamentgroup.com/examples/gpl-license.txt) licenses.
 * Version: 2.0, 08.01.2008 
--------------------------------------------------------------------*/

Number.prototype.pxToEm = String.prototype.pxToEm = function(settings){
	//set defaults
	settings = jQuery.extend({
		scope: 'body',
		reverse: false
	}, settings);
	
	var pxVal = (this == '') ? 0 : parseFloat(this);
	var scopeVal;
	var getWindowWidth = function(){
		var de = document.documentElement;
		return self.innerWidth || (de && de.clientWidth) || document.body.clientWidth;
	};	
	
	/* When a percentage-based font-size is set on the body, IE returns that percent of the window width as the font-size. 
		For example, if the body font-size is 62.5% and the window width is 1000px, IE will return 625px as the font-size. 	
		When this happens, we calculate the correct body font-size (%) and multiply it by 16 (the standard browser font size) 
		to get an accurate em value. */
				
	if (settings.scope == 'body' && $.browser.msie && (parseFloat($('body').css('font-size')) / getWindowWidth()).toFixed(1) > 0.0) {
		var calcFontSize = function(){		
			return (parseFloat($('body').css('font-size'))/getWindowWidth()).toFixed(3) * 16;
		};
		scopeVal = calcFontSize();
	}
	else { scopeVal = parseFloat(jQuery(settings.scope).css("font-size")); };
			
	var result = (settings.reverse == true) ? (pxVal * scopeVal).toFixed(2) + 'px' : (pxVal / scopeVal).toFixed(2) + 'em';
	return result;
};