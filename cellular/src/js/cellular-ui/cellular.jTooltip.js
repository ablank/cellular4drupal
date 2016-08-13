cellular.jTooltip = function (opts) {
  var o = jQuery.extend({
    trigger: 'jTooltip-trigger', // Class used to trigger tooltip.
    triggerbtn: false, //'jTooltip-trigger-btn', // class-name OR false, used to trigger tooltip
    triggerbtntext: 'About this',
    cclass: 'jTooltip-tooltip',
    dataattr: 'data-tooltip',
    bindto: 'btn', // OR 'event' OR {}
    wrap: true,
    offsetX: 10,
    offsetY: 5
  }, opts),
    fn = {};
  /**
   * Generate markup for buttons.
   *
   * @param object $obj
   */
  fn.style = function ($obj, callback) {
    var tooltip = jQuery('<div>' + $obj.attr(o.dataattr) + '</div>');
    if (o.wrap) {
      $obj.wrap('<div class="' + o.cclass + '-wrap" />');
    }
    tooltip.classify([o.cclass]);
    $obj.after(tooltip);
    if (o.triggerbtn !== false) {
      var btn = jQuery('<span aria-label="' + o.triggerbtntext + '">?</span>');
      btn.classify([o.trigger, o.triggerbtn])
        .prop('tabindex', $obj.prop('tabindex'));
      $obj.before(btn);
    } else {
      $obj.addClass(o.trigger);
    }

    callback($obj);
  };

  fn.events = function ($obj) {

    jQuery('.' + o.trigger).on('mouseenter focus', function (e) {
      var $t = jQuery(this),
        tooltip = $t.nextAll('.' + o.cclass + ':first'),
        btn = {},
        position = {};

      switch (o.bindto) {
        case 'event':
          position = {
            'top': (parseInt(e.clientY) + o.offsetY) + 'px',
            'left': (parseInt(e.clientX) + o.offsetX) + 'px'
          };
          break;
        case 'btn':
          btn = this.getBoundingClientRect();
          position = {
            'top': (btn.top + ($t.height() / 2) + o.offsetY) + 'px',
            'left': (btn.left + $t.width() + o.offsetX) + 'px'
          };
          break;
        default:
        case {}:
          btn = {}.getBoundingClientRect();
          position = {
            'top': (btn.top + ($t.height() / 2) + o.offsetY) + 'px',
            'left': (btn.left + ($t.width() / 2) + o.offsetX) + 'px'
          };
          break;
      }

      tooltip.css(position)
        .activate();
    })
      .on('mouseleave blur', function (e) {
        jQuery(this).nextAll('.' + o.cclass + ':first').deactivate();
      });
  };
  /**
   * Init jSocial
   */
  fn.init = function () {
    fn.style(jQuery(this), fn.events);
  };

  return this.each(fn.init);
};
