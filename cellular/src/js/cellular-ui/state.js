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
          cclass = 'scrolled',
          uc = cclass + '-up',
          dc = cclass + '-down',
          //y = cellular.state.scrolltop,
          scrolltimeout = null;

  cellular.state.scrolltop = $(document).scrollTop();

  el.attr('data-scrolltop', cellular.state.scrolltop);
  // Detect if page is scrolled
  if (cellular.state.scrolltop < 10) {
    el.removeClass(cclass);
  } else {
    el.addClass(cclass);
  }
  /*
   cellular.scrolltimer(el, uc, dc);
   // Detect scroll direction
   if (cellular.state.scrolltop > y) { // scroll down
   if (!el.hasClass(dc)) {
   el.removeClass(uc)
   .addClass(dc);
   }
   } else if (cellular.state.scrolltop < y) { // scroll up
   if (!el.hasClass(uc)) {
   el.removeClass(dc)
   .addClass(uc);
   }
   }
   */
}, 0, true);

(function state() {
  // Get initial state
  cellular.windowstate();
  cellular.scrollstate();

// Update state on user interaction
  jQuery(window).on('resize', cellular.windowstate);
  jQuery(document).on('scroll', cellular.scrollstate);

})();
