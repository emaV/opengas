<?php

// Link Icons
if (theme_get_setting('link_icons_enable') == 1) {
  drupal_add_css($theme_path . 'features/sooper-linkicons/linkicons-'. theme_get_setting('link_icons_set') .'.css', 'theme', 'all');
}