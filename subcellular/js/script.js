/**
 * @file
 *  Custom javascript for use in your theme
 */

(function ($) {

    Drupal.behaviors.theme = {
        attach: function (context, settings) {
            /// Call cellular functions
            $('.jAccordion').jAccordion();
            $('.jBlocklink').jBlocklink();
            $('form').jFormal();
            $('.jScrolli').jScrolli();
            $('.jTabs').jTabs({
                //"orient": "vertical"
            });
            $('#nav').jMmenu();
            //$('#nav').jStickyheader();
            // $('.jParallax').jParallax();
            //$('.jScrolltrigger').jScrolltrigger();
            //$('.jCarousel').jCarousel();
            //$('.jEqualheight').jEqualheight();
            //
            //$('.jToggle').jToggle();
            //$('.jSticky').jSticky();

            // Call Masonry
            /*
             $('.block-content').masonry({
             containerStyle: null,
             itemSelector: '.blocklink-wrap',
             isWitWidth: true, 
             columnWidth: 240
             });
             */

            // End Drupal.behaviors.theme
        }
    };
})(jQuery);
