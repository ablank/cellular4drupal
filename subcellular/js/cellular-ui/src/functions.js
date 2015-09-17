/**
 * Cellular utility functions
 */

// Get the breakpoints specified in CSS
cellular.breakpoint = function () {
  var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content');

  return {
    size: content.match(/\d/g).join(""),
    type: content.match(/\w*[^\"\'](?=-)/g).join("")
  };
};

// Add active class to element, remove active class from element siblings
cellular.activate = function () {
  return this.each(function () {
    var $t = jQuery(this);

    if (!$t.hasClass(cellular.opts.activeclass)) {
      $t.addClass(cellular.opts.activeclass)
        .siblings().removeClass(cellular.opts.activeclass);
    }
  });
};

// Remove 'active' class
cellular.deactivate = function () {
  return this.each(function () {
    jQuery(this).removeClass(cellular.opts.activeclass);
  });
};

// Wrap element's children after 1st child
cellular.kidWrap = function () {
  return this.each(function () {
    var $t = jQuery(this);

    if ($t.children().length > 1) {
      $t.children(':gt(0)').wrapAll('<div>');
    }
  });
};

// Add array of classes to element
cellular.classify = function ($array) {
  return this.each(function () {
    jQuery(this).addClass($array.join(' '));
  });
};

// Underscore's debounce fn
cellular.debounce = function (func, wait, immediate) {
  var timeout;
  return function () {
    var context = this,
      args = arguments,
      later = function () {
        timeout = null;
        if (!immediate)
          func.apply(context, args);
      },
      callNow = immediate && !timeout;

    clearTimeout(timeout);
    timeout = setTimeout(later, wait);
    if (callNow)
      func.apply(context, args);
  };
};

// Set state on window resize
cellular.windowstate = cellular.debounce(function () {
  cellular.state.breakpoint = cellular.breakpoint().type;
// console.log(cellular.state);
}, 500);

// Set state on document scroll
cellular.docstate = cellular.debounce(function () {
  var el = jQuery('body'),
    cclass = 'scrolled';
  cellular.state.scrolltop = $(document).scrollTop();

  if(cellular.state.scrolltop > 0){
    el.addClass(cclass);
  }
  else {
    el.removeClass(cclass);
  }
// console.log(cellular.state);
}, 20);
/*
 cellular.whichTransitionEvent = function () {
 // Thanks Modernizr :)
 var t,
 el = document.createElement('fakeelement'),
 transitions = {
 transition: 'transitionend',
 OTransition: 'oTransitionEnd',
 MozTransition: 'transitionend',
 WebkitTransition: 'webkitTransitionEnd'
 };

 for (t in transitions) {
 if (el.style[t] !== undefined) {
 return transitions[t];
 }
 }
 };

 // Listen for a transition!
 var transitionEvent = whichTransitionEvent();
 transitionEvent && e.addEventListener(transitionEvent, function () {
 console.log('Transition complete!  This is the callback, no library needed!');
 });
 */

/*
 The "whichTransitionEvent" can be swapped for "animation" instead of "transition" texts, as can the usage :)
 */

/*
 cellular.autodimension = function ($obj, dimension) {
 return this.each(function () {
 var $t = jQuery(this),
 max = 0;


 if ($obj === 'auto') {
 $t.height(state.maxheight);
 } else {
 $t.height(o.size.height);
 }
 });
 };
 */