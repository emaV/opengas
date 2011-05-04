<?php

  $defaults = array(
	// Other Options
    'iepngfix'                          => 1,
    'block_edit'                        => 1,
    'force_eq_heights'                  => 1,
    'commentheader'                     => 'Comments:',
    'timestamp'                         => 0,
  );

  // Merge with Defaults from the features
  
  // Load SOOPER Features
  foreach (file_scan_directory($theme_path .'features', 'defaults.inc', array('.', '..', 'CVS')) as $file) {
    include($file->filename);
    $defaults = array_merge($defaults, $sooperdefaults);    
  }

  // Merge the saved variables and their default values
  if (empty($saved_settings)) { $saved_settings = array(); }
  $settings = array_merge($defaults,  $saved_settings);