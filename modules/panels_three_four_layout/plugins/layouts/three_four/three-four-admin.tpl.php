<?php
// $Id: three-four-admin.tpl.php,v 1.1 2010/08/23 22:07:12 bdziewierz Exp $
?>

<div class="panel-display three-four clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

<?php if($content['top_left'] || $content['top_middle'] || $content['top_right']): ?>

  <div class="panel-row panel-three row-top">
    <div class="panel-top-left slot"><div class="inside">
      <?php print $content['top_left']; ?>
    </div></div>

    <div class="panel-top-middle slot"><div class="inside">
      <?php print $content['top_middle']; ?>
    </div></div>

    <div class="panel-top-right slot"><div class="inside">
      <?php print $content['top_right']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['middle_left'] || $content['middle_middle'] || $content['middle_right']): ?>

  <div class="panel-row panel-three row-middle">
    <div class="panel-middle-left slot"><div class="inside">
      <?php print $content['middle_left']; ?>
    </div></div>

    <div class="panel-middle-middle slot"><div class="inside">
      <?php print $content['middle_middle']; ?>
    </div></div>

    <div class="panel-middle-right slot"><div class="inside">
      <?php print $content['middle_right']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['bottom_left'] || $content['bottom_middle'] || $content['bottom_right']): ?>

  <div class="panel-row panel-three row-bottom">
    <div class="panel-bottom-left slot"><div class="inside">
      <?php print $content['bottom_left']; ?>
    </div></div>

    <div class="panel-bottom-middle slot"><div class="inside">
      <?php print $content['bottom_middle']; ?>
    </div></div>

    <div class="panel-bottom-right slot"><div class="inside">
      <?php print $content['bottom_right']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['first_first'] || $content['first_second'] || $content['first_third'] || $content['first_fourth']): ?>

  <div class="panel-row panel-four row-first">
    <div class="panel-first-first slot"><div class="inside">
      <?php print $content['first_first']; ?>
    </div></div>

    <div class="panel-first-second slot"><div class="inside">
      <?php print $content['first_second']; ?>
    </div></div>

    <div class="panel-first-third slot"><div class="inside">
      <?php print $content['first_third']; ?>
    </div></div>

    <div class="panel-first-fourth slot"><div class="inside">
      <?php print $content['first_fourth']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['second_first'] || $content['second_second'] || $content['second_third'] || $content['second_fourth']): ?>

  <div class="panel-row panel-four row-second">
    <div class="panel-second-first slot"><div class="inside">
      <?php print $content['second_first']; ?>
    </div></div>

    <div class="panel-second-second slot"><div class="inside">
      <?php print $content['second_second']; ?>
    </div></div>

    <div class="panel-second-third slot"><div class="inside">
      <?php print $content['second_third']; ?>
    </div></div>

    <div class="panel-second-fourth slot"><div class="inside">
      <?php print $content['second_fourth']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['third_first'] || $content['third_second'] || $content['third_third'] || $content['third_fourth']): ?>

  <div class="panel-row panel-four row-third">
    <div class="panel-third-first slot"><div class="inside">
      <?php print $content['third_first']; ?>
    </div></div>

    <div class="panel-third-second slot"><div class="inside">
      <?php print $content['third_second']; ?>
    </div></div>

    <div class="panel-third-third slot"><div class="inside">
      <?php print $content['third_third']; ?>
    </div></div>

    <div class="panel-third-fourth slot"><div class="inside">
      <?php print $content['third_fourth']; ?>
    </div></div>
  </div>

<?php endif; ?>

<?php if($content['fourth_first'] || $content['fourth_second'] || $content['fourth_third'] || $content['fourth_fourth']): ?>

  <div class="panel-row panel-four row-fourth">
    <div class="panel-fourth-first slot"><div class="inside">
      <?php print $content['fourth_first']; ?>
    </div></div>

    <div class="panel-fourth-second slot"><div class="inside">
      <?php print $content['fourth_second']; ?>
    </div></div>

    <div class="panel-fourth-third slot"><div class="inside">
      <?php print $content['fourth_third']; ?>
    </div></div>

    <div class="panel-fourth-fourth slot"><div class="inside">
      <?php print $content['fourth_fourth']; ?>
    </div></div>
  </div>

<?php endif; ?>

</div> 