/**
 * jMmenu: Hamburger menu for mobile devices
 */

cellular.jMmenu = function (opts) {
  var o = jQuery.extend({
    breakpoint: cellular.opts.breakpoint, // 'window_small'|| 'window_narrow' || 'window_default'
    parent: jQuery('body'), // Parent element used to attach menu
    cclass: "jMmenu", // Menu class to test
    triggertext: "Menu",
    animateclass: "slide-right", // Type of animation
    throttle: 101 // Time in ms to throttle window resize event
  }, opts),
    fn = {};

  fn.mediaQuery = cellular.debounce(function ($obj, state) {
    //console.log(cellular.opts.breakpoint);
    if (o.breakpoint === cellular.state.breakpoint) {
      var $menu = $obj.children([0]),
        label = null;

      state.mmenu = true;
      o.parent.addClass(o.animateclass);
      if (o.triggertext) {
        label = '<span class="' + o.cclass + '-triggertext">' + o.triggertext + '</span>';
      }
      $obj.prop("tabindex", "0")
        .addClass(o.cclass + '-trigger')
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
    fn.menutrigger($obj, state);
  }, o.throttle);

  fn.menutrigger = function ($obj, state) {
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

  fn.style = function ($obj) {
    var menu = $obj.find('>ul'),
      nested = menu.find('ul');

    // Add classes for parent/child.
    if (nested.length > 0) {
      var child = menu.find('li ul');

      child.addClass('child')
        .parent().addClass('parent')
        .css({
          willChange: 'contents'
        });
    }
  };

  fn.listen = function ($obj, state) {

    jQuery(window).on('resize', function () {
      fn.mediaQuery($obj, state);
    });

    $obj.on('click', function () {
      if (state.mmenu) {
        state.active = state.active ? false : true;
        fn.menutrigger($obj, state);
      }
    });

    jQuery(document).on('keyup', function (e) {
      // ENTER opens menu.
      if (jQuery('.' + o.cclass + '-trigger').is(":focus") && e.which === 13) {
        e.preventDefault();
        state.active = state.active === false ? true : false;
        fn.menutrigger($obj, state);
      }
      // ESC closes menu.
      if (state.active === true && e.which === 27) {
        e.preventDefault();
        state.active = false;
        fn.menutrigger($obj, state);
      }

    });

    jQuery('.parent > a').click(function (e) {
      if (state.mmenu) {
        var parent = jQuery(this).parent(),
          child = parent.children(':gt(0)');

        if (child.length > 0) {
          e.preventDefault();

          if (child.hasClass('active')) {
            parent.removeClass('active');
            child.removeClass('active');
          }
          else {
            parent.addClass('active');
            child.addClass('active');
          }
        }
      }
    });
  };

  fn.init = function () {
    var $obj = jQuery(this),
      state = {
        active: false,
        mmenu: false
      };

    $obj.addClass(o.cclass)
      .once(o.cclass, fn.style($obj));

    fn.mediaQuery($obj, state);

    fn.listen($obj, state);
  };

  return this.each(fn.init);
};