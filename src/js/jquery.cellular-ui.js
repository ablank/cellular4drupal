/**
 * @file
 * CellularUI Javascript Library
 *
 * @author Adam Blankenship <i.adambear@gmail.com>
 *
 * @see http://live-cellular.gotpantheon.com/cellular-ui
 */
(function ($) {
  Drupal.behaviors.cellular = {
    attach: function (context, settings) {
      var cellular = {};
      cellular.opts = {
        cclass: "cellular",
        activeclass: "active",
        breakpoint: "window_small"
      };
      cellular.state = {
        breakpoint: 0,
        scrolltop: 0,
        scrolltimer: 0
      };
      /**
       * Cellular utility functions
       */
      /**
       * Get the breakpoints specified in CSS
       */
      cellular.breakpoint = function () {
        var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content'),
                win = {};
        /*
         if (content) {
         win.type =  content.match(/\w*[^\"\'](?=-)/g).join("");
         } else {*/
// Provide default breakpoints if they aren't set by css.
        var ww = jQuery(window).width();
        switch (ww) {
          case ww < 650:
            win.type = 'window_small';
            break;
          case ww > 650 && ww < 800:
            win.type = 'window_narrow';
            break;
          case ww > 1200:
            win.type = 'window_large';
            break;
          case ww > 800 && ww < 1200:
          default:
            win.type = 'window_default';
            break;
        }
// }
        jQuery('body').addClass(win.type);
        win.size = ww;
        return win;
      };
      /**
       * Add active class to element, remove active class from element siblings
       */
      cellular.activate = function (theclass) {
        theclass = theclass ? theclass : cellular.opts.activeclass;
        return this.each(function () {
          var $t = jQuery(this);
          if (!$t.hasClass(theclass)) {
            $t.addClass(theclass)
                    .siblings().removeClass(theclass);
          }
        });
      };
      /**
       * Remove 'active' class
       */
      cellular.deactivate = function (theclass) {
        theclass = theclass ? theclass : cellular.opts.activeclass;
        return this.each(function () {
          jQuery(this).removeClass(theclass);
        });
      };
      /**
       * Wrap element's children after 1st child
       */
      cellular.kidWrap = function () {
        return this.each(function () {
          var $t = jQuery(this);
          if ($t.children().length > 1) {
            $t.children(':gt(0)').wrapAll('<div>');
          }
        });
      };
      /**
       * Add array of classes to element
       */
      cellular.classify = function ($array) {
        return this.each(function () {
          jQuery(this).addClass($array.join(' '));
        });
      };
      /**
       * Debounce fn borrowed from Underscore.js
       */
      cellular.debounce = function (func, wait, immediate) {
        var timeout;
        return function () {
          var context = this,
                  args = arguments,
                  later = function () {
                    timeout = null;
                    if (!immediate) {
                      func.apply(context, args);
                    }
                  },
                  callNow = immediate && !timeout;
          clearTimeout(timeout);
          timeout = setTimeout(later, wait);
          if (callNow) {
            func.apply(context, args);
          }
        };
      };
      /**
       * Detect css transition end event.
       * @see Function from David Walsh: http://davidwalsh.name/css-animation-callback
       */
      cellular.transitionend = function () {
        var t,
                el = document.createElement("test"),
                transitions = {
                  transition: "transitionend",
                  OTransition: "oTransitionEnd",
                  MozTransition: "transitionend",
                  WebkitTransition: "webkitTransitionEnd"
                };
        for (t in transitions) {
          if (el.style[t] !== undefined) {
            return transitions[t];
          }
        }
      };
      /**
       * Reset scroll timer
       */
      cellular.scrolltimer = function (el, uc, dc) {
        window.clearTimeout(cellular.state.scrolltimer);
        cellular.state.scrolltimer = window.setTimeout(function () {
          el.removeClass(uc + ' ' + dc);
        }, 2000);
      };
      /**
       *
       * @param {string} href
       * @param {string} title
       * @param {array} classes
       * @returns {string}
       */
      cellular.buttonize = function (href, title, classes) {
        var btn = $('<a />')
                .prop({
                  "href": href,
                  "title": title,
                  "tabindex": "0"
                })
                .text(title)
                .classify(classes);
        return $(this).append(btn);
      };
      /**
       *
       */
      cellular.scrollto = function (target, time) {
        target = target || jQuery(this).attr('href');
// Scroll to page anchors.
        jQuery('a[href^="#"]').on('click', function (e) {
          e.preventDefault();
          jQuery('html, body').stop().animate({
            scrollTop: jQuery(target).offset().top
          }, time);
        });
      };
      /**
       * Set state on window resize
       */
      cellular.windowstate = cellular.debounce(function () {
        var ob = cellular.state.breakpoint;
        cellular.state.breakpoint = cellular.breakpoint().type;
        jQuery('body').removeClass(ob)
                .addClass(cellular.state.breakpoint);
      }, 100);
      /**
       * Set state on document scroll
       */
      cellular.scrollstate = cellular.debounce(function (e, y) {
        var el = jQuery('body'),
                cclass = 'scrolling',
                uc = cclass + '-up',
                dc = cclass + '-down',
                dst = jQuery(document).scrollTop(),
                region = el.height() / 3,
//y = cellular.state.scrolltop,
                scrolltimeout = null;
        if (dst > 30) {
          el.addClass('scrolled');
        } else {
          el.removeClass('scrolled');
        }
        if (dst > cellular.state.scrolltop) {
          el.addClass(dc)
                  .removeClass(uc);
        } else {
          el.addClass(uc)
                  .removeClass(dc);
        }
// Detect if page is scrolled
        if (dst < region) {
          el.removeClass('page-middle page-bottom')
                  .addClass('page-top');
        } else if (dst > region && dst < region * 2) {
          el.removeClass('page-top page-bottom')
                  .addClass('page-middle');
        } else {
          el.removeClass('page-top page-middle')
                  .addClass('page-bottom');
        }
//Update global state
        cellular.state.scrolltop = dst;
// % of doc scrolled
        cellular.state.scrolled = (dst / (el.height() - jQuery(window).height())) * 100;
      }, 0, true);
      (function state() {
// Get initial state
        cellular.windowstate();
        cellular.scrollstate();
// Update state on user interaction
        jQuery(window).on('resize', cellular.windowstate);
        jQuery(document).on('scroll', cellular.scrollstate);
      })();
      cellular.jAccordion = function (opts) {
        var o = jQuery.extend({
          active: 0, // Index value of initial content to display.
          duration: 500, // Duration of transition.
          easing: "swing", // Type of easing.
          single: false, // Allow multiple panels to be opened or only 1?
          pclass: "panel"
        }, opts),
                fn = {};
        o.pselect = '.' + o.pclass;
        /**
         * The <li> object to show.
         *
         * @param object li
         *  $('<li>')
         */
        fn.showContent = function (li) {
          if (o.single) {
            li.siblings().find(o.pselect).slideUp(o.duration, o.easing);
            li.activate()
                    .find(o.pselect).slideDown(o.duration, o.easing);
          } else {
            li.toggleClass(cellular.opts.activeclass)
                    .find(o.pselect).slideToggle(o.duration, o.easing);
          }
        };
        /**
         * Generate markup for controls & other elements.
         *
         * @param object $obj
         */
        fn.style = function ($obj) {
          $obj.once('jAccordion', function () {
            $obj.prop("tabindex", "0").find('> li').each(function () {
              var li = jQuery(this);
              li.kidWrap();
              li.children().eq(0).addClass('title');
              li.children().eq(1).classify([cellular.opts.cclass, 'panel']);
              li.find(o.pselect).hide();
              li.find('.title').click(function (e) {
                e.preventDefault();
                fn.showContent(li);
              });
            });
          });
        };
        /**
         * Init jAccordion
         */
        fn.init = function () {
          var $obj = jQuery(this);
// Generate markup for accordion
          fn.style($obj);
//Set default content
          fn.showContent($obj.children().eq(o.active));
        };
        return this.each(fn.init);
      };
      cellular.jCard = function (opts) {
        var o = jQuery.extend({
          cclass: "jCard"
        }, opts),
                fn = {};
        fn.init = function () {
          var $obj = jQuery(this);
          $obj.once(o.cclass, function () {
            var a1 = $obj.find('a').eq(0);
            var href = a1.attr('href');
            if (href !== undefined) {
              var wrapperlink = jQuery('<a href="' + href + '" tabindex="0" />').classify([
                o.cclass + '-wrap',
                a1.attr('class') ? a1.attr('class') : null
              ]);
              $obj.wrap(wrapperlink)
                      .find('h2, h3').addClass('title');
            }
          });
          $obj.on('mouseenter touchstart', function () {
            $obj.activate();
          }).on('mouseleave touchend', function () {
            $obj.deactivate();
          });
        };
        return this.each(fn.init);
      };
      /**
       * jFormal: Improve form interaction
       */
      cellular.jFormal = function (opts) {
        var o = jQuery.extend({
          inputs: [
            'input[type="text"]',
            'input[type="email"]',
            'input[type="password"]',
            'textarea'
          ]
        }, opts);
        return this.each(function () {
          var inputs = o.inputs.join(',');
// get/set value of inputs
          jQuery(inputs).each(function () {
            var $t = jQuery(this),
                    hold = holder = $t.attr('placeholder');
            $t.on('focus', function () {
              holder = '';
              if (this.value === this.defaultValue) {
                this.value = '';
              }
            }).on('blur', function () {
// Reset to default value if no changes were made.
              holder = hold;
              if (this.value === '' || null) {
                this.value = this.defaultValue;
              }
            });
          });
        });
      };
      /**
       * jMmenu: Hamburger menu for mobile devices
       */
      cellular.jMmenu = function (opts) {
        var o = jQuery.extend({
          breakpoint: cellular.opts.breakpoint, // 'window_small'|| 'window_narrow' || 'window_default'
          parent: jQuery('body'), // Parent element used to attach menu
          cclass: "jMmenu", // Menu class to test
          triggertext: "Menu",
          animateclass: "slide-right", // Type of animation
          throttle: 101 // Time in ms to throttle window resize event
        }, opts),
                fn = {};
        fn.mediaQuery = cellular.debounce(function ($obj, state) {
//console.log(cellular.opts.breakpoint);
          if (o.breakpoint === cellular.state.breakpoint) {
            var $menu = $obj.children([0]),
                    label = null;
            state.mmenu = true;
            o.parent.addClass(o.animateclass);
            if (o.triggertext) {
              label = '<span class="' + o.cclass + '-triggertext">' + o.triggertext + '</span>';
            }
            $obj.prop("tabindex", "0")
                    .addClass(o.cclass + '-trigger')
                    .append(label);
            $menu.addClass(o.cclass + '-menu')
                    .prependTo(o.parent);
          } else {
            state.mmenu = false;
            state.active = false;
            o.parent.removeClass(
                    o.cclass + '-active ' +
                    o.cclass + '-inactive ' +
                    o.animateclass
                    );
            $obj.attr('aria-label', "Menu")
                    .removeClass(o.cclass + '-trigger');
            jQuery('.' + o.cclass + '-menu').removeClass(o.cclass + '-menu')
                    .prependTo($obj);
            jQuery('.' + o.cclass + '-triggertext').remove();
          }
          fn.menutrigger($obj, state);
        }, o.throttle);
        fn.menutrigger = function ($obj, state) {
          var classes = [
            o.cclass + '-active',
            o.cclass + '-inactive'
          ];
          if (state.active) {
            $obj.activate()
                    .attr('aria-label', "Close Menu");
            jQuery('.' + o.cclass + '-menu').addClass('active');
            o.parent.addClass(classes[0])
                    .removeClass(classes[1]);
          } else {
            $obj.deactivate()
                    .attr('aria-label', "Open Menu");
            jQuery('.' + o.cclass + '-menu').removeClass('active');
            if (state.mmenu) {
              o.parent.addClass(classes[1])
                      .removeClass(classes[0]);
            }
          }
        };
        fn.style = function ($obj) {
          var menu = $obj.find('>ul'),
                  nested = menu.find('ul');
// Add classes for parent/child.
          if (nested.length > 0) {
            var child = menu.find('li ul');
            child.addClass('child')
                    .parent().addClass('parent')
                    .css({
                      willChange: 'contents'
                    });
          }
        };
        fn.listen = function ($obj, state) {
          jQuery(window).on('resize', function () {
            fn.mediaQuery($obj, state);
          });
          $obj.on('click', function () {
            if (state.mmenu) {
              state.active = state.active ? false : true;
              fn.menutrigger($obj, state);
            }
          });
          jQuery(document).on('keyup', function (e) {
// ENTER opens menu.
            if (jQuery('.' + o.cclass + '-trigger').is(":focus") && e.which === 13) {
              e.preventDefault();
              state.active = state.active === false ? true : false;
              fn.menutrigger($obj, state);
            }
// ESC closes menu.
            if (state.active === true && e.which === 27) {
              e.preventDefault();
              state.active = false;
              fn.menutrigger($obj, state);
            }
          });
          jQuery('.parent > a').click(function (e) {
            if (state.mmenu) {
              var parent = jQuery(this).parent(),
                      child = parent.children(':gt(0)');
              if (child.length > 0) {
                e.preventDefault();
                if (child.hasClass('active')) {
                  parent.removeClass('active');
                  child.removeClass('active');
                } else {
                  parent.addClass('active');
                  child.addClass('active');
                }
              }
            }
          });
        };
        fn.init = function () {
          var $obj = jQuery(this),
                  state = {
                    active: false,
                    mmenu: false
                  };
          $obj.addClass(o.cclass)
                  .once(o.cclass, fn.style($obj));
          fn.mediaQuery($obj, state);
          fn.listen($obj, state);
        };
        return this.each(fn.init);
      };
      /**
       * jScrolli : Content carousel/slider
       */
      cellular.jScrolli = function (opts) {
        var o = $.extend({
          cclass: "jScrolli", // Object class selector
          active: 0, // Index of initially selected slide
          background: 'img:first', // Selector for applying background image
          title: 'h2, h3', // Selector for applying title class
//width: "100%", // 'auto' or '[value]', i.e. '300px'
          height: "auto", // 'auto' or '[value]', i.e. '300px'
          controls: {
            showmarkers: true,
            showcontrols: true,
            keyboard: true,
            swipe: true,
            autoplay: true,
            pauseonhover: true,
            autodim: true,
            delay: 1.4, // Time (seconds) to wait before dimming.
            text: {
              next: "Next",
              prev: "Prev",
              pause: "Pause",
              play: "Play"
            }
          },
          transition: {
            pause: 5 // Time (seconds) to pause between slides.
//speed: 500 // Animation speed (milliseconds).
          },
          caption: {
            enable: true,
            autohide: false,
            selector: ".caption" // '.selector' used to generate caption
          }
        }, opts),
                fn = {};
        /**
         * Format html buttons for controls.
         *
         * @param string $text
         * @returns string
         */
        fn.button = function ($text) {
          return '<a class="' + o.cclass + '-control ' + $text.toLowerCase() + '">' + $text + '</a>';
        };
        /**
         * Update next/prev slides.
         *
         * @param object state
         */
        fn.normalize = function (state) {
          state.prev = state.current - 1;
          state.next = state.current + 1;
          if (state.prev < 0) {
            state.prev = state.count;
          }
          if (state.next > state.count) {
            state.next = 0;
          }
        };
        /**
         * Activate selected slide & corresponding marker.
         *
         * @param int index
         * @param object $obj
         * @param object state
         */
        fn.go = function (index, $obj, state) {
          if (!state.paused) {
            var tclass = 'transition',
                    li = $obj.find('.' + o.cclass + '-slide');
// Unset tabindexes
            li.find('a').prop("tabindex", "-1");
// Get current slide.
            state.current = parseInt(index);
// Normalize state.
            fn.normalize(state);
// Update classes on slides for css transition.
            jQuery(li[state.prev]).activate('previous');
            jQuery(li[state.next]).activate('next');
            jQuery(li[index]).activate()
                    .find('a').prop("tabindex", "-1");
// Listen for transition to complete & update classes.
            $obj.parent().addClass(tclass)
                    .on(cellular.transitionend(), function () {
                      jQuery(this).removeClass(tclass);
                    });
// Update the marker
            if (o.controls.showmarkers) {
              fn.mark($obj, state);
            }
// Update the caption
            if (o.caption.enable) {
              fn.caption(li, state);
            }
// Reset the autoplay timer
            if (o.controls.autoplay) {
              fn.updateinterval($obj, state);
            }
          }
        };
        /**
         * Update the current marker.
         */
        fn.mark = function ($obj, state) {
          $obj.siblings().find('.' + o.cclass + '-marker')
                  .eq(state.current).activate();
        };
        /**
         * Update slide caption
         */
        fn.caption = function ($obj, state) {
          var wrap = $obj.parent().parent(),
                  cap = wrap.find('> .caption p');
// Get current slide's caption
          state.caption = wrap.find(o.caption.selector).eq(state.current).text();
          cap.on(cellular.transitionend(), function () {
// Update the active caption
            $(this).text(state.caption)
                    .activate();
          });
        };
        /**
         * Reset autoplay timer.
         */
        fn.updateinterval = function ($obj, state) {
          if (o.controls.autoplay && !state.paused) {
            clearInterval(state.interval);
            state.interval = setInterval(function () {
              state.current = state.next;
              fn.go(state.current, $obj, state);
            }, o.transition.pause * 1000);
          }
        };
        /**
         * Add event listeners
         *
         * @param {type} $obj
         * @param {type} state
         */
        fn.events = function ($obj, state) {
          var controls = $obj.siblings('.controls'),
                  wrap = $obj.parent(),
                  eX = null,
                  eY = null;
// Link markers to respective slides
          if (o.controls.showmarkers) {
            $obj.siblings().find('.' + o.cclass + '-marker').on('click', function () {
              state.current = jQuery(this).attr('data-href');
              state.paused = false;
              fn.go(state.current, $obj, state);
            });
          }
// Previous
          wrap.find('.prev').on('click', function (e) {
            state.current = state.prev;
            state.paused = false;
            fn.go(state.current, $obj, state);
          });
// Next
          wrap.find('.next').on('click', function (e) {
            state.current = state.next;
            state.paused = false;
            fn.go(state.current, $obj, state);
          });
          /*
           // Play/Pause
           wrap.find('.pause').on('click', function (e) {
           jQuery(this).activate('play')
           .deactivate('pause')
           .text('Play');
           state.paused = true;
           clearInterval(state.interval);
           console.log(state.paused);
           });
           wrap.find('.play').on('click', function (e) {
           jQuery(this).activate('pause')
           .deactivate('play')
           .text('Pause');
           state.paused = false;
           fn.updateinterval($obj, state);
           console.log(state.paused);
           });
           */
// Pause/showcontrols
          wrap.on({
            'mouseover': function () {
              state.active = true;
              if (o.controls.pauseonhover) {
                state.paused = true;
              }
              if (o.controls.autodim) {
                wrap.activate();
                window.clearTimeout(wrap.timeout);
              }
            },
            'mouseout': function () {
              state.active = false;
              if (o.controls.pauseonhover) {
                state.paused = false;
              }
              if (o.controls.autodim) {
                wrap.timeout = window.setTimeout(function () {
                  wrap.deactivate();
                }, o.controls.delay * 1000);
              }
            }
          });
// Keyboard
          if (o.controls.keyboard) {
            jQuery(document).on('keyup', function (e) {
              var keys = [
                37, // left
                39 // right
//38, // up
//40 // down
              ];
              if (keys.indexOf(e.which) !== -1) {
                e.preventDefault();
                state.paused = false;
                switch (e.which) {
                  case 37:
                    state.current = state.prev;
                    break;
                  case 39:
                    state.current = state.next;
                    break;
                }
                fn.go(state.current, $obj, state);
              }
            });
          }
          /*
           // Swipe
           if (o.controls.swipe) {
           $obj.on({
           'mousedown touchstart': function (e) {
           state.paused = true;
           if (e.touches) {
           eX = e.touches[0].clientX;
           eY = e.touches[0].clientY;
           }
           else {
           eX = e.pageX;
           eY = e.pageY;
           }
           },
           'mouseup touchmove': function (e) {
           if (!eX || !eY) {
           return;
           }
           var margin = 20,
           Xdiff,
           Ydiff;
           if (e.touches) {
           Xdiff = eX - e.touches[0].clientX;
           Ydiff = eY - e.touches[0].clientY;
           }
           else {
           Xdiff = eX - e.pageX;
           Ydiff = eY - e.pageY;
           }
           // Detect horizontal or vertical
           if (Math.abs(Xdiff) > Math.abs(Ydiff)) {
           // Horizontal (left : right)
           if (Xdiff < margin) {
           // right
           state.current = state.next;
           }
           else if (Xdiff > margin) {
           // left
           state.current = state.prev;
           }
           } else {
           if (Ydiff < margin) {
           // down
           state.current = state.next;
           }
           else if (Ydiff > margin) {
           // up
           state.current = state.prev;
           }
           }
           // Reset vars for next swipe
           eX = null;
           eY = null;
           // Move to next slide
           state.paused = false;
           fn.go(state.current, $obj, state);
           }
           });
           }
           */
        };
        /**
         * Set height explicitly to prevent 'jumping' content.
         *
         * @param object $obj
         * @param object state
         */
        fn.setheight = function ($obj, state) {
          jQuery(document).ready(function () {
            if (o.height === 'auto') {
              $obj.find('> li').each(function () {
                var tHeight = this.clientHeight;
                if (tHeight > state.maxheight) {
                  state.maxheight = tHeight;
                }
              });
            } else {
              state.maxheight = o.height;
            }
            $obj.height(state.maxheight);
          });
        };
        /**
         * Generate markup for controls & other elements.
         *
         * @param object $obj
         * @param object state
         */
        fn.style = function ($obj, state) {
          var li = $obj.find('> li');
          $obj.prop("tabindex", "0")
                  .addClass(cellular.opts.cclass)
                  .wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />')
                  .parent().css({
            willChange: "contents"
          });
          li.prop('tabindex', "-1")
                  .addClass(o.cclass + '-slide')
                  .each(function () {
                    var $t = jQuery(this);
                    $t.children().wrapAll('<div class="' + o.cclass + '-slide-content cell" />');
                    if (o.title) {
                      $t.find(o.title).addClass('title');
                    }
                    if (o.background) {
                      var background = $t.find(o.background);
                      if (background.length) {
                        background.hide();
                        $t.css({
                          'background-image': 'url(' + background.attr('src') + ')'
                        })
                                .addClass(o.cclass + '-background');
                      }
                    }
                  });
          fn.setheight($obj, state);
          if (o.controls.showmarkers) {
            var markers = jQuery('<ul class="' + o.cclass + '-markers"/>');
            for (var i = 0; i < li.length; i += 1) {
              markers.append('<li class="' + o.cclass + '-marker" data-href="' + i + '">' + (i + 1) + '</li>');
            }
            $obj.after(markers);
            fn.mark($obj, state);
          }
          if (o.caption.enable) {
            var cap = $obj.find(o.caption.selector);
            if (cap.length) {
              cap.hide();
              $obj.after('<div class="' + o.cclass + '-caption"><p/></div>');
            }
          }
          if (o.controls.showcontrols) {
            var j,
                    controls = [
                      fn.button(o.controls.text.prev),
                      fn.button(o.controls.text.next)
//o.autoplay ? fn.button(o.controls.text.pause) : null
                    ];
            for (j = 0; j < controls.length; j += 1) {
              $obj.parent().prepend(controls[j]);
            }
          }
        };
        /**
         * Init jScrolli
         */
        fn.init = function () {
          var $obj = jQuery(this),
                  state = {
                    active: true,
                    paused: false,
                    count: $obj.find('> li').length - 1,
//height: o.height ? o.height : fn.setheight($obj, state),
                    width: o.width ? o.width : $obj.width(),
                    maxheight: 0,
                    interval: 0,
                    controls: 0,
                    caption: jQuery(o.caption.selector).html(),
                    current: o.active ? o.active : 0
                  };
// o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
// Add markup
          $obj.once(o.cclass, function () {
            fn.style($obj, state);
          });
// Add Event Listeners
          fn.events($obj, state);
// Activate 1st slide
          fn.go(state.current, $obj, state);
// Start autoplay
          fn.updateinterval($obj, state);
        };
        return this.each(fn.init);
      };
      cellular.jSocial = function (opts) {
        var doctitle = document.title,
                page = $("link[rel='canonical']") ? $("link[rel='canonical']").attr('href') : window.location;
        var o = jQuery.extend({
          sharetitle: "", // "Share this page",
          followtitle: "", // "Follow Us",
          buttonclass: "social",
          share: [
// 'facebook',
// 'digg',
// 'google',
// 'twitter',
// 'linkedin',
// 'pinterest',
// 'reddit',
// 'stumbleupon',
//'tumblr'
          ],
          follow: {
            /*
             facebook: {
             title: "Facebook",
             url: "https://facebook.com"
             }
             */
          }
        }, opts),
                fn = {};
        /**
         * Generate markup for buttons.
         *
         * @param object $obj
         */
        fn.style = function ($obj) {
          $obj.once('jSocial', function () {
            if (o.share) {
              var sWrap = $('<div class="jSocial-share" />'),
                      sharetitle,
                      sharelinks = {
                        facebook: {
                          title: "Facebook",
                          url: "http://facebook.com/sharer/sharer.php?u=" + page
                        },
                        digg: {
                          title: "Digg",
                          url: "http://digg.com/submit?url=" + page + "&title=" + doctitle
                        },
                        google: {
                          title: "Google",
                          url: "https://plus.google.com/share?url=" + page
                        },
                        twitter: {
                          title: "Twitter",
                          url: "https://twitter.com/intent/tweet?url=" + page + "&text=" + doctitle
                        },
                        linkedin: {
                          title: "LinkedIn",
                          url: "http://linkedin.com/shareArticle?url=" + page + "&title=" + doctitle
                        },
                        pinterest: {
                          title: "Pinterest",
                          url: "http://pinterest.com/pin/create/bookmarklet/?url=" + page + "&description=" + doctitle
                        },
                        reddit: {
                          title: "Reddit",
                          url: "http://reddit.com/submit?url=" + page + "&title=" + doctitle
                        },
                        stumbleupon: {
                          title: "StumbleUpon",
                          url: "http://www.stumbleupon.com/submit?url=" + page + "&title=" + doctitle
                        },
                        tumblr: {
                          title: "Tumblr",
                          url: "https://www.tumblr.com/widgets/share/tool?canonicalUrl=" + page + "&title=" + doctitle
                        }
                      };
              if (o.sharetitle) {
                sWrap.append('<span class="title">' + o.sharetitle + '</span>');
                sharetitle = o.sharetitle + ' on ';
              }
              o.share.map(function (i) {
                sWrap.buttonize(sharelinks[i].url, sharetitle + sharelinks[i].title, [
                  sharelinks[i].title.toLowerCase(),
                  o.buttonclass,
                  'icon'
                ]);
              });
              $obj.append(sWrap);
            }
            if (Object.keys(o.follow) !== 'undefined') {
              var fWrap = $('<div class="jSocial-follow" />'),
                      followtitle = ''
                      /*
                       facebook: {
                       title: "Facebook",
                       url: "https://facebook.com"
                       },
                       google: {
                       title: "Google",
                       url: "https://plus.google.com"
                       },
                       twitter: {
                       title: "Twitter",
                       url: "https://twitter.com"
                       },
                       linkedin: {
                       title: "LinkedIn",
                       url: "https://linkedin.com"
                       },
                       pinterest: {
                       title: "Pinterest",
                       url: "https://pinterest.com"
                       },
                       yelp: {
                       title: "Yelp",
                       url: "https://yelp.com"
                       }*/;
              if (o.followtitle) {
                fWrap.append('<span class="title">' + o.followtitle + '</span>');
                followtitle = o.followtitle + ' on ';
              }
              $.each(o.follow, function () {
                fWrap.buttonize(this.url, followtitle + this.title, [
                  this.title.replace(/ /g, '').toLowerCase(),
                  o.buttonclass,
                  'icon'
                ]);
              });
              $obj.append(fWrap);
            }
          });
        };
        /**
         * Init jSocial
         */
        fn.init = function () {
// Generate markup for links.
          fn.style(jQuery(this));
        };
        return this.each(fn.init);
      };
      /**
       * jTabs : Tabify a list of content
       */
      cellular.jTabs = function (opts) {
        var o = jQuery.extend({
          active: 0, // Array index of initially active tab
          orient: "horizontal", // || "vertical"
          cclass: "jTabs"
        }, opts),
                fn = {};
        /**
         *
         *
         * @param object $obj
         * @param object li
         */
        fn.showContent = function ($obj, li) {
          var content = li.find('.content'),
                  pan = $obj.parent().find('.panel-content');
          li.activate();
          pan.fadeOut('normal', function () {
            jQuery(this).html(content.html())
                    .fadeIn('normal');
          });
        };
        /**
         * Init jTabs
         */
        fn.init = function () {
          var $obj = jQuery(this),
                  tab = $obj.find('> li'),
                  wrap = jQuery('<div/>').classify([
            o.orient,
            o.cclass + '-wrap'
          ]),
                  panel = '<div class="panel"><div class="panel-content" /></div>';
          $obj.once(o.cclass, function () {
            $obj.wrap(wrap)
                    .after(panel);
            tab.each(function () {
              var li = jQuery(this);
              li.addClass('tab')
                      .kidWrap();
//Set 1st child as title
              li.children().eq(0).addClass('title');
//Set wrapper as content
              li.children().eq(1).addClass('content')
                      .hide();
            });
          });
//Add classes/functions to each panel
          tab.each(function () {
            var li = jQuery(this);
            li.click(function (e) {
              e.preventDefault();
              fn.showContent($obj, li);
            });
          });
//Set default content
          fn.showContent($obj, tab.eq([o.active]));
        };
        return this.each(fn.init);
      };
      cellular.jModal = function (opts) {
        var o = jQuery.extend({
          cclass: "jModal",
          dataattr: "data-modal",
          groupattr: "data-album",
          offsetX: 10, // % or vw
          offsetY: 10, // % or vh
//caption: "data-caption",
//timeout: 10000,
//fitImg: true, // Scale images to user viewport.
          trigger: "click"
        }, opts),
                fn = {};
        /**
         *
         */
        fn.load = function ($obj, state) {
          var win = jQuery('.' + o.cclass + '-window'),
                  overlay = jQuery('#' + o.cclass + '-overlay'),
                  contentpane = win.find('.' + o.cclass + '-content'),
                  content;
// show loading icon
          state.active = true;
          overlay.activate();
// determine content source
          if (typeof ($obj.attr(o.dataattr)) !== 'undefined') {
            content = $obj.attr(o.dataattr);
          } else if ($obj.attr('href') !== 'undefined') {
            content = $obj.attr('href');
          }
// load content
          $.ajax({
            url: content,
            context: document.body,
            timeout: o.timeout,
            success: function (data) {
              console.log(data);
// Remove loading icon
// Re-position/re-size window to fit content
              win.css({
                height: 100 - (o.offsetY * 2) + 'vh',
                width: 100 - (o.offsetX * 2) + 'vw',
                top: o.offsetY + 'vh',
                left: o.offsetX + 'vw',
              });
// Show content
              contentpane.html(data)
                      .activate();
            },
            error: function (jqXHR, textStatus) {
              state.activate = false;
              overlay.deactivate();
              console.log("AJAX Request failed: " + textStatus);
            }
          });
        };
        fn.close = function (state) {
          var modal = jQuery('#' + o.cclass + '-overlay');
          state.active = false;
          modal.deactivate()
                  .find('.' + o.cclass + '-window').deactivate();
          modal.find('.' + o.cclass + '-content').deactivate()
                  .html('');
        };
        /**
         * Generate markup for controls & other elements.
         *
         * @param object $obj
         */
        fn.style = function ($obj) {
          var modal = jQuery('<div class="' + o.cclass + '-window" />')
                  .append('<div class="' + o.cclass + '-content" />')
                  .append('<span class="' + o.cclass + '-close" aria-label="Close" />'),
                  overlay = jQuery('<div id="' + o.cclass + '-overlay" />').append(modal);
          if (!jQuery('#' + o.cclass + '-overlay').length) {
            jQuery('body').append(overlay);
          }
        };
        /**
         *
         */
        fn.events = function ($obj, state) {
          $obj.on('click', function (e) {
            e.preventDefault();
            fn.load($obj, state);
          });
          jQuery(document).on('keyup', function (e) {
            if (state.active === true && e.which === 27) {
              fn.close(state);
            }
          });
          jQuery('#' + o.cclass + '-overlay, .' + o.cclass + '-close').on('click', function () {
            fn.close(state);
          });
        };
        /**
         * Init jModal
         */
        fn.init = function () {
          var $obj = jQuery(this),
                  state = {
                    active: false,
                    group: o.groupattr.length ? o.groupattr : null
                  };
// Generate markup for modal
          jQuery('.' + o.cclass).once(o.cclass, fn.style($obj));
// Listen for events
          fn.events($obj, state);
        };
        return this.each(fn.init);
      };
      jQuery.fn.extend(cellular);
//Drupal.behaviors.cellular = {
//attach: function (context, settings) {
    }
  };
})(jQuery);