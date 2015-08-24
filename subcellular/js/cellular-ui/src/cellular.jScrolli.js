cellular.jScrolli = function (opts) {
  o = $.extend({
    "active": 0,
    "speed": 500, // Duration of cycle
    "pause": 3000 // Time to pause between cycles
  }, opts);
  /*Math.max.apply(Math, array)*/
  var fn = {};
  //fn.style = function(){};
  return this.each(function () {
    var $obj = jQuery(this);
    var $i = $obj.find('> li');
    var active = o.active ? o.active : $i[0];
    var maxHeight = 0;

    $i.each(function () {
      $t = jQuery(this);
      // Set maxHeight equal to greatest element.
      if ($t.height() > maxHeight) {
        maxHeight = $t.height();
      }
      $t.hide();
    });

    $obj.addClass(cellular.opts.cclass)
      .height(maxHeight)
      .once(cellular.opts.cclass, function () {
        $i.kidWrap();
      });

    jQuery(active).activate()
      .fadeIn(o.speed, function () {
        var $t = jQuery(this);
        var next = $t.next();
        if (next.length === 0) {
          next = $i[0];
        }
        $t.delay(o.pause)
          .fadeOut(o.speed, function () {
            $t.deactivate();
            $obj.jScrolli({
              "active": next,
              "speed": o.speed,
              "pause": o.pause
            });
          });
      });
  });
};