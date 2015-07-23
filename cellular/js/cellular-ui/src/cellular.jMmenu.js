cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger
    parent: jQuery('body'),
    cclass: "jMmenu",
    type: "slide",
    direction: "right"
  }, opts),
    fn = {
      classes: [
        o.type + '-' + o.direction,
        o.cclass + '-active',
        o.cclass + '-inactive'
      ]
    };

  fn.mediaQuery = function ($obj) {
    if (o.breakpoint === 'mobile') {
      var classes = [
        fn.classes[0],
        fn.classes[2]
      ],
        $menu = $obj.children([0]);

      classes = classes.join(' ');
      if (o.parent.hasClass(fn.classes[0])) {
        // Skip if already set.
      }
      else {
        o.parent.addClass(classes);
        $menu.addClass(o.cclass);
      }
      // console.log($obj);
      // console.log('breakpoint: '+o.breakpoint);

      $menu.prependTo(o.parent);
    }
  };

  return this.each(function () {
    var $obj = jQuery(this);
    var $window = jQuery(window);

    fn.mediaQuery($obj);
    $window.resize(function () {
      $window.throttle(fn.mediaQuery($obj));
    });

    $obj.click(function () {
      if (o.parent.hasClass(fn.classes[0])) {
        o.parent.toggleClass(fn.classes[1])
          .toggleClass(fn.classes[2]);
        $obj.toggleClass('active');
      }
    });
  });
};