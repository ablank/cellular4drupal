/**
 * @file
 * Call javascript plugins used in theme.
 */

(function ($) {
  Drupal.behaviors.plugins = {
    attach: function (context, settings) {
      // CellularUI functions.
      if (Drupal.settings.cellular.cellularui === true) {
        $('.jAccordion').jAccordion({
          duration: 500, // Duration of transition.
          easing: "swing", // Type of easing.
          single: false // Allow multiple panels to be opened or only 1?
        });
        $('.jBlocklink').jBlocklink({
          cclass: "jBlocklink-link" // Class to add to wrapper link.
        });
        $('#nav').jMmenu({
          // Window breakpoint trigger:
          // "breakpoint": cellular.opts.breakpoint, // 650px
           cclass: "jMmenu", // default
          // Classes added for styling- CSS classes control position & animation.
          // Vars concat to class="type-direction".
          type: "push",
          direction: "down"
        });
        $('.jScrolli').jScrolli({
          active: 0, // Array index of initially active content.
          speed: 500, // Duration of cycle.
          pause: 3000 // Time to pause between cycles.
        });
        $('.jTabs').jTabs({
          active: 0, // Array index of initially active content.
          orient: "horizontal" // || 'vertical'
        });
      }

      // Backstretch functions.
      if (Drupal.settings.cellular.backstretch === true) {
        $.backstretch([
          "http://lorempixel.com/800/600/abstract/1",
          "http://lorempixel.com/800/600/abstract/2",
          "http://lorempixel.com/800/600/abstract/3"
        ], {
          duration: 3000,
          fade: 750
        });
      }

      // Flowtype functions.
      if (Drupal.settings.cellular.flowtype === true) {
        // Smoove functions.
        $('body').flowtype({
          minimum: 400,
          maximum: 800,
          minFont: 10,
          maxFont: 40,
          fontRatio: 45
        });
      }

      // Freetile functions.
      if (Drupal.settings.cellular.freetile === true) {
        // Smoove functions.
        $('.view-content').freetile({
          selector: '.views-row',
          animate: true,
          // containerAnimate: true,
          elementDelay: 0
        });
      }

      // jParallax functions.
      if (Drupal.settings.cellular.jparallax === true) {
        $('.parallax').parallax({
          xparallax: false,
          yparallax: true,
          freezeClass: "freeze",
          decay: 0.4
        });
      }

      // Smoove functions.
      if (Drupal.settings.cellular.smoove === true) {
        $('.smoove').smoove({
          offset: "20%",
          // skew: "20deg",
          // moveX: "15%",
          moveY: "20%"
        });
      }

      /* End Drupal.behaviors.plugins */
    }
  };
})(jQuery);