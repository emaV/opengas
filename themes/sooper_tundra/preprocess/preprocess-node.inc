<?php
// Customized byline
if ($vars['submitted']) {
  $vars['submitted'] = '<p class="author">'. t('by ') . theme('username', $vars['node']) .'</p> <p class="date">'. format_date($vars['created'], 'custom', "F jS, Y") .'</p>';
}

// Comments Header
if ((!$vars['teaser']) && ($vars['node']->comment_count > 0) && user_access('access comments')) {
  $vars['comment_header'] = '<h3 class="commentheader">'. t('Comments:') . ' <span class="comment-count">('. $vars['node']->comment_count .')</span></h3>';
}

// Taxonomy
if (module_exists('taxonomy')) {
  $vocabularies = taxonomy_get_vocabularies($vars['node']->type);
  $output = '';
  $vocab_delimiter = '';
  foreach ($vocabularies as $vocabulary) {
      $terms = taxonomy_node_get_terms_by_vocabulary($vars['node'], $vocabulary->vid);
      if ($terms) {
        $output .= '<li class="vocab vocab-'. $vocabulary->vid .'"><span class="vocab-name">'. $vocabulary->name .':</span> <ul class="vocab-list inline">';
        $links = array();
        foreach ($terms as $term) {
          $links[] = '<li class="vocab-term">'. l($term->name, taxonomy_term_path($term), array('rel' => 'tag', 'title' => strip_tags($term->description))) .'</li>';
        }
        $output .= implode(", ", $links);
        $output .= '</ul></li>';
      }
  }
  if ($output != '') {
    $output = '<ul class="taxonomy">'. $output .'</ul>';
  }
  $vars['terms'] = $output;
}
else {
  $vars['terms'] = '';
}

// Zen node classes
$node_classes = array();
if ($vars['sticky']) {
  $node_classes[] = 'sticky';
}
if (!$vars['node']->status) {
  $node_classes[] = 'node-unpublished';
  $vars['unpublished'] = TRUE;
}
else {
  $vars['unpublished'] = FALSE;
}
if ($vars['node']->uid && $vars['node']->uid == $user->uid) {
  // Node is authored by current user
  $node_classes[] = 'node-mine';
}
// Add a class to allow styling based on the node author.
$node_classes[] = 'author-' . theme('zen_id_safe', $vars['node']->name);
if ($vars['teaser']) {
  // Node is displayed as teaser
  $node_classes[] = 'node-teaser';
} else {
  $node_classes[] = 'node-full';
}
// Class for node type: "node-type-page", "node-type-story", "node-type-my-custom-type", etc.
$node_classes[] = 'node-type-'. $vars['node']->type;
// Class for node id
$node_classes[] = 'node-'. $vars['node']->nid;
$vars['node_classes'] = implode(' ', $node_classes); // Concatenate with spaces