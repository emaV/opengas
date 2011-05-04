<?php
  $form['layout'] = array(
    '#title' => t('SOOPER LayoutKit'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -10,
	);

	$form['layout']['fixedfluid'] = array(
    '#type' => 'radios',
    '#title' => t('Fixed or Fluid width'),
    '#default_value' => $settings['fixedfluid'],
    '#options' => array(
     'px' => t('Fixed width (in pixels)'),
     '%' => t('Fluid width (as percentage of browser width)')
    ),
    '#prefix' => '<p class="greenbutton" id="live-preview-layout">Apply LivePreview!</p>',
  );

  $form['layout']['layout_width_fixed'] = array(
    '#type' => 'textfield',
    '#title' => t('FIXED Layout Width'),
    '#default_value' => $settings['layout_width_fixed'],
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Width in pixels, do not add trailing \'px\'. This field is only used when "Fixed" is selected above.'),
    '#element_validate' => array('is_number'),
  );

  $form['layout']['layout_width_fluid'] = array(
    '#type' => 'textfield',
    '#title' => t('FLUID Layout Width'),
    '#default_value' => $settings['layout_width_fluid'],
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Width in percentage of browser, do not add trailing \'%\'. This field is only used when "Fluid" is selected above.'),
    '#element_validate' => array('is_number'),
  );

  $form['layout']['sidebar_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar Width'),
    '#default_value' => $settings['sidebar_width'],
    '#size' => 6,
    '#maxlength' => 6,
    '#description' => t('Sidebar width as percentage of layout width. The main content area (center) automatically assumes the leftover width. If you want 3 equal width columns it\'s  best to fill in 33.333.'),
    '#element_validate' => array('is_number'),
    '#suffix' => '<p class="bluebutton" id="random-layout" style="clear:both;margin:1em 0;">Set Random Layout!</p>',
  );

  $form['layout']['adv_layout'] = array(
    '#title' => t('Advanced Layout Options'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
	);

  $form['layout']['adv_layout']['layout_min_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Min-width'),
    '#default_value' => $settings['layout_min_width'],
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('CSS min-width setting in pixels. Set 0 to disable.'),
    '#element_validate' => array('is_number'),
  );

  $form['layout']['adv_layout']['layout_max_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Max-width'),
    '#default_value' => $settings['layout_max_width'],
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('CSS max-width setting in pixels. Set 0 to disable.'),
    '#element_validate' => array('is_number'),
  );

  $form['layout']['adv_layout']['sidebar_left_override'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar Left Width Override'),
    '#default_value' => $settings['sidebar_left_override'],
    '#size' => 6,
    '#maxlength' => 6,
    '#description' => t('Use this setting if you need unequal width sidebars. Takes a valid css width value such as "200px" or "20%". Advanced users only, wrong override settings may result in layout collapse. Set 0 to disable.'),
  );

  $form['layout']['adv_layout']['center_column_override'] = array(
    '#type' => 'textfield',
    '#title' => t('Center Column Width Override'),
    '#default_value' => $settings['center_column_override'],
    '#size' => 6,
    '#maxlength' => 6,
    '#description' => t('Use this setting if you need unequal width sidebars. Takes a valid css width value such as "200px" or "20%". Advanced users only, wrong override settings may result in layout collapse. Set 0 to disable.'),
  );

  $form['layout']['adv_layout']['sidebar_right_override'] = array(
    '#type' => 'textfield',
    '#title' => t('Sidebar Right Width Override'),
    '#default_value' => $settings['sidebar_right_override'],
    '#size' => 6,
    '#maxlength' => 6,
    '#description' => t('Use this setting if you need unequal width sidebars. Takes a valid css width value such as "200px" or "20%". Advanced users only, wrong override settings may result in layout collapse. Set 0 to disable.'),
  );

	$form['layout']['adv_layout']['expand_admin'] = array(
    '#type' => 'radios',
    '#title' => t('Expand admin pages'),
    '#default_value' => $settings['expand_admin'],
    '#options' => array(
     '0' => t('No'),
     '1' => t('Yes'),
    ),
     '#description' => t('Expand admin pages to 90% of browser width, to make your site more manageable if regular pages are narrow. Admin pages are all pages in the /admin path.')
  );
