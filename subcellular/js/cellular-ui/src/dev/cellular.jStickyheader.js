cellular.jStickyheader = function (opts) {
  var o = jQuery.extend({
    active: 0, // default active slide #
  }, opts);

  var fn = {};




  return this.each(function () {
    var $obj = jQuery(this);
    var vscroll = $(window).scrollTop();

    $obj.once(function () {
      $obj.addClass(cellular.opts.cclass);
    });

    if (vscroll > 0) {
      if (jQuery(window).width() > cellular.opts.breakpoint) {
        $obj.addClass("mini");
      }
      $(window).scroll(jStickyheader);
    } else {
      $obj.removeClass("mini");
    }

  });
};