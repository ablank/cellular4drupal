cellular.jCarousel = function(opts) {
var o = jQuery.extend({
active: 0, // default active slide #
  auto: false, // auto advance through slides
  pause: 15000, // time of each slide is displayed if auto == true
  speed: 500,
  easing: "swing"
  // direction: 'right', // direction of auto transition; top || right || bottom || left
  button: {
  next: "Next",
    prev: "Previous",
    pause: "Pause",
    play: "Play"
  }
}, opts);
  var fn = {};
  fn.style = function($obj) {
  var btn = '<div class="' + cellular.opts.cclass + '" />';
    $obj.addClass(cellular.opts.cclass)
    .css({
    "overflow": "hidden"
    })
    .prepend(jQuery(cellular.opts.wrapper).addClass(cellular.opts.cclass + ' back').text(o.button.prev))
    .append(jQuery(cellular.opts.wrapper).addClass(cellular.opts.cclass + ' next').text(o.button.next))
    .find('li').hide();
    if (o.auto) {
  $obj.find('.back').after(jQuery(cellular.opts.wrapper).addClass(cellular.opts.cclass + ' pause').text(o.button.pause));
  }
  };
  fn.showContent = function($obj, target) {
  var li = jQuery($obj).find('li');
    var $t = li.eq(target);
    var $i = $obj.find(jQuery($obj.children()));
    li.hide();
    $t.activate()
    .show();
    //console.log('showContent: '+$t.html());
  };
  return this.each(function() {
  var $obj = jQuery(this);
    var slides = o.src ? o.src : $obj;
    var active = jQuery($obj.find('.active:eq'));
    var target = {};
    // slides.first = jQuery(slides . ':first');

    target.prev = function($obj) {
    var i = 0;
      var li = $obj.find('li');
      for (i; i < li.length; i += 1) {
    i = active[i];
    }
    console.log(li.length);
      return i;
    };
    target.next = function() {
    if (active.next().length) {
    return active.next();
    } else {
    return 0;
    }
    };
    fn.style($obj);
    fn.showContent($obj, o.slide.active);
    $obj.find('.back').click(function() {
  fn.showContent($obj, cellular.previous($obj.find('.active')));
    console.log('prev: ' + cellular.previous($obj.find('.active')));
  });
    $obj.find('.next').click(function() {
  fn.showContent($obj, target.next(active.next()));
    console.log('next: ' + target.next(active.next()));
  });
    if (o.auto) {

  $obj.find('.pause').click(function() {

  });
    fn.showContent($obj, active.next());
  }
  });
};
  /*
   *
   //move the last list item before the first item. The purpose of this is if the user clicks previous he will be able to see the last item.
   $('#carousel_ul li:first').before($('#carousel_ul li:last'));

   //when user clicks the image for sliding right
   $('#right_scroll img').click(function(){

   //get the width of the items ( i like making the jquery part dynamic, so if you change the width in the css you won't have o change it here too ) '
   var item_width = $('#carousel_ul li').outerWidth() + 10;

   //calculate the new left indent of the unordered list
   var left_indent = parseInt($('#carousel_ul').css('left')) - item_width;

   //make the sliding effect using jquery's anumate function '
   $('#carousel_ul').animate({'left' : left_indent},{queue:false, duration:500},function(){

   //get the first list item and put it after the last list item (that's how the infinite effects is made) '
   $('#carousel_ul li:last').after($('#carousel_ul li:first'));

   //and get the left indent to the default -210px
   $('#carousel_ul').css({'left' : '-210px'});
   });
   });

   //when user clicks the image for sliding left
   $('#left_scroll img').click(function(){

   var item_width = $('#carousel_ul li').outerWidth() + 10;

   // same as for sliding right except that it's current left indent + the item width (for the sliding right it's - item_width)
   var left_indent = parseInt($('#carousel_ul').css('left')) + item_width;

   $('#carousel_ul').animate({'left' : left_indent},{queue:false, duration:500},function(){

   // when sliding to left we are moving the last item before the first item
   $('#carousel_ul li:first').before($('#carousel_ul li:last'));

   // and again, when we make that change we are setting the left indent of our unordered list to the default -210px
   $('#carousel_ul').css({'left' : '-210px'});
   });

   });
   */