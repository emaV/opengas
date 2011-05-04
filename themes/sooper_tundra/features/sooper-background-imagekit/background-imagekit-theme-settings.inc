<?php
// SOOPER Background-ImageKit
$form['background_options'] = array(
  '#title' => t('SOOPER Background-Image Kit'),
  '#type' => 'fieldset',
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$bg_images['none'] = 'none';
$bg_image_suffix = '<p><strong>'. t('Available background images:') .'</strong></p>';
foreach (file_scan_directory($theme_path .'images/backgrounds', '\.(jpg|gif|png)$', array('.', '..', 'CVS')) as $file) {
  $bg_images[$file->basename] = $file->basename;
  $bg_image_suffix .= '<p>'. $file->basename .'</p> <div class="demo-background" style="background:url(\''. $abs_theme_path .'images/backgrounds/' .$file->basename .'\');"></div>';
}
$form['background_options']['background_image'] = array(
  '#type'          => 'select',
  '#title'         => t('Background Image'),
  '#default_value' => $settings['background_image'],
  '#options'       => $bg_images,
  '#suffix'        => $bg_image_suffix,
  '#prefix'        => '<p>Selecting a new background image makes it visible immediately. If you want to add your own images, add them to the images/backgrounds folder in the theme directory and it will show up here automatically.</p>'
);