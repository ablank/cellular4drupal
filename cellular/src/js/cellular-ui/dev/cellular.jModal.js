cellular.jModal = function (opts) {
  var o = jQuery.extend({
    cclass: "jModal"
  }, opts),
    fn = {};

  /**
   * The <li> object to show.
   *
   * @param object li
   *  $('<li>')
   */
  fn.trigger = function (data) {
    var overlay = jQuery('.' + o.cclass + '-overlay'),
      modal = jQuery('<div class="' + o.cclass + '-window">')
      .append('<span class="control close" aria-label="Close" />');


  };

  /**
   * Generate markup for controls & other elements.
   *
   * @param object $obj
   */
  fn.style = function ($obj) {
    $jQuery.once('jModal', function () {
      var overlay = jQuery('<div class="' + o.cclass + '-overlay">')
        .append('<div class="' + o.cclass + '-window" />')
        .append('<span class="control close" aria-label="Close" />');
      jQuery('body').append(overlay);
    });
  };

  /**
   * Init jModal
   */
  fn.init = function () {
    var $obj = jQuery(this),
      state = {
        active: false
      };
    // Generate markup for modal
    fn.style($obj);
    fn.events($obj, state);
  };

  return this.each(fn.init);
};
