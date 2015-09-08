
cellular.breakpoint = function () {
  var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content'),
    mq = {
      size: content.match(/\d/g).join(""),
      type: content.match(/\w*[^\"\'](?=-)/g).join("")
    };

  return mq;
};

cellular.activate = function () {
  return this.each(function () {
    var $t = jQuery(this);

    if (!$t.hasClass(cellular.opts.activeclass)) {
      $t.addClass(cellular.opts.activeclass)
        .siblings().removeClass(cellular.opts.activeclass);
    }
  });
};

cellular.deactivate = function () {
  return this.each(function () {
    jQuery(this).removeClass(cellular.opts.activeclass);
  });
};

cellular.kidWrap = function () {
  // Wrap element's children with index gt 0
  return this.each(function () {
    var $t = jQuery(this);

    if ($t.children().length > 1) {
      $t.children(':gt(0)').wrapAll('<div>');
    }
  });
};

cellular.classify = function ($array) {
  // Add array of classes to element
  return this.each(function () {
    jQuery(this).addClass($array.join(' '));
  });
};

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

cellular.throttle = function (fn, delay) {
  return this.each(function () {
    var timer = null,
      context = this,
      args = arguments;
    ;

    delay = delay ? delay : 250;

    clearTimeout(timer);
    timer = setTimeout(function () {
      fn.apply(context, args);
    }, delay);
  });
};
*/