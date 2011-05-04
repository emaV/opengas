<?php

/**
 * Force refresh of theme registry.
 * DEVELOPMENT USE ONLY - COMMENT OUT FOR PRODUCTION
 */
 //   drupal_rebuild_theme_registry();
  
/* Store theme paths in php and javascript variables */
GLOBAL $theme;
$theme_path = drupal_get_path('theme', $theme) .'/';
$abs_theme_path = base_path().$theme_path;
/* Store theme paths in Drupal.settings JSON objects - Do not remove this! These bathe paths are used by various other scripts */
drupal_add_js(array('current_theme' => $theme), 'setting');
drupal_add_js(array('theme_path' => $abs_theme_path), 'setting');

/**
 * Implementation of hook_theme().
 *
 * @return
 */
function sooper_tundra_theme() {
  return array(
    // Custom theme functions.
    'system_settings_form' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

// include theme settings controller
if(is_file($theme_path . 'theme-overrides.inc')) {
  include($theme_path . 'theme-overrides.inc');
}

// include theme functions
if(is_file($theme_path . 'theme-functions.inc')) {
  include($theme_path . 'theme-functions.inc');
}

// include theme settings controller
if(is_file($theme_path . 'theme-settings-controller.php')) {
  include($theme_path . 'theme-settings-controller.php');
}

/**
 * Implementation of hook_preprocess()
 *
 * This function checks to see if a hook has a preprocess file associated with
 * it, and if so, loads it.
 *
 * @param $vars
 * @param $hook
 * @return Array
 */
 /* if you rename the theme you have to change the the name of this function and of the drupal_get_path parameter */
function sooper_tundra_preprocess(&$vars, $hook) {
  if(is_file(drupal_get_path('theme', 'sooper_tundra') . '/preprocess/preprocess-' . str_replace('_', '-', $hook) . '.inc')) {
    include('preprocess/preprocess-' . str_replace('_', '-', $hook) . '.inc');
  }
}

// Load the custom stylesheet.
if (is_file($theme_path . 'custom/style-custom.css')) {
  drupal_add_css($theme_path . 'custom/style-custom.css', 'theme', 'all');
}
// Load custom template.php code
if (is_file($theme_path . 'custom/template-custom.php')) {
  include $theme_path . 'custom/template-custom.php';
}

// Load livepreview jQuery for color module tuning
if ((arg(2) == 'themes') && (arg(3) == 'settings') && (arg(4) != FALSE)) {
  if (is_file($theme_path . 'features/sooper-livepreview/sooper-livepreview.js')) {
    drupal_add_js($theme_path .'features/sooper-livepreview/sooper-livepreview.js');
    drupal_add_css($theme_path .'features/sooper-livepreview/sooper-livepreview.css');
    drupal_add_js(array('t_s_page' => arg(4)), 'setting');
  }
}