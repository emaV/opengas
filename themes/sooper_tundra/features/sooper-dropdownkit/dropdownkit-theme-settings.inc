<?php
$form['dropdown'] = array(
'#title' => t('SOOPER DropDownKit'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#weight' => 0,
);

// Width of Drop-down menus
$form['dropdown']['sooperfish_width'] = array(
'#type' => 'select',
'#title' => t('Drop-down Menus Sub-Level Menu Width'),
'#default_value' => $settings['sooperfish_width'],
'#options' => sooper_size_range(150, 300, false, 200, 10),
'#prefix' => '<p>'. t('Note: Drop-down menus go up to 4 levels deep.') .'</p>',
'#description' => t('Sets the width of all the Sublevels of the dropdown menu.'),
);

$form['dropdown']['sooperfish'] = array(
'#title' => t('Sooperfish Dropdowns'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);

$form['dropdown']['sooperfish']['sooperfish_enable'] = array(
'#type'          => 'checkbox',
'#title'         => t('Enable Sooperfish dropdowns'),
'#default_value' => $settings['sooperfish_enable'],
);

$form['dropdown']['sooperfish']['sooperfish_invoke'] = array(
  '#type' => 'textfield',
  '#title' => t('Element for SooperFish invocation'),
  '#default_value' => $settings['sooperfish_invoke'],
  '#description' => t('valid CSS3 selector for pointing SooperFish to the dropdown menu.'),
);

$form['dropdown']['sooperfish']['sooperfish_dualcolumn'] = array(
'#type' => 'textfield',
'#title' => t('2-Column Dropdown'),
'#default_value' => $settings['sooperfish_dualcolumn'],
'#size' => 3,
'#maxlength' => 3,
'#description' => t('Maximum number of list items in a single column-dropdown. When this limit is exceeded a 2-column dropdown will load.'),
'#element_validate' => array('is_number'),
);

$form['dropdown']['sooperfish']['sooperfish_triplecolumn'] = array(
'#type' => 'textfield',
'#title' => t('3-Column Dropdown'),
'#default_value' => $settings['sooperfish_triplecolumn'],
'#size' => 3,
'#maxlength' => 3,
'#description' => t('Maximum number of list items in a 2-column dropdown. When this limit is exceeded a 3-column dropdown will load.'),
'#element_validate' => array('is_number'),
);

$form['dropdown']['sooperfish']['sooperfish_delay'] = array(
'#type' => 'textfield',
'#title' => t('Mouse-Out Delay'),
'#default_value' => $settings['sooperfish_delay'],
'#size' => 6,
'#maxlength' => 6,
'#description' => t('Time in milliseconds the sublevel menus remain visible when you mouse out of the menu. A study by usability expert Jacob Nielsen recommends 500 milliseconds. Do not add "ms" to the number. Set 0 to disable.'),
'#element_validate' => array('is_number'),
);

$form['dropdown']['sooperfish']['show_anim'] = array(
'#title' => t('Menu-Show Animation'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);

$form['dropdown']['sooperfish']['show_anim']['sooperfish_speed_show'] = array(
'#type' => 'textfield',
'#title' => t('Animation Speed'),
'#default_value' => $settings['sooperfish_speed_show'],
'#size' => 6,
'#maxlength' => 6,
'#description' => t('Animation speed in milliseconds. Do not add "ms" to the number.'),
'#element_validate' => array('is_number'),
);

$form['dropdown']['sooperfish']['show_anim']['sooperfish_easing_show'] = array(
'#type' => 'select',
'#title' => t('Animation Easing'),
'#default_value' => $settings['sooperfish_easing_show'],
'#options' => $easing_options,
'#description' => t('This determines how the animation gains speed.'),
);

$form['dropdown']['sooperfish']['show_anim']['sooperfish_properties_show'] = array(
'#type' => 'checkboxes',
'#title' => t('Animation set-up'),
'#default_value' => $settings['sooperfish_properties_show'],
'#options' => array(
  'opacity' => t('Fade'),
  'width' => t('Fold sideways'),
  'height' => t('Fold vertical'),
),
'#description' => t('Select the properties you would like to animate.'),
);

$form['dropdown']['sooperfish']['hide_anim'] = array(
'#title' => t('Menu-hide Animation'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);

$form['dropdown']['sooperfish']['hide_anim']['sooperfish_speed_hide'] = array(
'#type' => 'textfield',
'#title' => t('Animation Speed'),
'#default_value' => $settings['sooperfish_speed_hide'],
'#size' => 6,
'#maxlength' => 6,
'#description' => t('Animation speed in milliseconds. Do not add "ms" to the number.'),
'#element_validate' => array('is_number'),
);

$form['dropdown']['sooperfish']['hide_anim']['sooperfish_easing_hide'] = array(
'#type' => 'select',
'#title' => t('Animation Easing'),
'#default_value' => $settings['sooperfish_easing_hide'],
'#options' => $easing_options,
'#description' => t('This determines how the animation gains speed.'),
);

$form['dropdown']['sooperfish']['hide_anim']['sooperfish_properties_hide'] = array(
'#type' => 'checkboxes',
'#title' => t('Animation set-up'),
'#default_value' => $settings['sooperfish_properties_hide'],
'#options' => array(
  'opacity' => t('Fade'),
  'width' => t('Fold sideways'),
  'height' => t('Fold vertical'),
),
'#description' => t('Select the properties you would like to animate.'),
);
