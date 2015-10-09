cellular.jToggle = function (opts) {
  var o = jQuery.extend({
    "max-height": 500,
    "max-width": 500,
    "easing": "swing",
    "single": false
  }, opts);

  var fn = {};

  fn.showContent = function ($li) {

    if (o.single === true) {
      $li.siblings('.active').deactivate()
        .find('.panel').slideUp(o.duration, o.easing);
    }

    $li.activate()
      .find('.panel').slideToggle(o.duration, o.easing);
  };

  return this.each(function () {
    var $obj = jQuery(this);
    var li = $obj.find('li');

    $obj.addClass(cellular.opts.cclass);
    //fn.style($obj);
    //Add classes/functions to each panel
    li.each(function () {
      var $t = jQuery(this);

      $t.kidWrap();

      $t.children().eq(0).addClass('title');
      $t.children().eq(1).addClass('panel');

      $t.find('.panel').hide();

      $t.find('.title').click(function (e) {
        e.preventDefault();
        fn.showContent($t);
      });
    });

    //Set default content
    fn.showContent($obj.children().eq(o.active));
  });
};