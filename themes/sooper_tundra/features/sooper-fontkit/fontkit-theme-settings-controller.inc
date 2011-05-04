<?php
if (theme_get_setting('cufon_enable')) {
  drupal_add_js(array('fontKit' => array('invoke' => theme_get_setting('cufon_invoke'))), 'setting');
  
  //Load Cufon font replacement scripts
  if(is_file($theme_path .'features/sooper-fontkit/cufon-yui.js')) {
  drupal_add_js($theme_path .'features/sooper-fontkit/cufon-yui.js');
  }
  if(is_file($theme_path .'features/sooper-fontkit/fonts/'. theme_get_setting('cufon_font_face'))) {
  drupal_add_js($theme_path .'features/sooper-fontkit/fonts/'. theme_get_setting('cufon_font_face'));
  }
  if(is_file($theme_path .'features/sooper-fontkit/invoke-cufon.js')) {
  drupal_add_js($theme_path .'features/sooper-fontkit/invoke-cufon.js');
  }
}
