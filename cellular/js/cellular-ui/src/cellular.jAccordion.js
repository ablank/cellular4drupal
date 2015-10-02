cellular.jAccordion = function (opts) {
  var o = jQuery.extend({
    active: 0, // Index value of initial content to display.
    duration: 500, // Duration of transition.
    easing: "swing", // Type of easing.
    single: false, // Allow multiple panels to be opened or only 1?
    pclass: "panel"
  }, opts),
    fn = {};

  o.pselect = '.' + o.pclass;
  /**
   * The <li> object to show.
   *
   * @param object li
   *  $('<li>')
   */
  fn.showContent = function (li) {

    if (o.single) {
      li.siblings().find(o.pselect).slideUp(o.duration, o.easing);
      li.activate()
        .find(o.pselect).slideDown(o.duration, o.easing);
    }
    else {
      li.toggleClass(cellular.opts.activeclass)
        .find(o.pselect).slideToggle(o.duration, o.easing);
    }
  };

  /**
   * Generate markup for controls & other elements.
   *
   * @param object $obj
   */
  fn.style = function ($obj) {
    $obj.once('jAccordion', function () {

      $obj.addClass(cellular.opts.cclass)
        .find('> li').each(function () {
        var li = jQuery(this);

        li.kidWrap();
        li.children().eq(0).addClass('title');
        li.children().eq(1).classify([cellular.opts.cclass, 'panel']);
        li.find(o.pselect).hide();
        li.find('.title').click(function (e) {
          e.preventDefault();
          fn.showContent(li);
        });
      });
    });
  };

  /**
   * Init jAccordion
   */
  fn.init = function () {
    var $obj = jQuery(this);
    // Generate markup for accordion
    fn.style($obj);
    //Set default content
    fn.showContent($obj.children().eq(o.active));
  };

  return this.each(fn.init);
};