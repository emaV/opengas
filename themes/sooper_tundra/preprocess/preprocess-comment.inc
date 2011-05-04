<?php
// Customized byline
if ($vars['submitted']) {
  $vars['submitted'] = '<p class="author">'. t('by ') . theme('username', $vars['comment']) .'</p> <p class="date">'. format_date($vars['comment']->timestamp, 'custom', "F jS, Y") .'</p>';
}


// Special classes for comments
$comment_classes = array('comment');
$comment_classes[] = 'clearfix';
if ($vars['comment']->new) {
  $comment_classes[] = 'comment-new';
}
$comment_classes[] = $vars['status'];
$comment_classes[] = $vars['zebra'];
if ($vars['id'] == 1) {
  $comment_classes[] = 'first';
}
if ($vars['id'] == $vars['node']->comment_count) {
  $comment_classes[] = 'last';
}
// Add a class to show if a commenter is replying to a node that was authored 
// by them.
if ($vars['comment']->uid == $vars['node']->uid) {
  $comment_classes[] = 'node-author';
}

if ($vars['comment']->uid > 0) {
  $comment_classes[] = 'registered-user';
  $comment_classes[]  = 'author-' . theme('zen_id_safe', ($vars['comment']->registered_name));
}
else {
  $comment_classes[]  = 'author-anonymous';
}

$vars['comment_classes'] = implode(' ', $comment_classes);