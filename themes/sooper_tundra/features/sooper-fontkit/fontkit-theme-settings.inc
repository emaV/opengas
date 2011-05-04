<?php
$form['typography_options'] = array(
'#title' => t('SOOPER FontKit'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => TRUE,
 '#weight' => -5,
);

// Regular Fonts Settings
$form['typography_options']['body_font_face'] = array(
'#type' => 'select',
'#title' => t('Base Font'),
'#default_value' =>  $settings['body_font_face'],
'#options' => font_list(),
'#description' => t('Select the font set for the body text.'),
);

$form['typography_options']['headings_font_face'] = array(
'#type' => 'select',
'#title' => t('Headings Font'),
'#default_value' =>  $settings['headings_font_face'],
'#options' => font_list(),
'#description' => t('Select the font set for the headings.'),
);

// Cufon Font Replacement

$form['typography_options']['cufon_font_replacement'] = array(
'#title' => t('Cufon Font Replacement'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => FALSE,
);

$form['typography_options']['cufon_font_replacement']['cufon_enable'] = array(
'#type'          => 'checkbox',
'#title'         => t('Enable Cufon font replacement'),
'#default_value' => $settings['cufon_enable'],
'#prefix'        => '<p>Cufon is a script that replaces web fonts with an embedded font. This method does not have any effect on Search Engines or accessibility for screen-readers. You can generate you own Cufon fonts with the <a target=_blank" href="http://cufon.shoqolate.com/generate/">Cufon Generator</a>. For further instructions see (todo: write some documentation on this).</p>',
);

$form['typography_options']['cufon_font_replacement']['cufon_invoke'] = array(
  '#type' => 'textfield',
  '#title' => t('Element for Cufon invocation'),
  '#default_value' => $settings['cufon_invoke'],
  '#description' => t('valid CSS3 selector for pointing Cufon to the text elements to replace.'),
);


if(is_file($theme_path .'features/sooper-fontkit/cufon-yui.js')) {
foreach (file_scan_directory($theme_path .'features/sooper-fontkit/fonts', '.js', array('.', '..', 'CVS')) as $file) {
  $cufon_files[$file->basename] = $file->name;
}
$cufon_font_face_suffix = '<p><strong>'. t('Available font example images:') .'</strong></p>';
foreach (file_scan_directory($theme_path .'features/sooper-fontkit/fonts', '.png', array('.', '..', 'CVS')) as $file) {
  $cufon_font_face_suffix .= theme_image($theme_path .'features/sooper-fontkit/fonts/' .$file->basename);
}
} else {
$cufon_font_face_suffix = '<p class="error">'. t('Cufon script not found, did you download the typography package as instructed on http://drupal.org/project/sooper_prt_gadgetry?') .'</p>';
}
$form['typography_options']['cufon_font_replacement']['cufon_font_face'] = array(
'#type'          => 'select',
'#title'         => t('Cufon Font Face'),
'#default_value' => $settings['cufon_font_face'],
'#options'       => $cufon_files,
'#suffix'        => $cufon_font_face_suffix,
);

/**
 * Helper function to provide a list of fonts for select list in theme settings.
 * Originally by Jacine @ Sky theme - thx ;)
 */
function font_list() {
  $fonts = array(
    'Sans-serif' => array(
      'helvetica' => 'Helvetica/Arial',
      'myriad' => 'Myriad/Calibri',
      'verdana' => 'Verdana',
      'lucida' => 'Lucida Sans',
      'geneva' => 'Geneva',
      'tahoma' => 'Tahoma',
      'trebuchet' => 'Trebuchet',
      'century' => 'Century Gothic',
    ),
    'Serif' => array(
      'georgia' => 'Georgia',
      'palatino' => 'Palatino Linotype',
      'times' => 'Times New Roman',
    ),
  );
  return $fonts;
}
