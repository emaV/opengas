<div class="<?php print $comment_classes; ?>">
  <div class="comment-meta">

    <?php if ($unpublished): ?>
      <p class="unpublished"><?php print t('Unpublished'); ?></p>
    <?php endif; ?>

    <?php if ($picture) print $picture; ?>

    <p class="submitted">
      <?php print $submitted; ?>
    </p>

    <?php if ($links): ?>
      <div class="links">
        <?php print $links; ?>
      </div>
    <?php endif; ?>
  </div><!-- end .meta -->

  <div class="comment-data">
    <?php if ($title): ?>
      <h3 class="title comment-title"><?php print $title; if ($new): ?> <span class="new"><?php print $new; ?></span><?php endif; ?></h3>
    <?php endif; ?>
    <?php print $content; ?>
    <?php if ($signature): ?>
      <div class="signature">
        <?php print $signature ?>
      </div>
    <?php endif; ?>
  </div>


</div><!-- end .comment -->