<?php
if (theme_get_setting('slideshowkit_enable')) {

  drupal_add_js(array('featureKit' => array('invoke' => theme_get_setting('cycle_invoke'))), 'setting');
  drupal_add_js(array('featureKit' => array('fx' => theme_get_setting('cycle_fx'))), 'setting');
  drupal_add_js(array('featureKit' => array('timeout' => theme_get_setting('cycle_timeout'))), 'setting');
  drupal_add_js(array('featureKit' => array('continuous' => theme_get_setting('cycle_continuous'))), 'setting');
  drupal_add_js(array('featureKit' => array('speed' => theme_get_setting('cycle_speed'))), 'setting');
  drupal_add_js(array('featureKit' => array('pagerEvent' => theme_get_setting('cycle_pagerEvent'))), 'setting');
  drupal_add_js(array('featureKit' => array('easing' => theme_get_setting('cycle_easing'))), 'setting');
  drupal_add_js(array('featureKit' => array('random' => theme_get_setting('cycle_random'))), 'setting');
  drupal_add_js(array('featureKit' => array('pause' => theme_get_setting('cycle_pause'))), 'setting');
  drupal_add_js(array('featureKit' => array('pauseOnPagerHover' => theme_get_setting('cycle_pauseOnPagerHover'))), 'setting');
  drupal_add_js(array('featureKit' => array('delay' => theme_get_setting('cycle_delay'))), 'setting');
  
  if(is_file($theme_path .'features/sooper-slideshowkit/jquery.cycle.all.min.js')) {
    drupal_add_js($theme_path .'features/sooper-slideshowkit/jquery.cycle.all.min.js');
  }
  if(is_file($theme_path .'features/sooper-slideshowkit/invoke-SlideshowKit.js')) {
    drupal_add_js($theme_path .'features/sooper-slideshowkit/invoke-SlideshowKit.js');
  }
}