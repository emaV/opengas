<?php
/**
 * Provides Font Stack values for theme settings which are written to custom.css
 * @see font_list()
 * @param $attributes
 * @return string
 */
function font_stack($font) {
  if ($font) {
	$fonts = array(
	  'helvetica' => 'Arial, Helvetica, "Nimbus Sans L", "Liberation Sans", "FreeSans", sans-serif',
	  'myriad' => '"myriad pro",myriad,calibri,arial,tahoma,verdana,sans-serif',
	  'verdana' => 'Verdana, "Bitstream Vera Sans", Arial, sans-serif',
	  'lucida' => '"Lucida Sans Unicode", "Lucida Sans", "Lucida Grande", "DejaVu Sans", Arial, sans-serif',
	  'geneva' => '"Geneva", "Bitstream Vera Serif", "Tahoma", sans-serif',
	  'tahoma' => 'Tahoma, Geneva, "DejaVu Sans Condensed", sans-serif',
	  'trebuchet' => '"Trebuchet MS",Trebuchet,Tahoma,arial,verdana,sans',
	  'century' => '"Century Gothic", "URW Gothic L", Helvetica, Arial, sans-serif',
	  'georgia' => 'Georgia, "Bitstream Vera Serif", serif',
	  'palatino' => '"Palatino Linotype", "URW Palladio L", "Book Antiqua", "Palatino", serif',
	  'times' => '"Free Serif", "Times New Roman", Times, serif',
	);

	foreach ($fonts as $key => $value) {
	  if ($font == $key) {
		$output = $value;
	  }
	}
  }
  return $output;
}

if (theme_get_setting('body_font_face')):
  $font_set = font_stack(theme_get_setting('body_font_face'));
  $CSS .= "html body { font-family: {$font_set}; }\n";
endif;

if (theme_get_setting('headings_font_face')):
  $font_set = font_stack(theme_get_setting('headings_font_face'));
  $CSS .= "h1, h2, h3, h4, h5, h6, legend, p.mission, p.slogan, .views-field-title { font-family: {$font_set}; }\n";
endif;