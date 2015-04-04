cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    "breakpoint": cellular.opts.breakpoint, // Window breakpoint trigger
    "parent": jQuery('body'),
    "cclass": "jMmenu",
    "type": "slide",
    "direction": "right"
  }, opts);
  var fn = {};

  fn.classes = [
    o.type + '-' + o.direction,
    o.cclass + '-active',
    o.cclass + '-inactive'
  ];

  fn.mediaQuery = function ($obj) {
    //
    var $parent,
      classes,
      $menu = $obj.children([0]);

    // console.log($menu);

    if (window.innerWidth <= o.breakpoint) {
      $parent = o.parent;
      classes = [
        fn.classes[0],
        fn.classes[2]
      ];
      classes = classes.join(' ');
      if (o.parent.hasClass(fn.classes[0])) {
        // Skip if already set.
      }
      else {
        o.parent.addClass(classes);
        $menu.addClass(o.cclass);
      }
    }

    $menu.prependTo($parent);
  };

  return this.each(function () {
    var $obj = jQuery(this);
    var $window = jQuery(window);

    fn.mediaQuery($obj);
    $window.resize(function () {
      $window.throttle(fn.mediaQuery($obj), 250);
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