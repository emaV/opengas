<?php
// $Id: template.php,v 1.7.2.5 2010/12/31 18:22:14 jarek Exp $

/**
 * Initialize theme settings.
 */
if (is_null(theme_get_setting('base_font_size'))) {
  global $theme_key;
  // Save default theme settings
  $defaults = array(
    'base_font_size' => '12px',
    'header_image' => 'graytree',
    'sidebar_first_weight' => '1',
    'sidebar_second_weight' => '2',
    'layout_1_min_width' => '500px',
    'layout_1_max_width' => '820px',
    'layout_2_min_width' => '650px',
    'layout_2_max_width' => '910px',
    'layout_3_min_width' => '800px',
    'layout_3_max_width' => '980px',
    'copyright_information' => '© 2010 Your Name',
  );

  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge(theme_get_settings($theme_key), $defaults)
  );
  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

function tarski_preprocess_page(&$vars, $hook) {

  // Remove useless "no-sidebars" class from $body_classes variable
  if (preg_match("/no-sidebars/i", $vars['body_classes']) == true) {
    $vars['body_classes'] = str_replace('no-sidebars', '', $vars['body_classes']);
  }

  // Add $custom_body_classes variable
  if ( !empty($vars['sidebar_first']) && !empty($vars['sidebar_second']) ) {
    $vars['classes_array'][] = 'two-sidebars';
  }
  elseif ( !empty($vars['sidebar_first']) || !empty($vars['sidebar_second']) ) {
    $vars['classes_array'][] = 'one-sidebar';
  }
  else {
    $vars['classes_array'][] = 'no-sidebars';
  }
  $vars['classes_array'][] = theme_get_setting('header_image'); 

  $vars['custom_body_classes'] = implode(' ', $vars['classes_array']);

  // Add variables with weight value for each main column
  $vars['weight']['content'] = 0;
  $vars['weight']['sidebar-first'] = 'disabled';
  $vars['weight']['sidebar-second'] = 'disabled';
  if ($vars["sidebar_first"]) {
    $vars['weight']['sidebar-first'] = theme_get_setting('sidebar_first_weight');
  }
  if ($vars["sidebar_second"]) {
    $vars['weight']['sidebar-second'] = theme_get_setting('sidebar_second_weight');
  }

  // Add $main_columns_number variable (used in page-*.tpl.php files)
  $columns = 0;
  foreach (array('content', 'sidebar_first', 'sidebar_second') as $n) {
    if ($vars["$n"]) {
      $columns++;
    }
  }
  $vars['main_columns_number'] = $columns;  

  // Add $footer_columns_number variable to page.tpl.php file
  $columns = 0;
  foreach (array('first', 'second', 'third', 'fourth') as $n) {
    if ($vars["footer_column_$n"]) {
      $columns++;
    }
  }
  $vars['footer_columns_number'] = $columns;

  // Generate dynamic styles
  $base_font_size = theme_get_setting('base_font_size');
  if ($vars['main_columns_number'] == 1) {
    $layout_min_width = theme_get_setting('layout_1_min_width');
    $layout_max_width = theme_get_setting('layout_1_max_width');
  }
  if ($vars['main_columns_number'] == 2) {
    $layout_min_width = theme_get_setting('layout_2_min_width');
    $layout_max_width = theme_get_setting('layout_2_max_width');
  }
  if ($vars['main_columns_number'] == 3) {
    $layout_min_width = theme_get_setting('layout_3_min_width');
    $layout_max_width = theme_get_setting('layout_3_max_width');
  }
  $vars['dynamic_styles'] = "<style type='text/css' media='all'>html { font-size: $base_font_size; } #header, #header-menu, #main, #footer { width: 100%; min-width: $layout_min_width; max-width: $layout_max_width;}</style>";

}

/**
 * Overrides theme_more_link().
 */
function tarski_more_link($url, $title) {
  return '<div class="more-link">'. t('<a href="@link" title="@title">more ›</a>', array('@link' => check_url($url), '@title' => $title)) .'</div>';
}

