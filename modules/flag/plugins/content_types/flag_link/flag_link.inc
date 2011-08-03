<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Flag link'),
  'description' => t('Add a flag link of a certain flag type (user, content or comment).'),
  // We don't know the type of the flag yet, so our context as optional, and we
  // will check it before rending.
  'required context' => array(
    new ctools_context_optional(t('User'), 'user'),
    new ctools_context_optional(t('Node'), 'node'),
    new ctools_context_optional(t('Comment'), 'comment'),
  ),
  'category' => t('Activity'),
  'defaults' => array('flag_name' => ''),
);

/**
 * Render callback.
 */
function flag_flag_link_content_type_render($subtype, $conf, $args, $context) {
  $flag = flag_get_flag($conf['flag_name']);

  if (!$flag) {
    return;
  }

  // Check if we have the context for this flag type.
  list($user_context, $node_context, $comment_context) = $context;
  $current_context = ${$flag->content_type . '_context'};

  if (empty($current_context->data)) {
    return;
  }

  // Get the ID of the entity.
  if ($flag->content_type == 'user') {
    $key = 'uid';
  }
  elseif ($flag->content_type == 'node') {
    $key = 'nid';
  }
  elseif ($flag->content_type == 'comment') {
    $key = 'cid';
  }

  $id = $current_context->data->{$key};
  $link = flag_create_link($flag->name, $id);

  if (!$link) {
    return;
  }

  $block = new stdClass();
  $block->module = 'flag';
  $block->title = t('Flag link');
  $block->delta = $flag->name;

  $block->content = $link;
  return $block;
}

/**
 * Form callback.
 */
function flag_flag_link_content_type_edit_form(&$form, &$form_state) {
  $conf = $form_state['conf'];
  $options = array();

  foreach (flag_get_flags() as $flag) {
    $options[$flag->name] = $flag->title;
  }

  $form['flag_name'] = array(
    '#type' => 'select',
    '#title' => t('Flag name'),
    '#default_value' => $conf['flag_name'],
    '#options' => $options,
    '#description' => t('Select a flag.'),
    '#required' => TRUE,
    '#disabled' => !$options,
  );

}

/**
 * Form submit.
 */
function flag_flag_link_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a flag link.
 */
function flag_flag_link_content_type_admin_title($subtype, $conf) {
  if ($flag = flag_get_flag($conf['flag_name'])) {
    return t('Flag link of @flag', array('@flag' => $flag->title));
  }
}
