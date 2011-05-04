<?php

/**
* Shift colors in HSL color space
* @param color
* CSS hex color to be shifted (e.g. #000000 )
* @param $h
* Hue shift, normalized to a fraction of 1
* @param $s
* Saturation shift, normalized to a fraction of 1
* @param $l
* Lightness shift, normalized to a fraction of 1
* @return a string containing a CSS hexcolor (e.g. #000000 )
*/

function color_shift($color,$h,$s,$l) {
  $newcolor = _color_unpack($color,TRUE); // hex to RGB
  $newcolor = _color_rgb2hsl($newcolor); // RGB to HSL
  $newcolor[0] += $h;
  //if ($newcolor[0] > 1) { $newcolor[0] = 1; }
  //if ($newcolor[0] < 0) { $newcolor[0] = 0; }
  $newcolor[1] += $s;
  if ($newcolor[1] > 1) { $newcolor[1] = 1; }
  if ($newcolor[1] < 0) { $newcolor[1] = 0; }
  $newcolor[2] += $l;
  if ($newcolor[2] > 1) { $newcolor[2] = 1; }
  if ($newcolor[2] < 0) { $newcolor[2] = 0; }
  $newcolor = _color_hsl2rgb($newcolor); // Back to RGB
  $newcolor = _color_pack($newcolor,TRUE); // RGB back to hex
  return $newcolor;
}

/**
* Autohift colors in HSL color space
* @param color
* CSS hex color to be shifted (e.g. #000000 )
* @param $X_min
* Hue/Saturation/Lightness minimum value, normalized to a fraction of 1
* @param $X_max
* Hue/Saturation/Lightness maximum value, normalized to a fraction of 1
* @return a string containing a CSS hexcolor (e.g. #000000 )
*/
function color_autoshift($color,$min_h,$max_h,$min_s,$max_s,$min_l,$max_l) {
  $newcolor = _color_unpack($color,TRUE); // hex to RGB
  $newcolor = _color_rgb2hsl($newcolor); // RGB to HSL
  if ($min_h){
    if ($newcolor[0] < $min_h) { $newcolor[0] = $min_h; }
  }
  if ($max_h){
    if ($newcolor[0] > $max_h) { $newcolor[0] = $max_h; }
  }
  if ($min_s){
    if ($newcolor[1] < $min_s) { $newcolor[1] = $min_s; }
  }
  if ($max_s){
    if ($newcolor[1] > $max_s) { $newcolor[1] = $max_s; }
  }
  if ($min_l){
    if ($newcolor[2] < $min_l) { $newcolor[2] = $min_l; }
  }
  if ($max_l){
    if ($newcolor[2] > $max_l) { $newcolor[2] = $max_l; }
  }
  $newcolor = _color_hsl2rgb($newcolor); // Back to RGB
  $newcolor = _color_pack($newcolor,TRUE); // RGB back to hex
  return $newcolor;
}