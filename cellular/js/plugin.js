/**
 * @file
 * Call javascript plugins used in theme.
 */

(function ($) {
  Drupal.behaviors.theme.plugins = {
    attach: function (context, settings) {
      // CellularUI functions.
      if (Drupal.settings.cellular.cellularui === true) {
        $('.jAccordion').jAccordion({
          "active": 0, // Index value of initial content to display.
          "duration": 500, // Duration of transition.
          "easing": "swing", // Type of easing.
          "single": false // Allow multiple panels to be opened or only 1?
        });
        $('.jBlocklink').jBlocklink({
          "cclass": "jBlocklink-link"
        });
        $('form').jFormal({
          "inputs": [// Array of elements to format.
            'input[type="text"]',
            'input[type="email"]',
            'input[type="password"]',
            'textarea'
          ]
        });
        $('#nav').jMmenu({
          // Window breakpoint trigger:
          // "breakpoint": cellular.opts.breakpoint, // default
          // Classes added for styling.
          // "cclass": "jMmenu", // default
          "type": "slide",
          "direction": "right"
        });
        $('.jScrolli').jScrolli({
          "active": 0, // Array index of initially active content.
          "speed": 500, // Duration of cycle.
          "pause": 3000 // Time to pause between cycles.
        });
        $('.jTabs').jTabs({
          "active": 0, // Array index of initially active content.
          "orient": "horizontal" // || 'vertical'
        });
      }

      // Masonry functions.
      if (Drupal.settings.cellular.masonry === true) {
        $('.masonry').masonry({
          containerStyle: null,
          itemSelector: '.blocklink-wrap',
          isWitWidth: true,
          columnWidth: 240
        });
      }

      // Smoove functions.
      $(".smoove").smoove({
        offset: "15%",
        moveX: "15%"
      });

      /* End Drupal.behaviors.theme */
    }
  };
})(jQuery);
