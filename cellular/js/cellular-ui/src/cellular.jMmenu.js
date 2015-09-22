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

  fn.mediaQuery = cellular.debounce(function ($obj, state) {
    if (o.breakpoint === cellular.state.breakpoint) {
      var $menu = $obj.children([0]);

      o.parent.addClass(o.type + '-' + o.direction);
      $menu.addClass(o.cclass)
        .prependTo(o.parent);

      fn.trigger($obj, state);
    }
  }, 500);

  fn.trigger = function ($obj, state) {
    var classes = [
      o.cclass + '-active',
      o.cclass + '-inactive'
    ];
    
    if (state.active) {
      $obj.activate();
      o.parent.addClass(classes[0])
        .removeClass(classes[1]);
    }
    else {
      $obj.deactivate();
      o.parent.addClass(classes[1])
        .removeClass(classes[0]);
    }
  };

  fn.init = function () {
    var $obj = jQuery(this),
      state = {
        active: false
      };

    fn.mediaQuery($obj, state);

    jQuery(window).on('resize', function () {
      fn.mediaQuery($obj, state);
    });

    $obj.on('click', function () {
      state.active = state.active ? false : true;
      fn.trigger($obj, state);
    });
  };

  return this.each(fn.init);
};