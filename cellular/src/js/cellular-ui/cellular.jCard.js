cellular.jCard = function (opts) {
  var o = jQuery.extend({
    cclass: "jCard"
  }, opts),
    fn = {};

  fn.init = function () {
    var $obj = jQuery(this);

    $obj.once(o.cclass, function () {
      var a1 = $obj.find('a').eq(0);
      var href = a1.attr('href');

      if (href !== undefined) {
        var wrapperlink = jQuery('<a href="' + href + '" />').classify([
          o.cclass + '-wrap',
          a1.attr('class') ? a1.attr('class') : null
        ]);
        // .data(a.data());
        $obj.wrap(wrapperlink)
          .find('h2, h3').addClass('title');
      }
    });

    $obj.on('mouseenter touchstart', function () {
      jQuery(this).activate();
    }).on('mouseleave touchend', function () {
      jQuery(this).deactivate();
    });
  };

  return this.each(fn.init);
};
