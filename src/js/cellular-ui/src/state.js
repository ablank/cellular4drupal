
(function state() {
  // Get initial state
  cellular.windowstate();
  cellular.scrollstate();

// Update state on user interaction
  $(window).on('resize', cellular.windowstate);
  $(document).on('scroll', cellular.scrollstate);

})();
