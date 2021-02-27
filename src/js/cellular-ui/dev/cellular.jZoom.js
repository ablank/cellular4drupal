cellular.jZoom = function (opts) {
  var o = jQuery.extend({
    cclass: "jZoom",
    trigger: "jZoom",
    offsetX: "1em",
    offsetY: "1em",
  }, opts),
          fn = {};

  fn.showZoom = function ($obj) {

  };

  fn.closeZoom = function () {

  };

  fn.updateZoom = function ($obj) {

    var imgx = $obj.prop('x');
    var imgy = $obj.prop('y');
    console.log(imgy);
  };
  fn.style = function ($obj) {
    $obj.once(o.cclass, function () {
      jQuery(this).wrap('<span class="' + o.cclass + '-wrap" />')
              .after('<span class="' + o.cclass + '-trigger">Zoom Image</span>')
              .after('<span class="' + o.cclass + '-window">');
    });
  };
  /**
   *
   *
   * @param object $obj
   */
  fn.events = function ($obj) {
    var $zwin = $obj.parent().find('.' + o.cclass + '-window');
    $obj.on('click', function (e) {
      e.preventDefault();
      $zwin.activate();
    });
    $zwin.on('mouseleave blur', function () {
      $zwin.deactivate();
    });
    $zwin.on('mousedown', fn.updateZoom($obj));
  };

  /**
   * Init jTabs
   */
  fn.init = function () {
    var $obj = jQuery(this),
            state = {
              active: false
            };

    fn.style($obj);
    //Set default content
    fn.events($obj);
  };

  return this.each(fn.init);
};
