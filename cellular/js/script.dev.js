/**
 * @file
 * Custom javascript for use in your theme.
 */
!function($) {
    Drupal.behaviors.theme = {
        attach: function() {
            // Call cellular UI functions:
            $(".jAccordion").jAccordion({}), $(".jBlocklink").jBlocklink({}), $(".jTabs").jTabs({}), 
            $("form").jFormal(), $("#nav").jMmenu(), $(".jScrolli").jScrolli();
        }
    };
}(jQuery);