<?php
// $Id: page.tpl.php,v 1.1 2009/03/30 00:24:28 itemplater Exp $


?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>

<!--[if IE 6]>
	<style type="text/css">
	#mainMenu ul {margin-left: -40px;}
	</style>
<![endif]-->

<!--[if IE 7]>
	<style type="text/css">
	#searchBox input {height:13px;}
	</style>
<![endif]-->

</head>

<body>

<div id="top">
	<div id="mainMenu"><?php print theme('links', $primary_links, array('class' => 'menu')) ?> </div>
</div>
		
<div class="container">
	
	<div id="logo"><?php echo "<a href=\"$base_path\"><img src=\"".$base_path.path_to_theme()."/images/logo.png\" alt=\"logo\"></a>"; ?> 			</div>                         

	<div id="main">
     	        	         	    	
		<?php if ($idFactaLeft): ?>
		<div id="left"> <?php print $idFactaLeft ?> </div>	
		<?php endif; ?>
		
		<div id="content"> <?php if ($mission): ?><div id="mission"><?php print $mission ?></div><?php endif; ?>
						<?php if ($title): ?><h2 class="contentheading"><?php print $title ?></h2><?php endif; ?>
						<?php if ($tabs): ?><div class="tabs"><?php print $tabs ?></div><?php endif; ?>
						<?php print $help ?>
						<?php print $messages ?>
						<?php print $content  ?>
		 </div>
	
	</div>	
	
	<?php if ($idFactaUser1): ?>
	<div id="bottom"><?php print $idFactaUser1 ?>  </div>	
	<?php endif; ?>
</div> 		

<div id="footer">
	<div id="footerin">
		<div id="searchBox"> <?php print $idFactaSearch ?></div>
		<div id="footermenu"> <?php print $idFactaFootermenu ?> </div>
	</div>
</div> 

<div id="credits"> <?php print $idFactaCredits ?> </div>

<?php print $closure ?>
	    
</body>
</html>