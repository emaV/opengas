<?php

// Initialize theme settings
if (is_null(theme_get_setting('fixedfluid'))) {  // <-- if settings have never ben set

  // get theme key
  global $theme_key;

  // include theme settings defaults
  if(is_file($theme_path . 'theme-settings-defaults.php')) {
    include('theme-settings-defaults.php');
  }

  // Don't save the toggle_node_info_ variables
  if (module_exists('node')) {
    foreach (node_get_types() as $type => $name) {
      unset($settings['toggle_node_info_'. $type]);
    }
  }
  // Save default theme settings
  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge($defaults, theme_get_settings())
  );
  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

// Load the custom theme options CSS file
if (theme_get_setting('timestamp') > 0) {
  GLOBAL $theme;
  drupal_add_css(file_directory_path().'/cto-'.$theme.'.css', 'theme', 'all');
}

// Load jQuery equal heights plugin
if (theme_get_setting('force_eq_heights')) {
  if(is_file($theme_path .'scripts/misc/jQuery.equalHeights.js')) {
    drupal_add_js($theme_path .'scripts/misc/jQuery.equalHeights.js');
  }
}

// Load Grid debug stylesheet
if ((theme_get_setting('grid_debug_enable')) && (is_file($theme_path . 'css/debug.css'))) {
  drupal_add_css($theme_path . 'css/debug.css', 'theme', 'all');
}

// Load SOOPER Features
foreach (file_scan_directory($theme_path .'features', 'controller.inc', array('.', '..', 'CVS')) as $file) {
  include($file->filename);
}

// Create custom theme options CSS file
if (user_access('access administration pages') && (arg(2) == 'themes') && (arg(3) == 'settings') && (arg(4) != FALSE)) {
  GLOBAL $theme;

  if (theme_get_setting('timestamp')) { // If theme settings are in fact "customized", this only returns FALSE if the theme settings never have been saved
    $newTimestamp = "/*".theme_get_setting('timestamp')."*/\n";
    $ctoCssFile = file_directory_path().'/cto-'.$theme.'.css';
    if (is_file($ctoCssFile)) {
      $fh = fopen($ctoCssFile, 'r');
      $oldTimestamp = fgets($fh,1024); // extract timestamp from first line of css file. Note: the timestap is in a css file so it is wrapped in /* css comment */ characters.
      fclose($fh);
    }

    if (($oldTimestamp) != ($newTimestamp)) { // if custom theme options have been saved since last time css file was written
      /* Construct CSS file: */

      $CSS = '';

      // Load SOOPER Features
      foreach (file_scan_directory($theme_path .'features', 'css.inc', array('.', '..', 'CVS')) as $file) {
        include($file->filename);
      }

  /**
  * Color module injection
  * Writes the colors to the stylesheet, using the color_get_palette('themename') function, and assisting color-calibration functions if applicable
  * (color module's own color shifting in CSS works unreliably and inaccurately)
  */
      if (module_exists(color)){
      // Override colors in style.css with color palette from theme settings. All selectors have increased specificity so that they will override other stylesheets and not be overriden
        $ctopalette = color_get_palette($theme);
        $CSS .= "html body, body h1, body h2, body h3, body h4, body h5, body h6, body h1 a, body h2 a, body h3 a, body h4 a, body h5 a, body h6 a, body .item-list li a, body #toolbar input.form-text,body #content .node .node-data h1.nodetitle a { color:".$ctopalette['text'].";}\n";
        $CSS .= "body .poll .bar, body #content ul.secondary li a, body #container ul.primary li a:hover, body #container ul.primary li a:focus, body ul.primary li a, body div.block div.edit a, body #toolbar, body body .skinr-color-3 .block-inner { background-color:".$ctopalette['text'].";}\n";
        $CSS .= "body a, body #content ul.secondary li a,body h1#sitename a, body #main #content .nodetitle a:hover,body #main #content .nodetitle a:focus, body .item-list li, body span.form-required, body th a:link, body th a:visited,body ul.quicktabs_tabs.quicktabs-style-tundra li a { color:".$ctopalette['base'].";}\n";
        $CSS .= "body ul.secondary-links li a, body #cycle-pager a,body #content ul.secondary li a.active, body input.form-submit,body #navbar, body #navbar ul ul, body ul.primary li.active a,body .poll .bar .foreground,body .skinr-color,body ul.quicktabs_tabs.quicktabs-style-tundra li.active a { background-color:".$ctopalette['base'].";}\n";
        $CSS .= "body .slideshow,body #cycle-pager,body input.form-text:focus, body input.form-upload:focus, body input.form-file:focus, body textarea:focus { border-color:".$ctopalette['base'].";}\n";
        $CSS .= "body .comment .comment-meta, body .comment .comment-meta a, body .node-full .node-meta p.date, body .node-teaser .node-meta div.links a, body blockquote,body #content .node-teaser  .node-meta { color:".$ctopalette['link'].";}\n";
        $CSS .= "body #footer,body .comment .comment-meta, body blockquote,body #content .node-teaser  .node-meta { border-color:".$ctopalette['link'].";}\n";
        $CSS .= "body .skinr-color-2 .block-inner { background-color:".$ctopalette['link'].";}\n";
      }

      $fh = fopen($ctoCssFile, 'w');
      if ($fh) {
        fwrite($fh, $newTimestamp); // write new timestamp to file
        fwrite($fh, $CSS); // write css to file
      } else {
        drupal_set_message(t('Cannot write theme-settings file, please check your file system. (Visit status report page)'), 'error');
      }
      fclose($fh);
      // If the CSS & JS aggregation performance options are enabled we need to clear the caches
      drupal_clear_css_cache();
      drupal_clear_js_cache();
    }
  } else {
  $msgthemeset = 'Hello administrator! It looks like you\'ve never set your theme settings before, check out out the <a href="'. base_path() .'admin/build/themes/settings/'. $theme .'">theme settings page</a> to learn about the options.';
  drupal_set_message($msgthemeset, 'message');
  }
}
