cellular.jScrolltrigger = function (opts) {
  var o = jQuery.extend({
    "trigger": "bottom", // || 'top' || 'center' || 'inout'
    "padding": "1em", // distance to allow before activating trigger
  }, opts);

  var fn = {};
  fn.trigger = function () {
    jQuery(this).toggleClass(cellular.opts.activeclass);
  };
  return this.each(function () {
    var $w = jQuery(window);
    var w = {};
    w.hgt = $w.height();
    w.pos = $w.scrollTop();

    var $t = jQuery(this);
    var t = {};
    t.hgt = $t.height();
    t.pos = $t.scrollTop();

    if (w.pos - w.hgt >= t.pos) {
      $t.fn.trigger();
    }

    var trig = {};
    trig.top = function () {
      if (t.pos <= w.pos - (w.hgt + t.hgt + o.padding)) {
        $t.fn.trigger();
      }
    };
    trig.center = function () {
      if (t.pos <= w.pos - ((w.hgt / 2) + (t.hgt / 2))) {
        $t.fn.trigger();
      }
    };
    trig.bottom = function () {
      if (t.pos <= w.pos + w.hgt) {
        $t.fn.trigger();

        console.log('ok');
      }
    };

    return trig[o.trigger];
  });
};