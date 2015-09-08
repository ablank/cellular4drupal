cellular.jAccordion = function (opts) {
  var o = jQuery.extend({
    active: 0, // Index value of initial content to display.
    duration: 500, // Duration of transition.
    easing: "swing", // Type of easing.
    single: false // Allow multiple panels to be opened or only 1?
  }, opts);

  var fn = {};

  fn.showContent = function ($li) {

    if (o.single === true) {
      $li.siblings('.active').deactivate()
        .find('.panel').slideUp(o.duration, o.easing);
    }
    else {
      $li.activate()
        .find('.panel').slideToggle(o.duration, o.easing);
    }
  };

  fn.style = function ($obj) {
    $obj.once('jAccordion', function () {

      $obj.addClass(cellular.opts.cclass)
        .find('> li').each(function () {
        var $t = jQuery(this);

        $t.kidWrap();
        $t.children().eq(0).addClass('title');
        $t.children().eq(1).classify([cellular.opts.cclass, 'panel']);
        $t.find('.panel').hide();
        $t.find('.title').click(function (e) {
          e.preventDefault();
          fn.showContent($t);
        });
      });
    });
  };

  fn.init = function () {
    var $obj = jQuery(this);
    // Generate markup for accordion
    fn.style($obj);
    //Set default content
    fn.showContent($obj.children().eq(o.active));
  };

  return this.each(fn.init);
};