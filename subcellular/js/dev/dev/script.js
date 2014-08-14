/*****
 script.js

 Custom javascript functions
 *****/
!function($) {
    Drupal.behaviors.theme = {
        attach: function() {
            /////
            /// Call cellular functions
            /////
            $(".jAccordion").jAccordion(), $(".jBlocklink").jBlocklink(), //$('.jCarousel').jCarousel();
            //$('.jEqualheight').jEqualheight();
            $("form").jFormal(), $(".jMmenu").jMmenu(), //$('.jParallax').jParallax();
            $(".jScrolli").jScrolli(), //$('.jSticky').jSticky();
            $(".jTabs").jTabs();
        }
    };
}(jQuery);