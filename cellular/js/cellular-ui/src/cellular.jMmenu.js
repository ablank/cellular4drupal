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
  }, opts);

  o.classes = [
    o.type + '-' + o.direction,
    o.cclass + '-active',
    o.cclass + '-inactive'
  ];

  fn = {};

  fn.mediaQuery = cellular.debounce(function ($obj) {
    if (o.breakpoint === cellular.state.breakpoint) {
      var $menu = $obj.children([0]);

      if (!o.parent.hasClass(o.classes[0])) {
        o.parent.classify([o.classes[0], o.classes[2]]);
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
    });

    $obj.on('click', function () {
      if (o.parent.hasClass(o.classes[0])) {
        $obj.toggleClass(cellular.opts.activeclass);
        o.parent.toggleClass(o.classes[1] + ' ' + o.classes[2]);
      }
    });
  };

  return this.each(fn.init);
};