<?php
$width_prop = theme_get_setting('sooperfish_width')-15-1; //subtract margin and border
$CSS .= "body #navbar ul ul {width:". $width_prop ."px;}\n";
$CSS .= "body #navbar ul.menu ul.menu li a {width:". $width_prop ."px;}\n";
$CSS .= "body #navbar ul ul ul {margin-left:". $width_prop ."px;}\n";