$(document).ready(function(){

  var initPreview;
  var initToucan;
  var themePath = Drupal.settings.theme_path;
  var currentTheme = Drupal.settings.current_theme;
  var themeSettingsPage = Drupal.settings.t_s_page;
  var selectedBackground = '';

  // Update colors when farbtastic is updated
  $('.color-form input').click(function(event){
   updateColors();
  });

  $('.color-form input').keyup(function(event){
   updateColors();
  });

  $('.color-form select').click(function(event){
   updateColors();
  });

  $('.color-form select').keyup(function(event){
   updateColors();
  });

  $(document).bind('mousemove', checkDrag).bind('mouseup', checkDrag);

  function checkDrag() {
    if (document.dragging) {
      updateColors();
    }
  }

  function updateColors(source) {

    if (!initPreview) {
      initPreview = true;
      // Set warning message
      $('fieldset#color_scheme_form').prepend('<div class="messages warning sooper-livepreview-mssg">You are tuning colors in preview mode. Preview mode has some imperfections and will only give an approximate preview of the colorscheme. <strong>Submit the form to view the colorscheme in full effect</strong>.</div>');
      // Replace normal images with PNG ones

      toucan();
    }

    // From selectors as in the CSS theme-options file rendering in template.php... deleted all the selectors that are not needed on the colorform page to improve farbtastic performance.
    $('body, .item-list li,h1,h2,h3,h4,h5,h6').css('color',$('#edit-palette-text').val()); // dit overwrite alle css van alle tekst :|
    $('body a').css('color',$('#edit-palette-base').val());
    $('.poll .bar, #content ul.secondary li a, #cycle-pager a, ul.primary li a, div.block div.edit a, #toolbar, .skinr-color-3 .block-inner').css('background-color',$('#edit-palette-text').val());
    $('ul.secondary-links li a,#content ul.secondary li a.active, input.form-submit,#navbar, #navbar ul ul, ul.primary li.active a,.poll .bar .foreground,.skinr-color,ul.quicktabs_tabs.quicktabs-style-tundra li.active a').css('background-color',$('#edit-palette-base').val());
    $('#footer').css('border-color',$('#edit-palette-link').val());
    $('.skinr-color-2 .block-inner').css('background-color',$('#edit-palette-link').val());
    $('ul.secondary-links li a,#content ul.secondary li a.active, input.form-submit,#navbar a, ul.primary li.active a,.skinr-color,#content ul.secondary li a, #cycle-pager a, ul.primary li a, div.block div.edit a, #toolbar, .skinr-color-3 .block-inner').css('color','#fff');
    if ((window.Cufon)) { //Only update cufon if the headings color is updating, otherwise the layout update will be very slow
    Cufon.refresh();
    }
  }

  // Update layout when LivePreview button is clicked
  var containerWidth = '';
  var selectedUnit = '';
  var sidebarWidth = '';
  var singleWidth = '';
  var dualWidth = '';

  $('#live-preview-layout').click(function(event){
   updateLayout();
  });

  function updateLayout() {
  $('.sooper-mast').css('min-width',$('#edit-layout-min-width').val());

  if ($('#edit-layout-max-width').val() > 0) {
    $('.sooper-mast').css('max-width',$('#edit-layout-max-width').val());
  } else {
    $('.sooper-mast').css('max-width','none');
  }

    selectedUnit = $("input[@name='fixedfluid']:checked").val();
    widthFluid = $('#edit-layout-width-fluid').val();
    widthFixed = $('#edit-layout-width-fixed').val();
    if (selectedUnit == 'px') {
      $('.sooper-mast').animate({'width': widthFixed+'px'}, '1000ms');
    } else {
      $('.sooper-mast').animate({'width': widthFluid+'%'}, '1000ms');
    }

    sidebarWidth = Math.round($('#edit-sidebar-width').val()*1000)/1000;
    dualWidth = Math.round((100-$('#edit-sidebar-width').val()*2)*1000)/1000;
    singleWidth = Math.round((100-$('#edit-sidebar-width').val())*1000)/1000;
    $('body.two-sidebars #content').animate({'width': dualWidth+'%'}, '1000ms');
    $('body.one-sidebar #content').animate({'width': singleWidth+'%'}, '1000ms');
    $('.sidebar').animate({'width': sidebarWidth+'%'}, '1000ms');

    toucan();
  }

  // Update layout when randomizer is clicked
  $('#random-layout').click(function(event){
   randomLayout();
  });
  function randomLayout() {
    randomBinary = Math.floor(Math.random()*2);
    randomFixed = Math.floor(Math.random()*1401+600);
    randomFluid = Math.floor(Math.random()*71+30);
    randomSide = Math.floor(Math.random()*16+15);

    $('#edit-layout-width-fluid').val(randomFluid);
    $('#edit-layout-width-fixed').val(randomFixed);
    $('#edit-sidebar-width').val(randomSide)
    if (randomBinary) {
      $("input[@name='fixedfluid']").filter('[value=px]').attr('checked', true);
    } else {
      $("input[@name='fixedfluid']").filter('[value=%]').attr('checked', true);
    }
    updateLayout();
  }

  // Update Typography when selection changes
  $('#edit-headings-font-face, #edit-body-font-face').click(function(event){
   updateType();
  });

  $('#edit-headings-font-face, #edit-body-font-face').keyup(function(event){
   updateType();
  });

  function updateType() {
    bodyType = $('#edit-body-font-face').val();
    headingType = $('#edit-headings-font-face').val();

    $('body').css('font-family',fontFamily(bodyType));
    $('h1, h2, h3, h4, h5, h6, legend, p.mission, p.slogan').css('font-family',fontFamily(headingType));

    // Javascript does not support associative arrays :(
    function fontFamily(fontKey) {
      if (fontKey == 'helvetica') { family = 'Arial, Helvetica, "Helvetica Neue", "Nimbus Sans L", "Liberation Sans", "FreeSans", sans-serif'; }
      if (fontKey == 'verdana') { family = 'Verdana, "Bitstream Vera Sans", Arial, sans-serif'; }
      if (fontKey == 'lucida') { family = '"Lucida Grande", "Lucida Sans", "Lucida Sans Unicode", "DejaVu Sans", Arial, sans-serif'; }
      if (fontKey == 'geneva') { family = '"Geneva", "Bitstream Vera Serif", "Tahoma", sans-serif'; }
      if (fontKey == 'tahoma') { family = 'Tahoma, Geneva, "DejaVu Sans Condensed", sans-serif'; }
      if (fontKey == 'century') { family = '"Century Gothic", "URW Gothic L", Helvetica, Arial, sans-serif'; }
      if (fontKey == 'georgia') { family = 'Georgia, "Bitstream Vera Serif", serif'; }
      if (fontKey == 'palatino') { family = '"Palatino Linotype", "URW Palladio L", "Book Antiqua", "Palatino", serif'; }
      if (fontKey == 'times') { family = '"Times New Roman", Cambria, "Free Serif", Times, serif'; }

      return family;
    }

    toucan();
  }

  // Reload Cufon when selected font changes
  $('select#edit-cufon-font-face').change(function(event){
   updateCufon();
  });

  function updateCufon() {
    fontFile = $('select#edit-cufon-font-face').val();
    fontUrl = themePath+'features/sooper-fontkit/fonts/'+fontFile;

    $.getScript(fontUrl, function(){
      if(window.Cufon) { // unfortunately cufon.refresh works unreliably and the whole invocation needs to run here
        Cufon.replace('h1#sitename a, h1.nodetitle a', {
            hover: true
        });
        Cufon.replace(Drupal.settings.fontKit.invoke);
      } else {
        alert('Cufon needs to be enabled first, please enable cufon and save theme settings.')
      }
      alert("Font Loaded and Replaced");
    });

    toucan();
  }

  // Updating Background Image when selection changes
  $('#edit-background-image').click(function(event){
   updateBackground();
  });

  $('#edit-background-image').keyup(function(event){
   updateBackground();
  });

  function updateBackground() {
    selectedBackground = $('#edit-background-image').val()
    $('body').css('background-image','url('+themePath+'images/backgrounds/'+selectedBackground+')');
    
    toucan();
  }

  // Update colors when randomizer is clicked
  $('#random-color').click(function(event){
   randomColors();
  });
  function randomColors() {
    randomSeed = Math.floor(Math.random()*101)/100;
    randomLumi = Math.floor(Math.random()*101)/100;
    if (randomLumi > 0.85) { randomLumi = 0.85; };
    var farb = $.farbtastic('#placeholder');
    var randomHSL = [randomSeed,randomSeed,randomLumi]
    farb.setHSL(randomHSL);

    updateColors();
  }

  function toucan() {
    if (!initToucan) {
      initToucan = true;
      $('body').append('<div class="cornerstone toucan"></div>');
      $('.toucan').animate({'bottom': '-10px'},'2000ms');
    }
  }

});
