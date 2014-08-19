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
            $(".jAccordion").jAccordion(), $(".jBlocklink").jBlocklink(), $("form").jFormal(), 
            $(".jScrolli").jScrolli(), $(".jTabs").jTabs(), $("#nav").jMmenu();
        }
    };
}(jQuery);