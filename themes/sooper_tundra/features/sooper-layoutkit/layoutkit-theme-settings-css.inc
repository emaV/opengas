<?php
$layout_width_fixed = theme_get_setting('layout_width_fixed');
$layout_width_fluid = theme_get_setting('layout_width_fluid');
$layout_min_width = theme_get_setting('layout_min_width');
$layout_max_width = theme_get_setting('layout_max_width');
$sidebar_left_override = theme_get_setting('sidebar_left_override');
$center_column_override = theme_get_setting('center_column_override');
$sidebar_right_override = theme_get_setting('sidebar_right_override');

if (theme_get_setting('fixedfluid') == 'px') {
  $layout_width_fixed += 2; //to make sure inner layout width == layout_width_fixed even though it has 1px borders on side. This prevents conflict with column width override settings.
  $CSS .= ".sooper-mast { width: {$layout_width_fixed}px; }\n";
} else {
  $CSS .= ".sooper-mast { width: {$layout_width_fluid}%; }\n";
}
if ($layout_min_width) {
  $CSS .= "body .sooper-mast { min-width: {$layout_min_width}px; }\n";
} else {
$CSS .= "body .sooper-mast { min-width: 0; }\n";
}
if ($layout_max_width) {
  $CSS .= "body .sooper-mast { max-width: {$layout_max_width}px; }\n";
} else {
  $CSS .= "body .sooper-mast { max-width: none; }\n";
}
if (theme_get_setting('expand_admin')){
  $CSS .= "body.section-admin .sooper-mast,body.section-admin #footer { width:90%; }\n";
}

if ($sidebar_left_override){
  $CSS .= ".sidebar.side-first { width: {$sidebar_left_override}!important; }\n";
  $CSS .= "#main .sooper-mast { background-position: {$sidebar_left_override} 0!important; }\n";
}

if ($center_column_override){
  $CSS .= "#content { width: {$center_column_override}!important; }\n";
}

if ($sidebar_right_override){
  $CSS .= ".sidebar.side-second { width: {$sidebar_right_override}!important; }\n";
  //this will only work if you differentiate betwene px and % values. but it wont work with px values in a % layout? maybe add an override for the fauxcolumn position
  //$sidebar_right_faux = ;
  //$CSS .= "#main .wrapcolumns { background-position: {$sidebar_right_faux} 0!important; }\n";
}