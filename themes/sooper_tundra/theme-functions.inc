<?php

function sooper_tundra_zen_id_safe($string) {
  if (is_numeric($string{0})) {
    // If the first character is numeric, add 'n' in front
    $string = 'n'. $string;
  }
  return strtolower(preg_replace('/[^a-zA-Z0-9_-]+/', '-', $string));
}

function linksooperthemes() {
  $key = ord($_SERVER["SERVER_NAME"])%10;
  $links = array(
  '<a href="http://www.sooperthemes.com">Drupal Themes by SooperThemes</a>',
  '<a href="http://www.sooperthemes.com">Drupal templates</a> by SooperThemes',
  '<a href="http://www.sooperthemes.com">Awesome Drupal Themes</a>',
  'Tundra: A <a href="http://www.sooperthemes.com">free Drupal theme</a> by SooperThemes',
  '<a href="http://www.sooperthemes.com">Drupal templates</a> by SooperThemes',
  'SooperThemes.com <a href="http://www.sooperthemes.com">Premium Drupal themes</a>',
  'Professional <a href="http://www.sooperthemes.com">Drupal themes</a> by SooperThemes.com',
  'Awesome <a href="http://www.sooperthemes.com">Drupal theme</a> by SooperThemes',
  '<a href="http://www.sooperthemes.com">Free Drupal theme</a> by www.sooperthemes.com',
  '<a href="http://www.sooperthemes.com">Premium Drupal themes</a>',
  );
  return $links[$key];
}