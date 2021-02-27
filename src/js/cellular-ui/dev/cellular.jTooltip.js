cellular.jTooltip = function (opts) {
  var o = jQuery.extend({
    cclass: 'jTooltip', // jTooltip-tooltip
    dataattr: 'data-tooltip', // Data to use in the tooltip.
    triggerbtn: true, //'true OR false, used to trigger tooltip
    triggerbtntext: 'About this',
    offsetX: 10,
    offsetY: 5
  }, opts),
          fn = {};
  /**
   * Generate markup for buttons.
   *
   * @param object $obj
   */
  fn.style = function ($obj) {
    var tooltip = jQuery('<div>' + $obj.attr(o.dataattr) + '</div>'),
            tclass = o.cclass + '-trigger';

    // $obj

    tooltip.addClass(o.cclass + '-tooltip');

    if (o.triggerbtn === true) {
      var btn = jQuery('<span aria-label="' + o.triggerbtntext + '">?</span>'),
              tindex = $obj.prop('tabindex') ? $obj.prop('tabindex') : "0";

      btn.classify([tclass, o.cclass + '-btn'])
              .prop("tabindex", tindex);
      $obj.wrap('<div class="' + o.cclass + '-wrap" />')
              .parent().prepend(btn); //.before(btn)
    } else {
      $obj.addClass(tclass);
    }
    // Add the tooltip.
    $obj.after(tooltip);

//    callback($obj);
  };

  fn.listen = function ($obj) {

    jQuery('.' + o.cclass + '-trigger').on('mouseenter focus', function (e) {
      var $t = jQuery(this),
              tooltip = $t.nextAll('.' + o.cclass + ':first'),
              btn = {},
              position = {};

      if (o.triggerbtn === true) {
        btn = this.getBoundingClientRect();
        position = {
          'top': (btn.top + ($t.height() / 2) + o.offsetY) + 'px',
          'left': (btn.left + $t.width() + o.offsetX) + 'px'
        };
      } else {
        position = {
          'top': (parseInt(e.clientY) + o.offsetY) + 'px',
          'left': (parseInt(e.clientX) + o.offsetX) + 'px'
        };
      }

      tooltip.css(position)
              .activate();
    })
            .on('mouseleave blur', function (e) {
              jQuery(this).nextAll('.' + o.cclass + '-tooltip:first').deactivate();
            });
  };
  /**
   * Init jSocial
   */
  fn.init = function () {
    var $obj = jQuery(this);

    $obj.addClass(o.cclass)
            .once(o.cclass, fn.style($obj));

    fn.listen();
  };

  return this.each(fn.init);
};