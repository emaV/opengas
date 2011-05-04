<?php
global $custom_theme;
$custom_theme = $_SESSION['sooper_tundra'];
/**
* Implementation of THEMEHOOK_settings() function.
*
* @param $saved_settings
*   array An array of saved settings for this theme.
* @return
*   array A form array.
*/

function sooper_tundra_settings($saved_settings) {

  /* Store theme paths in variables - if you rename the theme you have to change the second parameter of the drupal_get_path function on the next line */
  $theme_path = drupal_get_path('theme', 'sooper_tundra') .'/';
  $abs_theme_path = base_path().$theme_path;

  // Variable that contains easing options. Chose not to use function because $theme_path would be unavailable
  if (file_exists($theme_path . 'scripts/misc/jquery.easing-sooper.js')) {
    $easing_options = array (
    'linear' => 'linear',
    'swing' => 'swing',    
    'easeInTurbo' => 'easeInTurbo',
    'easeOutTurbo' => 'easeOutTurbo',
    'easeInTurbo2' => 'easeInTurbo2',
    'easeOutTurbo2' => 'easeOutTurbo2',
    'easeInTurbo3' => 'easeInTurbo3',
    'easeOutTurbo3' => 'easeOutTurbo3',
    'easeInSine' => 'easeInSine',
    'easeOutSine' => 'easeOutSine',
    'easeInExpo' => 'easeInExpo',
    'easeOutExpo' => 'easeOutExpo',
    'easeInCirc' => 'easeInCirc',
    'easeOutCirc' => 'easeOutCirc',
    'easeInElastic' => 'easeInElastic',
    'easeOutElastic' => 'easeOutElastic',
    'easeInOvershoot' => 'easeInOvershoot',
    'easeOutOvershoot' => 'easeOutOvershoot',
    'easeInOvershootTurbo' => 'easeInOvershootTurbo',
    'easeOutOvershootTurbo' => 'easeOutOvershootTurbo',
    'easeInBounce' => 'easeInBounce',
    'easeOutBounce' => 'easeOutBounce',
    );
  } else {
    $easing_options = array (
    'linear' => 'linear',
    'swing' => 'swing',
    );
  }

  //Load Defaults
  if(is_file(drupal_get_path('theme', 'sooper_tundra') . '/theme-settings-defaults.php')) {
    include('theme-settings-defaults.php');
  }

  // Create the form widgets using Forms API
  
  // Load SOOPER Features
  foreach (file_scan_directory($theme_path .'features', 'settings.inc', array('.', '..', 'CVS')) as $file) {
    include($file->filename);
  }

  $form['misc'] = array(
    '#title' => t('Other Options'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
	);

  $form['misc']['block_edit'] = array(
    '#type' => 'radios',
    '#title' => t('Edit-Block links'),
    '#default_value' => $settings['block_edit'],
    '#options' => array(
     '0' => t('No'),
     '1' => t('Yes'),
    ),
    '#description' => t('Add edit links on all blocks to allow easy access to blocks management.'),
  );

	$form['misc']['force_eq_heights'] = array(
    '#type' => 'radios',
    '#title' => t('Enforce Equal heights'),
    '#default_value' => $settings['force_eq_heights'],
    '#options' => array(
     '0' => t('No'),
     '1' => t('Yes'),
    ),
    '#description' => t('Enforce equal heights on horizontally aligned blocks (it looks better).'),
  );

  $form['misc']['iepngfix'] = array(
    '#type' => 'radios',
    '#title' => t('Use IE PNG Fix'),
    '#default_value' => $settings['iepngfix'],
    '#options' => array(
     '0' => t('No'),
     '1' => t('Yes'),
    ),
    '#description' => t('Fix Alpha-transparency in PNG support for internet explorer 6.'),
  );
  
  $form['dev'] = array(
    '#title' => t('Developer Options'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
	);  
  
  $form['dev']['grid_debug_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Show Grid Lines'),
  '#default_value' => $settings['grid_debug_enable'],
  '#prefix'        => '<p>Shows lines of grid units. Can be helpful for planning your layout or debugging your CSS.</p>',
  );

  $form['timestamp'] = array(
    '#type' => 'value',
    '#value' => time(),
  );

  /**
   * Validation Function to enforce numeric values
   */
  function is_number($formelement, &$form_state) {
    $thevalue = $formelement['#value'];
    $title = $formelement['#title'];
    if (!is_numeric($thevalue)) {
      form_error($formelement, t("<em>$title</em> must be a number."));
    }
  }
  // Return the additional form widgets
  return $form;
}

/**
 * Helper function to provide a list of sizes for use in theme settings.
 * Originally by Jacine @ Sky theme - thx ;)
 */
function sooper_size_range($start = 11, $end = 16, $unit = false, $default = NULL, $granularity = 1) {
  $range = '';
  if (is_numeric($start) && is_numeric($end)) {
    $range = array();
    $size = $start;
    while ($size >= $start && $size <= $end) {
      if ($size == $default) {
        $range[$size . $unit] = $size . $unit .' (default)';
      }
      else {
        $range[$size . $unit] = $size . $unit;
      }
      $size += $granularity;
    }
  }
  return $range;
}
