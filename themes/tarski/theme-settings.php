<?php
// $Id: theme-settings.php,v 1.7.2.3 2010/08/19 21:40:07 jarek Exp $

function tarski_settings($saved_settings) {

  $settings = theme_get_settings('tarski');

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

  $settings = array_merge($defaults, $settings);

  // Generate the form using Forms API. http://api.drupal.org/api/7
  $form['custom'] = array(
    '#title' => 'Custom theme settings', 
    '#type' => 'fieldset', 
  );
  $form['custom']['base_font_size'] = array(
    '#title' => 'Base font size',
    '#type' => 'select', 
    '#default_value' => $settings['base_font_size'],
    '#options' => array(
      '9px' => '9px',
      '10px' => '10px',
      '11px' => '11px',
      '12px' => '12px',
      '13px' => '13px',
      '14px' => '14px',
      '15px' => '15px',
      '16px' => '16px',
      '100%' => '100%',
    ),
  );
  $form['custom']['header_image'] = array(
    '#title' => 'Header image', 
    '#type' => 'select',
    '#default_value' => $settings['header_image'],
    '#options' => array(
      'graytree' => 'Gray tree (default)',
      'coffeerings' => 'Coffee rings',
      'spots' => 'Spots',
      'splatter' => 'Splatter',
      'thoughtwind' => 'Thought wind',
      'mountain' => 'Mountain',
      'none' => 'None',
    ),
  );
  $form['custom']['sidebar_first_weight'] = array(
    '#title' => 'First sidebar position', 
    '#type' => 'select',
    '#default_value' => $settings['sidebar_first_weight'],
    '#options' => array(
      -2 => 'Far left',
      -1 => 'Left',
       1 => 'Right',
       2 => 'Far right',
    ),
  );
  $form['custom']['sidebar_second_weight'] = array(
    '#title' => 'Second sidebar position', 
    '#type' => 'select',
    '#default_value' => $settings['sidebar_second_weight'],
    '#options' => array(
      -2 => 'Far left',
      -1 => 'Left',
       1 => 'Right',
       2 => 'Far right',
    ),
  );
  $form['custom']['layout_1'] = array(
    '#title' => '1-column layout', 
    '#type' => 'fieldset',
  );
  $form['custom']['layout_1']['layout_1_min_width'] = array(
    '#type' => 'select',
    '#title' => 'Min width', 
    '#default_value' => $settings['layout_1_min_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['layout_1']['layout_1_max_width'] = array(
    '#type' => 'select',
    '#title' => 'Max width', 
    '#default_value' => $settings['layout_1_max_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['layout_2'] = array(
    '#title' => '2-column layout', 
    '#type' => 'fieldset',
  );
  $form['custom']['layout_2']['layout_2_min_width'] = array(
    '#type' => 'select',
    '#title' => 'Min width', 
    '#default_value' => $settings['layout_2_min_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['layout_2']['layout_2_max_width'] = array(
    '#type' => 'select',
    '#title' => 'Max width', 
    '#default_value' => $settings['layout_2_max_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['layout_3'] = array(
    '#title' => '3-column layout', 
    '#type' => 'fieldset',
  );
  $form['custom']['layout_3']['layout_3_min_width'] = array(
    '#type' => 'select',
    '#title' => 'Min width', 
    '#default_value' => $settings['layout_3_min_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['layout_3']['layout_3_max_width'] = array(
    '#type' => 'select',
    '#title' => 'Max width', 
    '#default_value' => $settings['layout_3_max_width'],
    '#options' => tarski_generate_array(200, 1200, 10, 'px'),
  );
  $form['custom']['copyright_information'] = array(
    '#title' => 'Copyright information',
    '#description' => t('Information about copyright holder of the website - will show up at the bottom of the page'), 
    '#type' => 'textfield',
    '#default_value' => $settings['copyright_information'],
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => FALSE,
  );

  return $form;
}

function tarski_generate_array($min, $max, $increment, $postfix, $unlimited = NULL) {
  $array = array();
  if ($unlimited == 'first') {
    $array['none'] = 'Unlimited';
  }
  for ($a = $min; $a <= $max; $a += $increment) {
    $array[$a . $postfix] = $a . ' ' . $postfix;
  }
  if ($unlimited == 'last') {
    $array['none'] = 'Unlimited';
  }
  return $array;
}

