/**
 * Set state on window resize
 */
cellular.windowstate = cellular.debounce(function () {
  var ob = cellular.state.breakpoint;

  cellular.state.breakpoint = cellular.breakpoint().type;
  jQuery('body').removeClass(ob)
    .addClass(cellular.state.breakpoint);
}, 100);

/**
 * Set state on document scroll
 */
cellular.scrollstate = cellular.debounce(function (e, y) {
  var el = jQuery('body'),
    cclass = 'scrolling',
    uc = cclass + '-up',
    dc = cclass + '-down',
    dst = jQuery(document).scrollTop(),
    region = el.height() / 3,
    //y = cellular.state.scrolltop,
    scrolltimeout = null;

  if (dst > 30) {
    el.addClass('scrolled');
  }
  else {
    el.removeClass('scrolled');
  }

  if (dst > cellular.state.scrolltop) {
    el.addClass(dc)
      .removeClass(uc);
  } else {
    el.addClass(uc)
      .removeClass(dc);
  }

  // Detect if page is scrolled
  if (dst < region) {
    el.removeClass('page-middle page-bottom')
      .addClass('page-top');
  }
  else if (dst > region && dst < region * 2) {
    el.removeClass('page-top page-bottom')
      .addClass('page-middle');
  }
  else {
    el.removeClass('page-top page-middle')
      .addClass('page-bottom');
  }
//Update global state
  cellular.state.scrolltop = dst;
  // % of doc scrolled
  cellular.state.scrolled = (dst/(el.height()-jQuery(window).height())) * 100;
}, 0, true);

(function state() {
  // Get initial state
  cellular.windowstate();
  cellular.scrollstate();

  // Update state on user interaction
  jQuery(window).on('resize', cellular.windowstate);
  jQuery(document).on('scroll', cellular.scrollstate);

})();
