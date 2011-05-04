<?php
  //color schemes
  $info = array('schemes' => array(
    '#88cb00,#666666,#000000,#000000,#444444' => t('Green (Default)'),    
  ),

  // Images to copy over
  'copy' => array(
    'logo.png',
  ),

  // Color areas to fill (x, y, width, height)
  'fill' => array(
    'base' => array(0, 0, 1488, 1057),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/style.css',
  ),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(
  ),

  // color preview css
  'preview_css' => '',

  // Base file for image generation
  'base_image' => 'color/base.png',

  //	blend target
	'blend_target' => '#ffffff'
);
?>