<?php
// $Id: three_four.inc,v 1.1 2010/08/23 22:07:12 bdziewierz Exp $

/**
 * Plugin definition
 */
$plugin = array(
  'title' => t('Three four'),
  'category' => t('Adaptive'),
  'icon' => 'three-four.png',
  'theme' => 'three_four',
  'admin theme' => 'three_four_admin',
  'css' => 'three-four.css',
  'admin css' => 'three-four-admin.css',
  'panels' => array(
    'top_left' => t('Top left'),
    'top_middle' => t('Top middle'),
    'top_right' => t('Top right'),

    'middle_left' => t('Middle left'),
    'middle_middle' => t('Middle middle'),
    'middle_right' => t('Middle right'),

    'bottom_left' => t('Bottom left'),
    'bottom_middle' => t('Bottom middle'),
    'bottom_right' => t('Bottom right'),

    'first_first' => t('First first'),
    'first_second' => t('First second'),
    'first_third' => t('First third'),
    'first_fourth' => t('First fourth'),

    'second_first' => t('Second first'),
    'second_second' => t('Second second'),
    'second_third' => t('Second third'),
    'second_fourth' => t('Second fourth'),

    'third_first' => t('Third first'),
    'third_second' => t('Third second'),
    'third_third' => t('Third third'),
    'third_fourth' => t('Third fourth'),

    'fourth_first' => t('Fourth first'),
    'fourth_second' => t('Fourth second'),
    'fourth_third' => t('Fourth third'),
    'fourth_fourth' => t('Fourth fourth'),
  ),
);