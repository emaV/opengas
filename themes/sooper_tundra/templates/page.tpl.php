<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">
<head>
  <title><?php print $head_title ?></title>

  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>

  <style type="text/css">
  <?php
  /*** Widths of blocks in dynamic regions ***/
  print $blockwidths;
  /*** Sidebars And Middle column widths ***/
  print $structure_widths;
  ?>
  </style>

  <?php if ($lte_ie6): ?>
  <!--[if lte IE 6]>
      <?php print $lte_ie6 ?>
  <![endif]-->
  <?php endif; ?>

  <?php if ($lte_ie7): ?>
  <!--[if lte IE 7]>
      <?php print $lte_ie7 ?>
  <![endif]-->
  <?php endif; ?>

  <?php if ($lte_ie8): ?>
  <!--[if lte IE 8]>
      <?php print $lte_ie8 ?>
  <![endif]-->
  <?php endif; ?>

</head>

<body class="<?php print $body_classes ?>">

<p id="skipcontent"><a href="#content"><?php print t('Skip to content'); ?></a></p>

<div id="container" class="clearifx sooper-mast">

  <div id="header"><div class="inner clearfix">
    <?php if ($logo): ?>
      <a href="<?php print url() ?>" title="<?php t('Home') ?>"><img src="<?php print($logo) ?>" alt="Logo" class="logo"/></a>
    <?php endif; ?>

    <?php if ($site_name): ?>
    <h1 id="sitename"><a href="<?php print url() ?>" title="<?php t('Home') ?>"><?php print($site_name) ?></a></h1>
    <?php endif;?>

    <?php if ($site_slogan): ?>
    <p class="slogan"><?php print $site_slogan ?></p>
    <?php endif;?>

    <?php if ($secondary_links): ?>
      <?php print $secondary_menu ?>
    <?php endif; ?>
  </div></div><!-- end .inner --><!-- end #header -->

  <div id="main">

  <?php if ($primary_links): ?>
  <div id="navbar" class="lone-grid-unit">
      <?php print $primary_menu ?>
  </div><!-- end #navbar -->
  <?php endif; ?>

  <?php if ($preblocks): ?>
  <div class="sooperblocks clearfix preblocks precount<?php print $precount ?>">
  <?php print $preblocks ?>
  </div><!-- end .preblocks -->
  <?php endif; ?>

  <div class="wrapcolumns">
  <?php if ($sidebar_first): ?>
  <div class="sidebar side-first"><div class="side-inner">
  <?php print $sidebar_first ?>
  </div></div><!-- end .inner --><!-- end sidebar first -->
  <?php endif; ?>

  <div id="content"><div class="content-inner grid-unit">

    <?php if ($slideshow): ?>
      <div class="slideshow">
        <?php print $slideshow ?>
        <div id="cycle-pager"></div>
      </div><!-- end .slideshow -->
    <?php endif; ?>
      
    <?php if ($breadcrumb) print $breadcrumb ?>

    <?php if ($tabs) print $tabs ?>

      <a name="content"></a>
      <?php if ($title): ?>
        <h1 class="content title" id="content-title"><?php print $title ?></h1>
      <?php endif; ?>

      <?php if ($help): ?>
        <?php print $help ?>
      <?php endif; ?>

      <?php if ($messages): ?>
        <div id="content-message"><?php print $messages ?></div>
      <?php endif; ?>

      <?php if ($content_top): ?>
        <div class="content-top"><?php print $content_top ?></div>
      <?php endif; ?>

      <?php print $content ?>

      <?php if ($content_bottom): ?>
        <div class="content-bottom"><?php print $content_bottom ?></div>
      <?php endif; ?>

      <?php print $feed_icons; ?>

  </div></div><!-- end .inner --><!-- end #content -->

  <?php if ($sidebar_second): ?>
  <div class="sidebar side-second"><div class="inner">
  <?php print $sidebar_second ?>
  </div></div><!-- end .inner --><!-- end sidebar second -->
  <?php endif; ?>
  </div><!-- end .wrapcolumns -->

  <?php if ($postblocks): ?>
  <div class="sooperblocks clearfix postblocks postcount<?php print $postcount ?>">
  <?php print $postblocks ?>
  </div><!-- end .postblocks -->
  <?php endif; ?>

  </div><!-- end #main -->

  <div id="footer" class="clearfix">
    <?php if ($footer): ?>
      <?php print $footer ?>
    <?php endif; ?>
    <?php if ($footer_message): ?>
    <p id="footermessage"><?php print $footer_message ?></p>
    <?php endif; ?>
	
	<?php if ($sooper_message): // Since this is open source software you are allowed to remove this link to SooperThemes.com, but it's helpful to my website so if you could leave it, it's much appreciated! - Jurriaan (peach) ?>
	<?php print $sooper_message ?>
    <?php endif; ?>
  </div><!-- end #footer -->

</div><!-- end #container -->

<?php if ($toolbar): ?>
<div id="toolbar">
<?php print $toolbar ?>
</div><!-- end .toolbar -->
<?php endif; ?>

<?php print $closure ?>

</body>
</html>
