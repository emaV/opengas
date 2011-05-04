<?php
// $Id: block.tpl.php,v 1.1 2009/03/30 00:23:05 itemplater Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="clear-block block block-<?php print $block->module ?>">

<?php if (!empty($block->subject)): ?>
  <h3><?php print $block->subject ?></h3>
<?php endif;?>

  <div class="content"><?php print $block->content ?></div>
</div>
