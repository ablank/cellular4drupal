/**
 * jScrolli : Content carousel/slider
 */

cellular.jScrolli = function (opts) {
  var o = $.extend({
    cclass: "jScrolli", // Object class selector
    active: 0, // Index of initially selected slide
    //width: 0,
    height: "auto", // 'auto' or '[value]', i.e. '300px'
    controls: {
      showmarkers: true,
      showcontrols: true,
      keyboard: true,
      swipe: true,
      autoplay: true,
      pauseonhover: true,
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
      selector: ".caption" // 'auto' or '.selector' used to generate caption
    },
    autodim: true,
    delay: 1.4 // Time (seconds) to wait before dimming.
  }, opts),
    fn = {};

  /**
   * Format html buttons for controls.
   *
   * @param string $text
   * @returns string
   */
  fn.button = function ($text) {
    return '<a class="control ' + $text.toLowerCase() + '">' + $text + '</a>';
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
        li = $obj.find('.slide');
      state.current = parseInt(index);
      // Normalize state
      fn.normalize(state);
      // Update classes on slides for css transition
      jQuery(li[state.prev]).activate('previous');
      jQuery(li[state.next]).activate('next');
      jQuery(li[index]).activate();
      // Listen for transition to complete & update classes
      $obj.parent().addClass(tclass)
        .one(cellular.transitionend(), function () {
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
    $obj.siblings().find('.marker')
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
    // Update the active caption
    cap.text(state.caption);
  };
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
      $obj.siblings().find('.marker').on('click', function () {
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
    jQuery(window).on('load', function () {
      if (o.height === 'auto') {
        $obj.find('.panel').each(function () {
          var tHeight = jQuery(this).height();

          if (tHeight > state.maxheight) {
            state.maxheight = tHeight;
          }
        });
      }
      else {
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

    $obj.addClass(cellular.opts.cclass)
      .wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />');

    li.addClass('slide')
      .each(function () {
        jQuery(this).children().wrapAll('<div class="panel" />');
      });

    fn.setheight($obj, state);
    if (o.controls.showmarkers) {
      var markers = jQuery('<ul class="markers"/>');
      for (var i = 0; i < li.length; i += 1) {
        markers.append('<li class="marker" data-href="' + i + '">' + (i + 1) + '</li>');
      }
      $obj.after(markers);
      fn.mark($obj, state);
    }

    if (o.caption.enable) {
      /*
       if (o.caption.selector === 'auto') {
       // o.caption.selector = what?
       }
       else {
       $obj.find(o.caption.selector).hide();
       }
       */
      $obj.find(o.caption.selector).hide();
      $obj.after('<div class="caption"><p/></div>');
    }

    if (o.controls.showcontrols) {
      var controls = [
        fn.button(o.controls.text.prev),
        fn.button(o.controls.text.next),
        //o.autoplay ? fn.button(o.controls.text.pause) : null
      ], i = 0;
      for (i; i < controls.length; i += 1) {
        $obj.parent().prepend(controls[i]);
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
