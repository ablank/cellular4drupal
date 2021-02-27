cellular.jSticky = function (opts) {
  var fn = {},
          o = jQuery.extend({
            cclass = "jSticky",
            offset: "20%" //Distance from top before activating sticky.
          }, opts);

  fn.style = function ($obj) {
    $obj.classify([o.cclass]);
  };

  fn.update = function ($obj, ostyle) {
    var offsets = $obj.offset(),
            scroll = jQuery(window).scrollTop();

    if (scroll >= offsets.top) {
      $obj.activate()
              .css({
                "position": "fixed",
                "left": offsets.left,
                "top": 0
              });

    } else {
      $obj.removeClass("mini");
      jQuery.each(ostyle, function (prop, value) {
        $obj.css(prop + ": " + value);
      });
    }
  };


  /**
   * Init jSticky
   */
  fn.init = function ($obj) {
    var ostyle = $obj.css(["position", "left", "top", "z-index"]);

    fn.style($obj);
    $(window).scroll(function () {
      fn.update($obj, ostyle);
    });
  };

  return this.each(fn.init(jQuery(this)));
};