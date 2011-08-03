<?php
// $Id$

/**
 * @file theme.inc
 *
 * An array of preprocessors to fill variables for templates and helper
 * functions to make theming easier.
 */
function template_preprocess_views_gas_catalog(&$vars) {
  $views_path = drupal_get_path('module', 'views');
  require_once "./$views_path/theme/theme.inc";
//  dpm($vars);
  template_preprocess_views_view_table($vars);
//  dpm($vars);

  if($vars['view']->total_rows == 0) {
    return;
  }
  $vars['gas_catalog'] = drupal_get_form('gas_catalog_form', $vars);
/*
  $rows = $vars['rows'];
  foreach($rows as $num => $row) {
    $vars['rows'][$num]['qty'] = drupal_render($form['items'][$row['nid']]);
  }
  $vars['tfoot'] = drupal_render($form);
*/
//dpm($vars);

}

function template_preprocess_views_gas_conti(&$vars) {
  $views_path = drupal_get_path('module', 'views');
  require_once "./$views_path/theme/theme.inc";
//  dpm($vars);
  template_preprocess_views_view_table($vars);
//  dpm($vars);

  $vars['gas_content'] = 'pippo';
  if($vars['view']->total_rows == 0) {
    return;
  }
  $vars['gas_form'] = drupal_get_form('gas_conti_form', $vars);
}

function template_preprocess_views_gas_ordini(&$vars) {
  $views_path = drupal_get_path('module', 'views');
  require_once "./$views_path/theme/theme.inc";
//  dpm($vars);
  template_preprocess_views_view_table($vars);
//  dpm($vars);

  $vars['gas_content'] = 'pippo';
  if(empty($vars['rows'])) {
    return;
  }
  $vars['gas_form'] = drupal_get_form('gas_ordini_form', $vars);
dsm('zut');
}

