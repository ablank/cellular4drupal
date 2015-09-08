cellular.jScrolli = function (opts) {
  var o = $.extend({
    cclass: 'jScrolli', // Object class selector
    active: 0, // Index of initially selected slide
    size: {
      //width: 700,
      height: 'auto' // 'auto' or '[value]', i.e. '300px'
    },
    controls: {
      events: 'click touchend MSPointerUp',
      showcontrols: true,
      showmarkers: true,
      autoplay: true,
      pauseonhover: true,
      text: {
        next: 'Next',
        prev: 'Prev',
        pause: 'Pause'
      }
    },
    transition: {
      function: 'fn.slide', // 
      pause: 5, // Time (seconds) to pause between slides.
      speed: 500 // Animation speed (milliseconds).

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
    state.caption = $obj.parent().find(o.caption.selector).eq(state.current).html();
    $obj.parent().parent().find('> .caption').html(state.caption);
  };

  fn.autoheight = function ($obj, state) {
    if (o.size.height === 'auto') {
      $obj.height(state.maxheight);
    } else {
      $obj.height(o.size.height);
    }
  };

  // Generate markup
  fn.style = function ($obj, state) {
    var slides = $obj.find('> li');

    $obj.addClass(cellular.opts.cclass)
      .wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />');

    if (o.caption.enable) {
      if (o.caption.selector === 'auto') {
        // o.caption.selector =
      }
      else {
        $obj.find(o.caption.selector).hide();
      }

      $obj.before('<div class="caption" />');
    }
    
    slides.each(function () {
      var $t = jQuery(this);

      $t.addClass('slide')
        .children().wrapAll('<div class="wrap" />');

      fn.autoheight($t, state);
    });

    fn.autoheight($obj, state);

    if (o.controls.showmarkers) {
      var markers = jQuery('<div class="markers"><ul></ul></div>');
      for (var i = 0; i < slides.length; i += 1) {
        var index = i;
        markers.find('ul')
          .append('<li class="marker" data-href="' + index + '">' + (index + 1) + '</li>');
      }
      $obj.after(markers);
      fn.mark($obj, state);
    }

    if (o.controls.showcontrols) {
      var controls = [
        fn.button(o.controls.text.pause),
        fn.button(o.controls.text.prev),
        fn.button(o.controls.text.next)
      ];

      $obj.after('<div class="controls">' + controls[0] + controls[1] + controls[2] + '</div>');
    }
  };

  fn.updateinterval = function ($obj, state) {
    clearInterval(state.interval);
    state.interval = setInterval(function () {
      state.current = state.next;
      fn.go(state.current, $obj, state);
    }, o.transition.pause * 1000);
  };

  // Auto-increment to next slide
  fn.autoplay = function ($obj, state) {
    if (!state.paused) {
      fn.updateinterval($obj, state);
      /*
       state.interval = setInterval(function () {
       state.current = state.next;
       fn.go(state.current, $obj, state);
       }, o.transition.pause * 1000);
       */
    }
  };

  // Add Event Listeners
  fn.events = function ($obj, state) {
    var controls = $obj.siblings('.controls'),
      $i = $obj.find('> li'),
      wrap = $obj.parent(),
      eX = null,
      eY = null;

    // Previous
    controls.find('.prev').on(o.controls.events, function (e) {
      state.current = state.prev;
      state.paused = false;
      fn.go(state.current, $i, state);
    });
    // Next
    controls.find('.next').on(o.controls.events, function (e) {
      state.current = state.next;
      state.paused = false;
      fn.go(state.current, $i, state);
    });
    /*
     // Pause
     controls.find('.pause').on(o.controls.events, function (e) {
     state.paused = state.paused ? false : true;
     state.active = state.active ? ;
     console.log(state.paused);
     });
     */
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
      },
      'touchstart': function (e) {
        eX = e.touches[0].clientX;
        eY = e.touches[0].clientY;
        state.active = true;
      },
      'touchmove': function (e) {
        if (!eX || !eY) {
          return;
        }
        var margin = 20,
          Xdiff = eX - (e.touches[0].clientX),
          Ydiff = eY - (e.touches[0].clientY);

        // Detect horizontal or vertical swipe
        if (Math.abs(Xdiff) > Math.abs(Ydiff)) {
          // Horizontal (left : right)
          state.current = Xdiff > margin ? state.prev : state.next;
        } else {
          // Vertical (up : down)
          state.current = Ydiff > margin ? state.prev : state.next;
        }
        // Reset vars for next swipe
        eX = null;
        eY = null;
        state.active = false;
        // Move to next slide
        fn.go(state.current, $i, state);
      }
    });

    // Link markers to respective slides
    if (o.controls.showmarkers) {
      $obj.siblings().find('.marker').on('click', function () {
        state.current = jQuery(this).attr('data-href');
        state.paused = false;
        fn.go(state.current, $i, state);
      });
    }

    if (state.active) {
      jQuery(document).on('keyup', function (e) {
        console.log(e.which);
        var keys = [
          37, // left
          38, // up
          39, // right
          40 // down
        ];

        if (keys.indexOf(e.which) !== -1) {
          console.log(e.which);
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

          fn.go(state.current, $i, state);
        }
      });
    }
  };

  fn.init = function () {
    var $obj = jQuery(this),
      $i = $obj.find('> li'),
      state = {
        active: true,
        paused: false,
        animating: false,
        count: $i.length - 1,
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

    $i.each(function () {
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
    fn.go(state.current, $i, state);
    // Start autoplay
    if (o.controls.autoplay) {
      fn.autoplay($i, state);
    }
  };

  return this.each(fn.init);
};