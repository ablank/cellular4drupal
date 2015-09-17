/**
 * jScrolli : Content carousel/slider
 */

cellular.jScrolli = function (opts) {
  var o = $.extend({
    cclass: 'jScrolli', // Object class selector
    active: 0, // Index of initially selected slide
    //activeSlides: 1,
    size: {
      //width: 700,
      height: 'auto' // 'auto' or '[value]', i.e. '300px'
    },
    controls: {
      showcontrols: true,
      keyboard: true,
      swipe: true,
      showmarkers: true,
      autoplay: true,
      pauseonhover: true,
      events: 'click mouseup MSPointerUp touchend',
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
    delay: 1.4 // Time (seconds) to wait before dimming.
  }, opts);

  var fn = {};

  fn.button = function ($text) {
    return '<a class="control ' + $text.toLowerCase() + '">' + $text + '</a>';
  };

  // Update next/prev slides.
  fn.normalize = function ($obj, state) {
    /*
     state.prev = state.current - o.activeSlides;
     state.next = state.current + o.activeSlides;
     */
    state.prev = state.current - 1;
    state.next = state.current + 1;
    if (state.prev < 0) {
      state.prev = state.count;
    }
    if (state.next > state.count) {
      state.next = 0;
    }
    // state.interval = 0;
  };

  // Activate selected slide & corresponding marker
  fn.go = function (index, $obj, state) {
    if (!state.paused) {
      var tclass = 'transition';
    console.log(state.current);

      $obj.parent().parent().addClass(tclass)
        .one(cellular.transitionend(), function () {
          jQuery(this).removeClass(tclass);
        });
      // Normalize state
      fn.normalize($obj, state);
      // Update the marker
      if (o.controls.showmarkers) {
        fn.mark($obj, state);
      }
      // Update the caption
      if (o.caption.enable) {
        fn.caption($obj, state);
      }
      if (o.controls.autoplay) {
        // Reset the transition timer for autoplay
        fn.updateinterval($obj, state);
      }
      // Update classes on slides for css transition
      jQuery($obj[state.prev]).addClass('previous')
        .siblings().removeClass('previous');
      jQuery($obj[state.next]).addClass('next')
        .siblings().removeClass('next');
      jQuery($obj[index]).activate()
        .removeClass('previous next');
    }
  };

  // Activate the slide marker
  fn.mark = function ($obj, state) {
    $obj.parent().parent().find('.marker')
      .eq(state.current).activate();
  };

  // Update slide caption
  fn.caption = function ($obj, state) {
    var wrap = $obj.parent().parent(),
      cap = wrap.find('> .caption p');
    // Get current slide's caption
    state.caption = wrap.find(o.caption.selector).eq(state.current).text();
    // Update the active caption
    cap.text(state.caption);
  };

  // Calculate largest dimension to prevent 'jumping' content
  fn.setheight = function ($obj, state) {
    if (o.size.height === 'auto') {
      jQuery(window).on('load', function () {
        $obj.find('.slide').each(function () {
          var height = jQuery(this).height();
          //console.log(h);
          if (height > state.maxheight) {
            state.maxheight = height;
          }
        });
      });
    }
    else {
      state.maxheight = o.size.height;
    }

    //console.log(state.maxheight);

    $obj.parent().height(state.maxheight);
  };

  // Generate markup
  fn.style = function ($obj, state) {
    var slides = $obj.find('> li');

    $obj.addClass(cellular.opts.cclass)
      .wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />');

    if (o.controls.showmarkers) {
      var markers = jQuery('<div class="markers"><ul></ul></div>');
      for (var i = 0; i < slides.length; i += 1) {
        markers.find('ul')
          .append('<li class="marker" data-href="' + i + '">' + (i + 1) + '</li>');
      }
      $obj.after(markers);
      fn.mark($obj, state);
    }

    if (o.caption.enable) {
      if (o.caption.selector === 'auto') {
        // o.caption.selector = what?
      }
      else {
        $obj.find(o.caption.selector).hide();
      }

      $obj.after('<div class="caption"><p/></div>');
    }

    if (o.controls.showcontrols) {
      var controls = [
        fn.button(o.controls.text.pause),
        fn.button(o.controls.text.prev),
        fn.button(o.controls.text.next)
      ];

      $obj.parent().prepend(controls[0] + controls[1] + controls[2]);
    }

    slides.each(function () {
      jQuery(this).addClass('slide');
      // .children().wrapAll('<div class="wrap" />');
    });

    fn.setheight($obj, state);
  };

  fn.updateinterval = function ($obj, state) {
    if (!state.paused) {
      clearInterval(state.interval);
      state.interval = setInterval(function () {
        state.current = state.next;
        fn.go(state.current, $obj, state);
      }, o.transition.pause * 1000);
    }
  };

  // Add Event Listeners
  fn.events = function ($obj, state) {
    var controls = $obj.siblings('.controls'),
      li = $obj.find('> li'),
      wrap = $obj.parent(),
      eX = null,
      eY = null;

    // Previous
    wrap.find('.prev').on(o.controls.events, function (e) {
      state.current = state.prev;
      state.paused = false;
      fn.go(state.current, li, state);
    });

    // Next
    wrap.find('.next').on(o.controls.events, function (e) {
      state.current = state.next;
      state.paused = false;
      fn.go(state.current, li, state);
    });
    // Pause
    wrap.find('.pause').on(o.controls.events, function (e) {
      if (state.paused) {
        state.paused = false;
        fn.updateinterval($obj, state);
      }
      else {
        state.paused = true;
        clearInterval(state.interval);
      }
      $(this).toggleClass('play');
      //console.log(state.paused);
    });

    // Link markers to respective slides
    if (o.controls.showmarkers) {
      $obj.siblings().find('.marker').on('click', function () {
        state.current = jQuery(this).attr('data-href');
        state.paused = false;
        fn.go(state.current, li, state);
      });
    }

    // Pause/showcontrols
    wrap.on({
      'mouseover': function () {
        state.active = true;
        o.controls.pauseonhover ? state.paused = true : null;
        if (o.autodim)
          wrap.activate();
        window.clearTimeout(wrap.timeout);
      },
      'mouseout': function () {
        state.active = false;
        o.controls.pauseonhover ? state.paused = false : null;
        o.autodim ? wrap.timeout = window.setTimeout(function () {
          wrap.deactivate();
        }, o.delay * 1000) : null;
      }
    });

    // Keyboard
    if (o.controls.keyboard) {
      jQuery(document).on('keyup', function (e) {
        // console.log(e.which);
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

          fn.go(state.current, li, state);
        }
      });
    }

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
          fn.go(state.current, li, state);
        }
      });
    }

  };

  fn.init = function () {
    var $obj = jQuery(this),
      li = $obj.find('> li'),
      state = {
        active: true,
        paused: false,
        count: li.length - 1,
        width: $obj.width(),
        maxheight: 0,
        interval: 0,
        controls: 0,
        caption: jQuery(o.caption.selector).html(),
        current: o.active ? o.active : 0
      };

    state.prev = state.current - 1;
    state.next = state.current + 1;

    o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;

    li.each(function () {
      var $t = jQuery(this);
      // Set maxheight equal to greatest element.
      if ($t.height() > state.maxheight) {
        state.maxheight = $t.height();
      }
    });
    // Add markup
    $obj.once(o.cclass, function () {
      fn.style($obj, state);
    });
    // Add Event Listeners
    fn.events($obj, state);
    // Activate 1st slide
    fn.go(state.current, li, state);
    // Start autoplay
    if (o.controls.autoplay) {
      fn.updateinterval(li, state);
    }
  };

  return this.each(fn.init);
};