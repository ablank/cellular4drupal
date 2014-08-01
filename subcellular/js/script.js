/*****
 script.js

 Custom javascript functions
 *****/
(function($) {

    Drupal.behaviors.theme = {
        attach: function(context, settings) {

            /////
            /// Call cellular functions
            /////
            $('.jAccordion').jAccordion();
            $('.jBlocklink').jBlocklink();
            //$('.jCarousel').jCarousel();
            //$('.jEqualheight').jEqualheight();
            $('form').jFormal();
            $('.jMmenu').jMmenu();
            //$('.jParallax').jParallax();
            $('.jScrolli').jScrolli();
            //$('.jSticky').jSticky();
            $('.jTabs').jTabs();

            /////
            /// Call Masonry
            /////       

            /*
             $('.block-content').masonry({
             containerStyle: null,
             itemSelector: '.blocklink-wrap',
             isWitWidth: true, 
             columnWidth: 240
             });
             */

            /////
            /// End Drupal.behaviors.theme
            ///// 
        }
    };
})(jQuery);
