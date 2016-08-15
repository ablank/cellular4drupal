/**
 * @file
 * Call javascript plugins used in theme.
 */

(function ($) {
  Drupal.behaviors.plugins = {
    attach: function (context, settings) {
      var opts = Drupal.settings.cellular;
      // CellularUI functions.
      if (typeof (opts.ui) !== 'undefined') {
        $('.jAccordion').jAccordion({
          duration: 500, // Duration of transition.
          easing: "swing", // Type of easing.
          single: false // Allow multiple panels to be opened or only 1?
        });

        $('.jCard').jCard();

        $('form').jFormal();

        $('#main-menu').jMmenu({
          animateclass: "slide-down"
        });

        $('.jScrolli').jScrolli({
          transition: {
            background: 'img:first', // Selector for applying background image
            pause: 8 // Time (seconds) to pause between slides.
              //speed: 500 // Animation speed (milliseconds).
          },
          autodim: true,
          delay: 1.4 // Time (seconds) to wait before dimming.
        });

        $('.jSocial.share').jSocial({
          share: opts.ui.jSocial_share
        });

        $('.jSocial.follow').jSocial({
          follow: opts.ui.jSocial_follow
        });

        $('.jTabs').jTabs({
          active: 0, // Array index of initially active content.
          orient: "horizontal" // || "vertical"
        });
        $('.jTabs.vertical').jTabs({
          active: 0, // Array index of initially active content.
          orient: "vertical" //
        });

        //$('[data-tooltip]').jTooltip();

      }

      // Backstretch functions.
      if (opts.plugins.backstretch === true) {
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
      if (opts.plugins.flowtype === true) {
        $('#content-wrap').flowtype({
          minimum: 400,
          maximum: 800,
          minFont: 12,
          maxFont: 40,
          fontRatio: 45
        });
      }

      // Freetile functions.
      if (opts.plugins.freetile === true) {
        $('.view-content').freetile({
          selector: '.views-row',
          animate: true,
          // containerAnimate: true,
          elementDelay: 0
        });
      }

      // jParallax functions.
      if (opts.plugins.jparallax === true) {
        $('.parallax').parallax({
          xparallax: false,
          yparallax: true,
          freezeClass: "freeze",
          decay: 0.4
        });
      }

      // Smoove functions.
      if (opts.plugins.smoove === true) {
        $('.smoove').smoove({
          offset: "20%",
          // skew: "20deg",
          // moveX: "15%",
          moveY: "20%"
        });
      }

      if (opts.plugins.nprogress === true) {
        $(document).on('ajaxStart', function () {
          NProgress.start();
        })
          .on('ajaxComplete', function () {
            NProgress.done().remove();
          });
      }
      /* End Drupal.behaviors.plugins */
    }
  };
})(jQuery);
