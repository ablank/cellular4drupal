cellular.activate = function () {
  return this.each(function () {
    var $t = jQuery(this);

    if ($t.hasClass('active')) {
      return;
    } else {
      $t.addClass('active')
        .siblings().removeClass('active');
    }
  });
};

cellular.deactivate = function () {
  return this.each(function () {
    var $t = jQuery(this);
    if ($t.hasClass('active')) {
      $t.removeClass('active');
    }
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
    var $t = jQuery(this);
    var classes = $array.join(' ');

    $t.addClass(classes);
  });
};

cellular.throttle = function (fn, delay) {
  var timer = null;

  delay = delay ? delay : 250;

  return function () {
    var context = this, args = arguments;
    clearTimeout(timer);
    timer = setTimeout(function () {
      fn.apply(context, args);
    }, delay);
  };
};

cellular.cycle = function (dir) {
  var $obj = jQuery(this),
    kids = $obj.children(),
    count = -1,
    next;

  if (dir === "next") {
    next = kids.next();
    if (next.length < 1) {
      next = kids[count += 1 % kids.length];
    }
  }

  if (dir === "prev") {
    next = kids.prev();
    if (next.length < 1) {
      next = kids[kids.length];
    }
  }

  return next;
};
