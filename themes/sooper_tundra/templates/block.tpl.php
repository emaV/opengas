  <div class="<?php print $block_classes; ?>" id="block-<?php print $block->module; ?>-<?php print $block->delta; ?>"><div class="block-inner grid-unit">
	<?php if ($block->subject): ?>
		<h2 class="title blocktitle"><?php print $block->subject; ?></h2>
	<?php endif; ?>
    <div class="content">
      <?php print $block->content; ?>
      <?php if ($edit_links): ?>
        <?php print $edit_links; ?>
      <?php endif; ?>
    </div>
 </div>
 <?php if ($cornerstones) { print $cornerstones; } ?>
 </div><!-- end .inner --><!-- end .block -->
