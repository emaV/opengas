<?php

$form['linkicons'] = array(
'#title' => t('SOOPER LinkIcons'),
'#type' => 'fieldset',
'#collapsible' => TRUE,
'#collapsed' => TRUE,
);

$form['linkicons']['link_icons_enable'] = array(
  '#type' => 'radios',
  '#title' => t('Link Icons'),
  '#default_value' => $settings['link_icons_enable'],
  '#options' => array(
   '0' => t('No'),
   '1' => t('Yes'),
  ),
  '#description' => t('Standards compliant browsers with load filetype icons through CSS2.1 selectors (no javascript!). ie6 is not supported in this features.'),
);

if (($settings['cycle_fx']) == 'famfamfam') {
  $linkicons_credit = '<p>Many thanks go out to Mark James from <a href="http://www.famfamfam.com">http://www.famfamfam.com/</a> for supplying awesome free icons.</p>';
} else {
  $linkicons_credit = '<p>Many thanks go out to Yusuke Kamiyamanes from <a href="http://p.yusukekamiyamane.com">http://p.yusukekamiyamane.com/</a> for supplying awesome free icons.</p>';
}

$form['linkicons']['link_icons_set'] = array(
'#type' => 'select',
'#title' => t('Link Icons Package'),
'#default_value' => $settings['cycle_fx'],
'#prefix'        => $linkicons_credit,
'#options'       => array(
  'fugue' => t('fugue'),
  'famfamfam' => t('famfamfam'),
  ),
);