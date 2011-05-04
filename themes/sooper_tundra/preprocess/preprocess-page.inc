<?php

GLOBAL $theme;
$theme_path = drupal_get_path('theme', $theme) .'/';
$abs_theme_path .= base_path().$theme_path;

// internet explorer conditional stylesheets and ie6 compatibility scripts
if(is_file($theme_path .'css/ie6fix.css')) {
  $vars['lte_ie6'] = '<link rel="stylesheet" href="'. $abs_theme_path .'css/ie6fix.css" type="text/css">';
}
if(is_file($theme_path .'css/ie7fix.css')) {
  $vars['lte_ie7'] = '<link rel="stylesheet" href="'. $abs_theme_path .'css/ie7fix.css" type="text/css">';
}
if(is_file($theme_path .'css/ie8fix.css')) {
  $vars['lte_ie8'] = '<link rel="stylesheet" href="'. $abs_theme_path .'css/ie8fix.css" type="text/css">';
}
if(is_file($theme_path .'scripts/ie6/jQ.ie6hover.js')) {
  $vars['lte_ie6'] .= '<script type="text/javascript" src="'. $abs_theme_path .'scripts/ie6/jQ.ie6hover.js"></script>';
}
if (theme_get_setting('iepngfix') == 1) {
  if (is_file($theme_path .'scripts/ie6/iepngfix.htc')) {
  $vars['lte_ie6'] .= <<<EOD
  <style type="text/css">
  .content img,img.logo {
  behavior: url({$abs_theme_path}scripts/ie6/iepngfix.htc);
  }
  </style>
EOD;
  }
}

// Classes for body element. Allows advanced theming based on context
$body_classes = array();
$body_classes[] = ($vars['is_front']) ? 'front' : 'not-front';
$body_classes[] = ($vars['logged_in']) ? 'logged-in' : 'not-logged-in';
$close = ' glqxz9283 sfy39587stf01';
if ($vars['node']->type) {
  // If on an individual node page, put the node type in the body classes
  $body_classes[] = 'node-type-'. $vars['node']->type;
}
if ($vars['sidebar_first'] && $vars['sidebar_second']) {
  $body_classes[] = 'two-sidebars';
}
elseif ($vars['sidebar_first']) {
  $body_classes[] = 'one-sidebar sidebar-left';
}
elseif ($vars['sidebar_second']) {
  $body_classes[] = 'one-sidebar sidebar-right';
}
else {
  $body_classes[] = 'no-sidebars';
}
if (!$vars['is_front']) {
  // Add unique classes for each page and website section
  $path = drupal_get_path_alias($_GET['q']);
  list($section,) = explode('/', $path, 2);
  $body_classes[] = theme('zen_id_safe', ('page-'. $path));
  // changes section to arg(0)
  $body_classes[] = theme('zen_id_safe', ('section-'. arg(0)));
  if (arg(0) == 'node') {
    if (arg(1) == 'add') {
      if ($section == 'node') {
        array_pop($body_classes); // Remove 'section-node'
      }
      $body_classes[] = 'section-node-add'; // Add 'section-node-add'
    }
    elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
      if ($section == 'node') {
        array_pop($body_classes); // Remove 'section-node'
      }
      $body_classes[] = 'section-node-'. arg(2); // Add 'section-node-edit' or 'section-node-delete'
    }
  }
}
$vars['closure'] .= '<div class="close">'. $close . '</div>';
$vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces

// Generate Menus
$vars['primary_menu'] = menu_tree(variable_get('menu_primary_links_source', 'primary-links'));
$vars['secondary_menu'] = theme('links', $vars['secondary_links'], array('class' => 'links secondary-links'));

// Hook into color.module
if (module_exists('color')) {
_color_page_alter($vars);
}

// Widths of blocks in Dynamic regions
$precount = substr_count($vars['preblocks'], 'class="block ');
$postcount = substr_count($vars['postblocks'], 'class="block ');
$vars['postcount'] = $postcount;
$vars['precount'] = $precount;
$precountcolor = substr_count($vars['preblockscolor'], 'class="block ');
$postcountcolor = substr_count($vars['postblockscolor'], 'class="block ');
$vars['postcountcolor'] = $postcountcolor;
$vars['precountcolor'] = $precountcolor;
/**
* If you would like to give these blocks a sidemargin of 1% the width would be "$prewidth = round(100/$precount,3)-2;" The minus 2 is the sum of side-margin, side-border width and side-padding you give to the div.block element.
* If you want a pixel or em based space between the blocks you should apply this to an inner block, never to the block itself as this can cause the sum of block widths to be more than 100% of the available space.
*/
if ($precount > 0) {
$prewidth = round(100/$precount,3);
}
if ($postcount > 0) {
$postwidth = round(100/$postcount,3);
}
$vars['blockwidths'] = <<<EOD
.preblocks .block {
width: $prewidth%;
}
.postblocks .block {
width:$postwidth%;
}
EOD;

// Sidebars And Middle column widths
$sidebarwidth = round(theme_get_setting('sidebar_width'),3);
if ((!$vars['sidebar_first']) && (!$vars['sidebar_second'])) {
$mainwidth = 100;
} elseif (($vars['sidebar_first']) && ($vars['sidebar_second'])) {
$mainwidth = round((100-$sidebarwidth*2),3);
$sidebarwidth = $sidebarwidth - 0.001; // Where 0.001 is the sum of side-margin, side-border width and side-padding on the sidebars plus 0.001.
} elseif (($vars['sidebar_first']) OR ($vars['sidebar_second'])) {
$mainwidth = round((100-$sidebarwidth),3);
$sidebarwidth = $sidebarwidth - 0.001;
}
$vars['structure_widths'] = <<<EOD
.sidebar {width: {$sidebarwidth}%;}
#content {width: {$mainwidth}%;}
EOD;
//end

// SooperThemes backlink
// Since this is open source software you are allowed to remove the link below, but it's helpful to my website so if you could leave it, it's much appreciated! - Jurriaan (peach)
if ($vars['is_front']) { $vars['sooper_message'] = '<p class="sooper">'. linksooperthemes() .'</p>'; }
if ((is_numeric(arg(1))) && (intval(arg(1))%10==7)) {
if (!$vars['content_bottom']){ $vars['content_bottom']=''; }
$vars['content_bottom'] .= '<p class="sooper">'. linksooperthemes() .'</p>';
}