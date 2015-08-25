cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger
    parent: jQuery('body'), // Parent element used to attach menu
    cclass: "jMmenu", // Menu class to test
    type: "slide", // Type of animation
    direction: "right" // Direction of animation
  }, opts),
    fn = {
      classes: [
        o.type + '-' + o.direction,
        o.cclass + '-active',
        o.cclass + '-inactive'
      ]
    };

  fn.mediaQuery = function ($obj) {
    if (o.breakpoint === cellular.breakpoint().type) {
      var $menu = $obj.children([0]),
        classes = [
          fn.classes[0],
          fn.classes[2]
        ];

      if (!o.parent.hasClass(fn.classes[0])) {
        o.parent.addClass(classes.join(' '));
        $menu.addClass(o.cclass);
      }
      $menu.prependTo(o.parent);
    }
  };

  return this.each(function () {
    var $obj = jQuery(this);
    var $window = jQuery(window);

    fn.mediaQuery($obj);
    $window.on('resize', function () {
      fn.mediaQuery($obj);
    });

    $obj.on('click', function () {
      if (o.parent.hasClass(fn.classes[0])) {
        o.parent.toggleClass(fn.classes[1])
          .toggleClass(fn.classes[2]);
        $obj.toggleClass('active');
      }
    });
  });
};