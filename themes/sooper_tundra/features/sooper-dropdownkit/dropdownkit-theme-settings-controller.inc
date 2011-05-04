<?php
if (theme_get_setting('sooperfish_enable')) {
  //Load sooperfish drop-down scripts
  if(is_file($theme_path .'features/sooper-dropdownkit/jquery.sooperfish.js')) {
  drupal_add_js($theme_path .'features/sooper-dropdownkit/jquery.sooperfish.js');
  }
  if(is_file($theme_path .'features/sooper-dropdownkit/invoke-sooperfish.js')) {
  drupal_add_js($theme_path .'features/sooper-dropdownkit/invoke-sooperfish.js');
  }
  drupal_add_js(array('sooperfish' => array('invoke' => theme_get_setting('sooperfish_invoke'))), 'setting');
  drupal_add_js(array('sooperfish' => array('delay' => theme_get_setting('sooperfish_delay'))), 'setting');
  drupal_add_js(array('sooperfish' => array('dualColumn' => theme_get_setting('sooperfish_dualcolumn'))), 'setting');
  drupal_add_js(array('sooperfish' => array('tripleColumn' => theme_get_setting('sooperfish_triplecolumn'))), 'setting');
  drupal_add_js(array('sooperfish' => array('sooperfishWidth' => theme_get_setting('sooperfish_width'))), 'setting');
  drupal_add_js(array('sooperfish' => array('speedShow' => theme_get_setting('sooperfish_speed_show'))), 'setting');
  drupal_add_js(array('sooperfish' => array('easingShow' => theme_get_setting('sooperfish_easing_show'))), 'setting');
  drupal_add_js(array('sooperfish' => array('speedHide' => theme_get_setting('sooperfish_speed_hide'))), 'setting');
  drupal_add_js(array('sooperfish' => array('easingHide' => theme_get_setting('sooperfish_easing_hide'))), 'setting');
  foreach (theme_get_setting('sooperfish_properties_show') as $property => $value) {
    if ($value){
      drupal_add_js(array('sooperfish' => array('animationShow' => array($property => 'show'))), 'setting');
    }
  }
  foreach (theme_get_setting('sooperfish_properties_hide') as $property => $value) {
    if ($value){
      drupal_add_js(array('sooperfish' => array('animationHide' => array($property => 'hide'))), 'setting');
    }
  }
}