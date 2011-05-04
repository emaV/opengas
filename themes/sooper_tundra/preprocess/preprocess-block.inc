<?php

$block = $vars['block'];
// Special classes for blocks
$block_classes = array('block');
$block_classes[] = 'block-'. $block->module;
$block_classes[] = 'region-'. $vars['block_zebra'];
$block_classes[] = $vars['zebra'];
$block_classes[] = 'region-count-'. $vars['block_id'];
$block_classes[] = 'count-'. $vars['id'];
$block_classes[] = $block->first_last;
$vars['block_classes'] = implode(' ', $block_classes);

// ADD Skinr styles
if ($vars['skinr']) {
  $vars['block_classes'] .= ' '. $vars['skinr'];
  // Add cornerstones to rounded blocks
  if (strstr($vars['skinr'], 'rounded') !== FALSE) {
    $vars['cornerstones'] = '<div class="cornerstone b-cs1"></div><div class="cornerstone b-cs2"></div><div class="cornerstone b-cs3"></div><div class="cornerstone b-cs4"></div>';
  }
}

// Edit Links from Zen project:
$vars['edit_links'] = '';
if (theme_get_setting('block_edit') && user_access('administer blocks')) {
$vars['block_classes'] .= ' with-block-editing';
// Display 'edit block' for custom blocks.
if ($block->module == 'block') {
  $edit_links[] = l('<span>' . t('edit block') . '</span>', 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
    array(
      'attributes' => array(
        'title' => t('edit the content of this block'),
        'class' => 'block-edit',
      ),
      'query' => drupal_get_destination(),
      'html' => TRUE,
    )
  );
}
// Display 'configure' for other blocks.
else {
  $edit_links[] = l('<span>' . t('configure') . '</span>', 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
    array(
      'attributes' => array(
        'title' => t('configure this block'),
        'class' => 'block-config',
      ),
      'query' => drupal_get_destination(),
      'html' => TRUE,
    )
  );
}

// Display 'edit menu' for Menu blocks.
if (($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1)) && user_access('administer menu')) {
  $menu_name = ($block->module == 'user') ? 'navigation' : $block->delta;
  $edit_links[] = l('<span>' . t('edit menu') . '</span>', 'admin/build/menu-customize/' . $menu_name,
    array(
      'attributes' => array(
        'title' => t('edit the menu that defines this block'),
        'class' => 'block-edit-menu',
      ),
      'query' => drupal_get_destination(),
      'html' => TRUE,
    )
  );
}
// Display 'edit menu' for Menu block blocks.
elseif ($block->module == 'menu_block' && user_access('administer menu')) {
  $menu_name = variable_get('menu_block_' . $block->delta . '_menu_name', 'navigation');
  $edit_links[] = l('<span>' . t('edit menu') . '</span>', 'admin/build/menu-customize/' . $menu_name,
    array(
      'attributes' => array(
        'title' => t('edit the menu that defines this block'),
        'class' => 'block-edit-menu',
      ),
      'query' => drupal_get_destination(),
      'html' => TRUE,
    )
  );
}
  $vars['edit_links_array'] = $edit_links;
  $vars['edit_links'] = '<div class="edit">'. implode(' ', $edit_links) .'</div>';
}