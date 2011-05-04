$Id: README.txt,v 1.1.2.2 2009/04/14 20:20:37 nk Exp $

Node Reference formatters module
--------------------------------
Provides four additional display styles (formatters) for Node Reference CCK field.

Fieldset
- Standard Drupal collapsible fieldset where legend is referenced node title and value is node content in chosen format.

AHAH link
- Button with #ahah property and value of referenced node title. When user clicks on it referenced node is called dynamically
via AHAH callback which is in Drupal core.

jQuery clueTip
- Utilizes jQuery clueTip plugin, nice dynamic (ajax) content loading in a tooltip when user hovers mouse on link.

Thickbox
- Loads referred content into thickbox, requires this module installed. http://drupal.org/thickbox

Administrators may define those three styles on Display fields tab for particular Node reference field. Additionally each of three styles has options for displaying: Full node, Teaser or Custom. Custom style is provided as an extra option for themers and is supposed to be overridden in template.php file, therefore node object is available in appropriate functions which are: theme_nodereference_formatters_fieldset_custom($element), theme_nodereference_formatters_ahah_custom($element), theme_nodereference_formatters_cluetip_custom($element).

Check out this screencast demo: http://freefreeze.biz/nodereference-formatters.html

Installation
------------
1.) Place module in your module's directory and enable it.
2.) For use of jQuery clueTip plugin as a display style download it from here: 
http://plugins.jquery.com/project/cluetip
Note that clueTip requires jQuery dimensions plugin and optionally integrates with jQuery hoverIntent plugin but they're both
shipped along in the same archive.
3.) Once you downloaded clueTip you'll need following files: 'jquery.cluetip.js', 'jquery.dimensions.js', 'jquery.cluetip.css' and as optional 'jquery.hoverIntent.js' and folder images if you want to use hoverIntent options and style your clueTip with images and/or extra css classes efined in jquery.cluetip.css file.
4.) You can put those files wherever you wish but you have to define it's path on the 
Node Reference formatters settings page (admin/settings/nodereference_formatters).    
Default path i.e.: sites/all/plugins/jquery.cluetip/jquery.cluetip.js is recommended as from this location you can easily use it for all other possible needs and for multi-site installations.
5.) For us of Thickbox formatter, set width an height of the Thickbox window on the 
Node Reference formatters settings page (admin/settings/nodereference_formatters).
6.) Navigate to 'Display fields' tab of your content type which uses Node Reference CCK field and select one of the provided display styles (formatters).
7.) If you are using jQuery clueTip you may wish to edit 'nodereference_formatters.js' file to set width of the tooltip, effect etc. IMPORTANT do not change 'attribute' property in this file. This module is written to work with 'href' property rather than 'rel' which is default for jquery.clueTip plugin. jQuery clueTip plugin has many options and it's quite easy to configure. For more information, demo and API check this page:
http://plugins.learningjquery.com/cluetip/


Author
------
Nenad Kesic
nenadkesic@gmail.com