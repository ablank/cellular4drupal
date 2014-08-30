/**
 * @file
 * Custom javascript for use in your theme.
 */
!function($) {
    Drupal.behaviors.theme = {
        attach: function() {
            // Call cellular UI functions:
            $(".jAccordion").jAccordion(), $(".jBlocklink").jBlocklink(), $("form").jFormal(), 
            $(".jScrolli").jScrolli(), $(".jTabs").jTabs({}), $("#nav").jMmenu();
        }
    };
}(jQuery);