cellular.jBlocklink = function (opts) {
  var o = jQuery.extend({
    cclass: "jBlocklink-link"
  }, opts),
    fn = {};
  
  fn.init = function () {
      var $obj = jQuery(this);

      $obj.once(o.cclass, function () {
        var a1 = $obj.find('a').eq(0);
        var href = a1.attr('href');

        if (href !== undefined) {
          var blink = jQuery('<a href="' + href + '" />');

          blink.classify([
            cellular.opts.cclass,
            o.cclass,
            a1.attr('class') ? a1.attr('class') : null
          ]);
          // .data(a.data());
          $obj.wrap(blink)
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