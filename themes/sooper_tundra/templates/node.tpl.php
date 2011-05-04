  <div class="node grid-unit <?php print $node_classes ?>">
    <div class="node-meta">
    
    <?php if ($picture):
      print $picture;
    endif; ?>
    
    <?php if ($submitted):
      print $submitted;
    endif; ?>

    <?php if ($links): ?><?php print $links?><?php endif; ?>
    
    <?php if ($terms):
      print $terms;
    endif; ?>
    </div>
    
    <div class="node-data">

      <?php if ($page == 0): ?>
      <h1 class="title nodetitle"><a href="<?php print $node_url?>"><?php print $title?></a></h1>
      <?php endif; ?>
      
      <div class="content"><?php print $content?></div>
    
    </div>
  </div><!-- end .node -->

  <?php if ($comment_header):
    print $comment_header;
  endif; ?>