<?php
if (theme_get_setting('background_image')) {
  if (theme_get_setting('background_image') == 'none') {
  $CSS .= "html body {background-image: none;}";
  } else {
  $CSS .= "html body {background-image: url('". $abs_theme_path ."images/backgrounds/". theme_get_setting('background_image') ."');}";
  }
}