<?php
/**
Drupal Core Function Overrides
Author: Jurriaan Roelofs

TABLE OF CONTENTS:
1. Block counter
2. Theme Settings Page Tweaks
*/

// Add first/last classes to blocks. If there is only 1 block inform this too (For grid-unit)
function sooper_tundra_blocks($region) {
  $output = '';

  if ($list = block_list($region)) {
    $i = 1;
    $count = count($list);
    foreach ($list as $key => $block) {
      // $key == <i>module</i>_<i>delta</i>
      if ($count == 1 ) {
        $block->first_last = 'lone-block';
      } else {
        if ($i == 1){ // is this the first block in this region?
          $block->first_last = 'first';
        }
        if ($i == $count){ // is this the last block in this region?
          $block->first_last = 'last';
        }
      }
      $output .= theme('block', $block);
      $i++;
    }
  }

  // Add any content assigned to this region through drupal_set_content() calls.
  $output .= drupal_get_content($region);

  return $output;
}

// Override theme settings form to collapse logo image stuff and shortcut icon stuff. Adapted from AdaptiveTheme!
function sooper_tundra_system_settings_form($form) {
  $form['theme_specific']['#title'] = t('SooperThemes Settings');
  $form['theme_specific']['#weight'] = 0;
  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;

  return drupal_render($form);
}

// Override color module form to change color semantics and if necessary remove the preview
function sooper_tundra_color_scheme_form($form) {
  $form['palette']['text']['#suffix'] = '<p class="bluebutton" id="random-color" style="clear:both;margin:1em 0;">Set Random Color</p>';
  $form['palette']['base']['#title'] = 'Primary Color';
  $form['palette']['link']['#title'] = 'Secondary Color';
  $form['palette']['link']['#suffix'] = '<div class="hide">';
  $form['palette']['bottom']['#suffix'] = '</div>';

  // Include stylesheet
  $theme = $form['theme']['#value'];
  $info = $form['info']['#value'];
  drupal_add_css($theme_path . $info['preview_css']);

  // Wrapper
  $output .= '<div class="color-form clear-block">';

  // Color schemes
  $output .= drupal_render($form['scheme']);

  // Palette
  $output .= '<div id="palette" class="clear-block">';
  foreach (element_children($form['palette']) as $name) {
    $output .= drupal_render($form['palette'][$name]);
  }
  $output .= '</div>';

  // Preview
  $output .= drupal_render($form);
  $output .= '<div class="hide">'; // It's not possible to just remove the preview output, will cause javascript errors and will break form completely in ie
  $output .= '<h2>'. t('Preview') .'</h2>';
  $output .= '<div id="preview"><div id="text"><h2>Lorem ipsum dolor</h2><p>Sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud <a href="#">exercitation ullamco</a> laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p></div><div id="img" style="background-image: url('. base_path() . $path . $info['preview_image'] .')" alt=""></div></div>';
  $output .= '</div>';

  // Close wrapper
  $output .= '</div>';

  return $output;
}
