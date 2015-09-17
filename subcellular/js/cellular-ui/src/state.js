
(function state() {
  // Get initial state
  cellular.windowstate();
  cellular.docstate();

// Update state on user interaction
  $(window).on('resize', cellular.windowstate);
  $(document).on('scroll', cellular.docstate);

})();
