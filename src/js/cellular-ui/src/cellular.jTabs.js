/**
 * jTabs : Tabify a list of content
 */

cellular.jTabs = function (opts) {
  var o = jQuery.extend({
    active: 0, // Array index of initially active tab
    orient: "horizontal", // || "vertical"
    cclass: "jTabs"
  }, opts),
    fn = {};

  /**
   *
   *
   * @param object $obj
   * @param object li
   */
  fn.showContent = function ($obj, li) {
    var c = li.find('.content'),
      pan = $obj.parent().find('.panel-content');

    li.activate();
    pan.fadeOut('normal', function () {
      jQuery(this).html(c.html())
        .fadeIn('normal');
    });
  };

  /**
   * Init jTabs
   */
  fn.init = function () {
    var $obj = jQuery(this),
      tab = $obj.find('> li'),
      wrap = jQuery('<div/>').classify([
      cellular.opts.cclass,
      o.orient,
      o.cclass + '-wrap'
    ]),
      panel = '<div class="panel"><div class="panel-content" /></div>';

    $obj.once(o.cclass, function () {

      $obj.wrap(wrap)
        .after(panel);

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