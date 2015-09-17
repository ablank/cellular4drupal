/**
 * jTabs : Tabify a list of content
 */

cellular.jTabs = function (opts) {
  var o = jQuery.extend({
    active: 0, // Array index of initially active tab
    orient: "horizontal" // || "vertical"
  }, opts),
    fn = {};

  fn.showContent = function ($obj, li) {
    var c = li.find('.content'),
      pan = $obj.parent().find('.panel-content');

    li.activate();
    pan.fadeOut('normal', function () {
      jQuery(this).html(c.html())
        .fadeIn('normal');
    });
  };

  fn.init = function () {
    var $obj = jQuery(this),
      tab = $obj.find('> li'),
      wrap = jQuery('<div class="' + cellular.opts.cclass + ' ' + o.orient + ' jTabs-wrap"></div>');

    $obj.once('jTabs', function () {

      $obj.wrap(wrap)
        .after('<div class="panel"><div class="panel-content" /></div>');

      //wrap.find('.panel').append('');

      tab.each(function () {
        var li = jQuery(this);

        li.addClass('tab')
          .kidWrap();
        //Set 1st child as title
        li.children().eq(0).addClass('title');
        //Set wrapper as content
        li.children().eq(1).addClass('content')
          .hide();
      });
    });

    //Add classes/functions to each panel
    tab.each(function () {
      var li = jQuery(this);

      li.click(function (e) {
        e.preventDefault();
        fn.showContent($obj, li);
      });
    });

    //Set default content
    fn.showContent($obj, tab.eq([o.active]));
  };

  return this.each(fn.init);
};