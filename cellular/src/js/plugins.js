/**
 * @file
 * Call javascript plugins used in theme.
 */

(function ($) {
  Drupal.behaviors.plugins = {
    attach: function (context, settings) {
      // CellularUI functions.
      if (Drupal.settings.cellular.cellularui === true) {

        $('.jCard').jCard();
        $('.jTooltip').jTooltip();

        $('.jAccordion').jAccordion({
          duration: 500, // Duration of transition.
          easing: "swing", // Type of easing.
          single: false // Allow multiple panels to be opened or only 1?
        });

        $('#nav').jMmenu({
          animateclass: "slide-down"
        });

        $('.jTabs').jTabs({
          active: 0, // Array index of initially active content.
          orient: "horizontal" // || "vertical"
        });
        $('.jTabs.vertical').jTabs({
          active: 0, // Array index of initially active content.
          orient: "vertical" //
        });

        $('.jSocial').jSocial({
          share: [
            'facebook',
            'google',
            'twitter'
                    //'digg',
                    //'linkedin',
                    //'pinterest',
                    //'reddit',
                    //'stumbleupon',
                    //'tumblr'
          ]
                  /*
                   follow: {
                   facebook: {
                   url: "https://facebook.com"
                   },
                   google: {
                   url: "https://plus.google.com"
                   },
                   twitter: {
                   url: "https://twitter.com"
                   },
                   linkedin: {
                   url: "https://linkedin.com"
                   },
                   pinterest: {
                   url: "https://pinterest.com"
                   },
                   yelp: {
                   url: "https://yelp.com"
                   }
                   }
                   */
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
        /*
         $('.jScrolli').jScrolli({
         cclass: 'jScrolli', // Object class selector
         active: 0, // Index of initially selected slide
         height: 'auto', // 'auto' or '[value]', i.e. '300px'
         controls: {
         showcontrols: true,
         keyboard: true,
         swipe: true,
         showmarkers: true,
         autoplay: false,
         pauseonhover: true,
         text: {
         next: 'Next',
         prev: 'Prev',
         pause: 'Pause'
         }
         },
         transition: {
         pause: 5 // Time (seconds) to pause between slides.
         //speed: 500 // Animation speed (milliseconds).
         },
         caption: {
         enable: true,
         autohide: false,
         selector: '.caption' // 'auto' or '.selector' used to generate caption
         },
         autodim: true,
         delay: 1.4, // Time (seconds) to wait before dimming.
         background: 'img:first' // Selector for applying background image
         });*/
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
        $('#content-wrap').flowtype({
          minimum: 400,
          maximum: 800,
          minFont: 12,
          maxFont: 40,
          fontRatio: 45
        });
      }

      // Freetile functions.
      if (Drupal.settings.cellular.freetile === true) {
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
