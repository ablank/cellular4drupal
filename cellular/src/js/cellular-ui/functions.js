/**
 * Cellular utility functions
 */

/**
 * Get the breakpoints specified in CSS
 */
cellular.breakpoint = function () {
  var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content'),
    obj;

  if (content) {
    obj = {
      size: content.match(/\d/g).join(""),
      type: content.match(/\w*[^\"\'](?=-)/g).join("")
    };
  } else {
    // Provide default breakpoints if they aren't set by css.
    var ww = jQuery(window).width(),
      ssize = [
        ''
      ];
    switch (ww) {
      case ww > 650 && ww < 800:
        //console.log(ww);

        obj = {
          size: '',
          type: ''
        };
        break;
      default:

        obj = {
          size: '',
          type: ''
        };
        break;
    }
  }

  return obj;
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