$(function() {
    $("div.slideshow .views-admin-links").remove(); // Remove views administration links, they mess up the cycle pager
    var pagerCounter = 1; //CSS nth-child pseudo selectors start counting at 1, not 0;
    $(Drupal.settings.featureKit.invoke).cycle({
        fx:                   Drupal.settings.featureKit.fx,
        timeout:              parseInt(Drupal.settings.featureKit.timeout),
        continuous:           parseInt(Drupal.settings.featureKit.continuous),
        speed:                parseInt(Drupal.settings.featureKit.speed),
        pagerEvent:           Drupal.settings.featureKit.pagerEvent,
        easing:               Drupal.settings.featureKit.easing,
        random:               parseInt(Drupal.settings.featureKit.random),
        pause:                parseInt(Drupal.settings.featureKit.pause),
        pauseOnPagerHover:    parseInt(Drupal.settings.featureKit.pauseOnPagerHover),
        delay:                parseInt(Drupal.settings.featureKit.delay),
        pager:                '#cycle-pager'
    }).find('div.pager').each(function () { //find all pager texts that are embedded in the slides
        currPager = $(this).html();
        $('#cycle-pager a:nth-child('+pagerCounter+')').append('. '+currPager); //inject embedded pager code into cycle pager
        $(this).hide();
        pagerCounter++; //set pointer to the next pager
      });
});