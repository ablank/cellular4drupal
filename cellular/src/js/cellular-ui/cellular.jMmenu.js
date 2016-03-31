/**
 * jMmenu: Hamburger menu for mobile devices
 */

cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
    parent: jQuery('body'), // Parent element used to attach menu
    cclass: "jMmenu", // Menu class to test
    triggertext: "Menu",
    animateclass: "slide-right", // Type of animation
    throttle: 101 // Time in ms to throttle window resize event
  }, opts),
          fn = {};

  fn.mediaQuery = cellular.debounce(function ($obj, state) {
    if (o.breakpoint === cellular.state.breakpoint) {
      var $menu = $obj.children([0]),
              label = null;

      state.mmenu = true;
      o.parent.addClass(o.animateclass);
      if (o.triggertext) {
        label = '<span class="' + o.cclass + '-triggertext">' + o.triggertext + '</span>';
      }
      $obj.addClass(o.cclass + '-trigger')
              .append(label);

      $menu.addClass(o.cclass + '-menu')
              .prependTo(o.parent);
    } else {
      state.mmenu = false;
      state.active = false;
      o.parent.removeClass(
              o.cclass + '-active ' +
              o.cclass + '-inactive ' +
              o.animateclass
              );
      $obj.attr('aria-label', "Menu")
              .removeClass(o.cclass + '-trigger');
      jQuery('.' + o.cclass + '-menu').removeClass(o.cclass + '-menu')
              .prependTo($obj);
      jQuery('.' + o.cclass + '-triggertext').remove();
    }
    fn.trigger($obj, state);
  }, o.throttle);

  fn.trigger = function ($obj, state) {
    var classes = [
      o.cclass + '-active',
      o.cclass + '-inactive'
    ];

    if (state.active) {
      $obj.activate()
              .attr('aria-label', "Close Menu");
      jQuery('.' + o.cclass + '-menu').addClass('active');
      o.parent.addClass(classes[0])
              .removeClass(classes[1]);
    } else {
      $obj.deactivate()
              .attr('aria-label', "Open Menu");
      jQuery('.' + o.cclass + '-menu').removeClass('active');
      if (state.mmenu) {
        o.parent.addClass(classes[1])
                .removeClass(classes[0]);
      }
    }
  };

  fn.init = function () {
    var $obj = jQuery(this),
            state = {
              active: false,
              mmenu: false
            };

    fn.mediaQuery($obj, state);

    jQuery(window).on('resize', function () {
      fn.mediaQuery($obj, state);
    });

    $obj.on('click', function () {
      //console.log(this);
      if (state.mmenu) {
        state.active = state.active ? false : true;
        fn.trigger($obj, state);
      }
    });

    jQuery(document).on('keyup', function (e) {
      if (state.active === true && e.which === 27) {
        e.preventDefault();
        state.active = false;
        fn.trigger($obj, state);
      }
    });
  };

  return this.each(fn.init);
};
