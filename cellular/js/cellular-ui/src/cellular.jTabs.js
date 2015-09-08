cellular.jTabs = function (opts) {
  var o = jQuery.extend({
    active: 0, // Array index of initially active tab
    orient: "horizontal" // || 'vertical'
  }, opts),
    fn = {};

  fn.showContent = function (li) {
    var c = li.find('.content'),
      pan = li.parent().find('.panel-content');

    li.activate();
    pan.fadeOut('normal', function () {
      jQuery(this).html(c.html())
        .fadeIn('normal');
    });
  };

  fn.init = function () {
    var $obj = jQuery(this),
      tab = $obj.find('> li'),
      maxheight = 0;

    $obj.addClass(cellular.opts.cclass)
      .height(maxheight);
    $obj.once('jTabs', function () {

      $obj.addClass(cellular.opts.cclass + ' ' + o.orient)
        .append('<div class="' + cellular.opts.cclass + ' panel" />');
      $obj.find('.panel').append('<div class="panel-content" />');

      tab.each(function () {
        var li = jQuery(this);

        li.addClass('tab')
          .kidWrap();
        //Set 1st child as title
        li.children().eq(0).addClass('title');
        //Set 2nd child as content
        li.children().eq(1).addClass('content')
          .hide();
      });
    });

    //Add classes/functions to each panel
    tab.each(function () {
      var li = jQuery(this);

      li.click(function (e) {
        e.preventDefault();
        fn.showContent(li);
      });
    });

    //Set default content
    fn.showContent(tab.eq([o.active]));
  };

  return this.each(fn.init);
};