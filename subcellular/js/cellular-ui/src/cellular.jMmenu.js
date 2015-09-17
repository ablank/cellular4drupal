/**
 * jMmenu: Hamburger menu for mobile devices
 */

cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
    parent: jQuery('body'), // Parent element used to attach menu
    cclass: "jMmenu", // Menu class to test
    type: "slide", // Type of animation
    direction: "right" // Direction of animation
  }, opts),
    fn = {};

  fn.classes = [
    o.type + '-' + o.direction,
    o.cclass + '-active',
    o.cclass + '-inactive'
  ];

  fn.mediaQuery = cellular.debounce(function ($obj) {
    if (o.breakpoint === cellular.state.breakpoint) {
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
  }, 500);

  fn.init = function () {
    var $obj = jQuery(this);

    fn.mediaQuery($obj);
    jQuery(window).on('resize', function () {
      fn.mediaQuery($obj);
      // console.log(cellular.breakpoint());
    });

    $obj.on('click', function () {
      if (o.parent.hasClass(fn.classes[0])) {
        o.parent.toggleClass(fn.classes[1])
          .toggleClass(fn.classes[2]);
        $obj.toggleClass(cellular.opts.activeclass);
      }
    });
  };

  return this.each(fn.init);
};