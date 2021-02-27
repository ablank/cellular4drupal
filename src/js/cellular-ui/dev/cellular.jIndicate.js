/**
 * jIndicate: Improve form interaction
 */

cellular.jIndicate = function (opts) {
  var fn = {},
          o = jQuery.extend({
            cclass: "jIndicate",
            el: "a", // The html element or .class to indicate.
            events: ['click'] // The events to detect & apply updates on.
          }, opts);

  /**
   * Init jIndicate
   */
  fn.init = function ($obj) {
    var indicator = jQuery('<div class="' + o.cclass + '-indicator"/>'),
            ref = $obj.find(o.el),
            events = [];

    $obj.append(indicator);

    ref.on(events, function (e) {
      var active = jQuery(this);
      active.activate();
      indicator.css({
        "left": active.css('left'),
        "width": active.css('width'),
      });
    });
  };

  return this.each(fn.init(jQuery(this)));
};
