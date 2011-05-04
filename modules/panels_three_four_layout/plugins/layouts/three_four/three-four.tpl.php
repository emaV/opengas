<?php
// $Id: three-four.tpl.php,v 1.1 2010/08/23 22:07:12 bdziewierz Exp $
?>

<div class="panel-display three-four clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  
<?php if($content['top_left'] || $content['top_middle'] || $content['top_right']): ?>

  <div class="panel-row panel-three row-top">
    <?php if($content['top_left']): ?>
      <div class="panel-top-left panel-left slot<?php if(!$content['top_middle'] && !$content['top_right']): ?> slot-x3<?php endif; ?><?php if(!$content['top_middle']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['top_left']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['top_middle']): ?>
      <div class="panel-top-middle panel-middle <?php if(!$content['top_left']): ?>skip-left<?php endif; ?> slot<?php if(!$content['top_right']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['top_middle']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['top_right']): ?>
      <div class="panel-top-right panel-right <?php if(!$content['top_left'] && !$content['top_middle']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['top_right']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['middle_left'] || $content['middle_middle'] || $content['middle_right']): ?>

  <div class="panel-row panel-three row-middle">
    <?php if($content['middle_left']): ?>
      <div class="panel-middle-left panel-left slot<?php if(!$content['middle_middle'] && !$content['middle_right']): ?> slot-x3<?php endif; ?><?php if(!$content['middle_middle']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['middle_left']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['middle_middle']): ?>
      <div class="panel-middle-middle panel-middle <?php if(!$content['middle_left']): ?>skip-left<?php endif; ?> slot<?php if(!$content['middle_right']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['middle_middle']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['middle_right']): ?>
      <div class="panel-middle-right panel-right <?php if(!$content['middle_left'] && !$content['middle_middle']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['middle_right']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['bottom_left'] || $content['bottom_middle'] || $content['bottom_right']): ?>

  <div class="panel-row panel-three row-bottom">
    <?php if($content['bottom_left']): ?>
      <div class="panel-bottom-left panel-left slot<?php if(!$content['bottom_middle'] && !$content['bottom_right']): ?> slot-x3<?php endif; ?><?php if(!$content['bottom_middle']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['bottom_left']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['bottom_middle']): ?>
      <div class="panel-bottom-middle panel-middle <?php if(!$content['bottom_left']): ?>skip-left<?php endif; ?> slot<?php if(!$content['bottom_right']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['bottom_middle']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['bottom_right']): ?>
      <div class="panel-bottom-right panel-right <?php if(!$content['bottom_left'] && !$content['bottom_middle']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['bottom_right']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['first_first'] || $content['first_second'] || $content['first_third'] || $content['first_fourth']): ?>

  <div class="panel-row panel-four row-first">
    <?php if($content['first_first']): ?>
      <div class="panel-first-first panel-first slot<?php if(!$content['first_second'] && !$content['first_third'] && !$content['first_fourth']): ?> slot-x4<?php endif; ?><?php if(!$content['first_second'] && !$content['first_third']): ?> slot-x3<?php endif; ?><?php if(!$content['first_second']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['first_first']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['first_second']): ?>
      <div class="panel-first-second panel-second <?php if(!$content['first_first']): ?>skip-left<?php endif; ?> slot<?php if(!$content['first_third'] && !$content['first_fourth']): ?> slot-x3<?php endif; ?><?php if(!$content['first_third']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['first_second']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['first_third']): ?>
      <div class="panel-first-third panel-third <?php if(!$content['first_first'] && !$content['first_second']): ?>skip-left<?php endif; ?> slot<?php if(!$content['first_fourth']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['first_third']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['first_fourth']): ?>
      <div class="panel-first-fourth panel-fourth <?php if(!$content['first_first'] && !$content['first_second'] && !$content['first_third']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['first_fourth']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['second_first'] || $content['second_second'] || $content['second_third'] || $content['second_fourth']): ?>

  <div class="panel-row panel-four row-second">
    <?php if($content['second_first']): ?>
      <div class="panel-second-first panel-first slot<?php if(!$content['second_second'] && !$content['second_third'] && !$content['second_fourth']): ?> slot-x4<?php endif; ?><?php if(!$content['second_second'] && !$content['second_third']): ?> slot-x3<?php endif; ?><?php if(!$content['second_second']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['second_first']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['second_second']): ?>
      <div class="panel-second-second panel-second <?php if(!$content['second_first']): ?>skip-left<?php endif; ?> slot<?php if(!$content['second_third'] && !$content['second_fourth']): ?> slot-x3<?php endif; ?><?php if(!$content['second_third']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['second_second']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['second_third']): ?>
      <div class="panel-second-third panel-third <?php if(!$content['second_first'] && !$content['second_second']): ?>skip-left<?php endif; ?> slot<?php if(!$content['second_fourth']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['second_third']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['second_fourth']): ?>
      <div class="panel-second-fourth panel-fourth <?php if(!$content['second_first'] && !$content['second_second'] && !$content['second_third']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['second_fourth']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['third_first'] || $content['third_second'] || $content['third_third'] || $content['third_fourth']): ?>

  <div class="panel-row panel-four row-third">
    <?php if($content['third_first']): ?>
      <div class="panel-third-first panel-first slot<?php if(!$content['third_second'] && !$content['third_third'] && !$content['third_fourth']): ?> slot-x4<?php endif; ?><?php if(!$content['third_second'] && !$content['third_third']): ?> slot-x3<?php endif; ?><?php if(!$content['third_second']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['third_first']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['third_second']): ?>
      <div class="panel-third-second panel-second <?php if(!$content['third_first']): ?>skip-left<?php endif; ?> slot<?php if(!$content['third_third'] && !$content['third_fourth']): ?> slot-x3<?php endif; ?><?php if(!$content['third_third']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['third_second']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['third_third']): ?>
      <div class="panel-third-third panel-third <?php if(!$content['third_first'] && !$content['third_second']): ?>skip-left<?php endif; ?> slot<?php if(!$content['third_fourth']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['third_third']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['third_fourth']): ?>
      <div class="panel-third-fourth panel-fourth <?php if(!$content['third_first'] && !$content['third_second'] && !$content['third_third']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['third_fourth']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

<?php if($content['fourth_first'] || $content['fourth_second'] || $content['fourth_third'] || $content['fourth_fourth']): ?>

  <div class="panel-row panel-four row-fourth">
    <?php if($content['fourth_first']): ?>
      <div class="panel-fourth-first panel-first slot<?php if(!$content['fourth_second'] && !$content['fourth_third'] && !$content['fourth_fourth']): ?> slot-x4<?php endif; ?><?php if(!$content['fourth_second'] && !$content['fourth_third']): ?> slot-x3<?php endif; ?><?php if(!$content['fourth_second']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['fourth_first']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['fourth_second']): ?>
      <div class="panel-fourth-second panel-second <?php if(!$content['fourth_first']): ?>skip-left<?php endif; ?> slot<?php if(!$content['fourth_third'] && !$content['fourth_fourth']): ?> slot-x3<?php endif; ?><?php if(!$content['fourth_third']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['fourth_second']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['fourth_third']): ?>
      <div class="panel-fourth-third panel-third <?php if(!$content['fourth_first'] && !$content['fourth_second']): ?>skip-left<?php endif; ?> slot<?php if(!$content['fourth_fourth']): ?> slot-x2<?php endif; ?>"><div class="inside">
        <?php print $content['fourth_third']; ?>
      </div></div>
    <?php endif; ?>

    <?php if($content['fourth_fourth']): ?>
      <div class="panel-fourth-fourth panel-fourth <?php if(!$content['fourth_first'] && !$content['fourth_second'] && !$content['fourth_third']): ?>skip-left<?php endif; ?> slot"><div class="inside">
        <?php print $content['fourth_fourth']; ?>
      </div></div>
    <?php endif; ?>
  </div>

<?php endif; ?>

</div> 