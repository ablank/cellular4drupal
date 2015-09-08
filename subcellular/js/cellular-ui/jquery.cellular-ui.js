/**
* @file
* CellularUI Javascript Library
* 
* @author Adam Blankenship <i.adambear@gmail.com>
\n* 
* @see http://live-cellular.gotpantheon.com/cellular-ui
*/
(function ($) {

 // :)
Drupal.behaviors.cellular = {
attach: function (context, settings) {

 // :)
var cellular = {};
cellular.opts = {
cclass: "cellular",
activeclass: "active",
breakpoint: "mobile"
};

 // :)
cellular.breakpoint = function () {
var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content'),
mq = {
size: content.match(/\d/g).join(""),
type: content.match(/\w*[^\"\'](?=-)/g).join("")
};
return mq;
};
cellular.activate = function () {
return this.each(function () {
var $t = jQuery(this);
if (!$t.hasClass(cellular.opts.activeclass)) {
$t.addClass(cellular.opts.activeclass)
.siblings().removeClass(cellular.opts.activeclass);
}
});
};
cellular.deactivate = function () {
return this.each(function () {
jQuery(this).removeClass(cellular.opts.activeclass);
});
};
cellular.kidWrap = function () {
// Wrap element's children with index gt 0
return this.each(function () {
var $t = jQuery(this);
if ($t.children().length > 1) {
$t.children(':gt(0)').wrapAll('<div>');
}
});
};
cellular.classify = function ($array) {
// Add array of classes to element
return this.each(function () {
jQuery(this).addClass($array.join(' '));
});
};
/*
cellular.autodimension = function ($obj, dimension) {
return this.each(function () {
var $t = jQuery(this),
max = 0;
if ($obj === 'auto') {
$t.height(state.maxheight);
} else {
$t.height(o.size.height);
}
});
};
cellular.throttle = function (fn, delay) {
return this.each(function () {
var timer = null,
context = this,
args = arguments;
;
delay = delay ? delay : 250;
clearTimeout(timer);
timer = setTimeout(function () {
fn.apply(context, args);
}, delay);
});
};
*/

 // :)
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

 // :)
cellular.jBlocklink = function (opts) {
var o = jQuery.extend({
cclass: "jBlocklink-link"
}, opts),
fn = {};
fn.init = function () {
var $obj = jQuery(this);
$obj.once(o.cclass, function () {
var a = $obj.find('a').eq(0);
var ahref = a.attr('href');
if (ahref !== undefined) {
var bl = jQuery('<a href="' + ahref + '" />');
bl.classify([
cellular.opts.cclass,
o.cclass,
a.attr('class') ? a.attr('class') : null
]);
// .data(a.data());
$obj.wrap(bl)
.find('h2, h3').addClass('title');
}
});
$obj.on('mouseenter touchstart', function () {
jQuery(this).activate();
}).on('mouseleave touchend', function () {
jQuery(this).deactivate();
});
};
return this.each(fn.init);
};

 // :)
cellular.jEqualheight = function (opts) {
/*
var array = [267, 306, 108];
var largest = Math.max.apply(Math, array); // 306
*/
var o = jQuery.extend({
//"opt": val
}, opts),
fn = {};
fn.init = function () {
var $obj = jQuery(this),
kids = $obj.find('>*'),
maxHeight = 0;
kids.each(function () {
$t = jQuery(this);
if ($t.height() > maxHeight) {
maxHeight = $t.height();
}
$t.height(maxHeight);
});
};
return this.each(fn.init);
};

 // :)
cellular.jMmenu = function (opts) {
var o = jQuery.extend({
breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
parent: jQuery('body'), // Parent element used to attach menu
cclass: "jMmenu", // Menu class to test
type: "slide", // Type of animation
direction: "right" // Direction of animation
}, opts),
fn = {};
fn.classes = [
o.type + '-' + o.direction,
o.cclass + '-active',
o.cclass + '-inactive'
];
fn.mediaQuery = function ($obj) {
if (o.breakpoint === cellular.breakpoint().type) {
var $menu = $obj.children([0]),
classes = [
fn.classes[0],
fn.classes[2]
];
if (!o.parent.hasClass(fn.classes[0])) {
o.parent.addClass(classes.join(' '));
$menu.addClass(o.cclass);
}
$menu.prependTo(o.parent);
}
};
fn.init = function () {
var $obj = jQuery(this),
$window = jQuery(window);
fn.mediaQuery($obj);
$window.on('resize', function () {
fn.mediaQuery($obj);
// console.log(cellular.breakpoint());
});
$obj.on('click', function () {
if (o.parent.hasClass(fn.classes[0])) {
o.parent.toggleClass(fn.classes[1])
.toggleClass(fn.classes[2]);
$obj.toggleClass(cellular.opts.activeclass);
}
});
};
return this.each(fn.init);
};

 // :)
cellular.jScrolli = function (opts) {
var o = $.extend({
cclass: 'jScrolli', // Object class selector
active: 0, // Index of initially selected slide
size: {
//width: 700,
height: 'auto' // 'auto' or '[value]', i.e. '300px'
},
controls: {
events: 'click touchend MSPointerUp',
showcontrols: true,
showmarkers: true,
autoplay: true,
pauseonhover: true,
text: {
next: 'Next',
prev: 'Prev',
pause: 'Pause'
}
},
transition: {
function: 'fn.slide', //
pause: 5, // Time (seconds) to pause between slides.
speed: 500 // Animation speed (milliseconds).
},
caption: {
enable: true,
autohide: false,
selector: '.caption' // 'auto' or '.selector' used to generate caption
},
autodim: true,
delay: 1.4 // Time (seconds) to wait before dimming.
}, opts);
var fn = {};
fn.button = function ($text) {
return '<a class="control ' + $text.toLowerCase() + '">' + $text + '</a>';
};
// Update next/prev slides.
fn.normalize = function ($obj, state) {
state.prev = state.current - 1;
state.next = state.current + 1;
if (state.prev < 0) {
state.prev = state.count;
}
if (state.next > state.count) {
state.next = 0;
}
// state.interval = 0;
};
// Activate selected slide & corresponding marker
fn.go = function (index, $obj, state) {
if (!state.paused) {
// Normalize state
fn.normalize($obj, state);
// Update the marker
if (o.controls.showmarkers) {
fn.mark($obj, state);
}
// Update the caption
if (o.caption.enable) {
fn.caption($obj, state);
}
if (o.controls.autoplay) {
// Reset the transition timer for autoplay
fn.updateinterval($obj, state);
}
// Update classes on slides for css transition
jQuery($obj[state.prev]).addClass('previous')
.siblings().removeClass('previous');
jQuery($obj[state.next]).addClass('next')
.siblings().removeClass('next');
jQuery($obj[index]).activate()
.removeClass('previous next');
}
};
// Activate the slide marker
fn.mark = function ($obj, state) {
$obj.parent().parent().find('.marker')
.eq(state.current).activate();
};
// Update slide caption
fn.caption = function ($obj, state) {
state.caption = $obj.parent().find(o.caption.selector).eq(state.current).html();
$obj.parent().parent().find('> .caption').html(state.caption);
};
fn.autoheight = function ($obj, state) {
if (o.size.height === 'auto') {
$obj.height(state.maxheight);
} else {
$obj.height(o.size.height);
}
};
// Generate markup
fn.style = function ($obj, state) {
var slides = $obj.find('> li');
$obj.addClass(cellular.opts.cclass)
.wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />');
if (o.caption.enable) {
if (o.caption.selector === 'auto') {
// o.caption.selector =
}
else {
$obj.find(o.caption.selector).hide();
}
$obj.before('<div class="caption" />');
}
slides.each(function () {
var $t = jQuery(this);
$t.addClass('slide')
.children().wrapAll('<div class="wrap" />');
fn.autoheight($t, state);
});
fn.autoheight($obj, state);
if (o.controls.showmarkers) {
var markers = jQuery('<div class="markers"><ul></ul></div>');
for (var i = 0; i < slides.length; i += 1) {
var index = i;
markers.find('ul')
.append('<li class="marker" data-href="' + index + '">' + (index + 1) + '</li>');
}
$obj.after(markers);
fn.mark($obj, state);
}
if (o.controls.showcontrols) {
var controls = [
fn.button(o.controls.text.pause),
fn.button(o.controls.text.prev),
fn.button(o.controls.text.next)
];
$obj.after('<div class="controls">' + controls[0] + controls[1] + controls[2] + '</div>');
}
};
fn.updateinterval = function ($obj, state) {
clearInterval(state.interval);
state.interval = setInterval(function () {
state.current = state.next;
fn.go(state.current, $obj, state);
}, o.transition.pause * 1000);
};
// Auto-increment to next slide
fn.autoplay = function ($obj, state) {
if (!state.paused) {
fn.updateinterval($obj, state);
/*
state.interval = setInterval(function () {
state.current = state.next;
fn.go(state.current, $obj, state);
}, o.transition.pause * 1000);
*/
}
};
// Add Event Listeners
fn.events = function ($obj, state) {
var controls = $obj.siblings('.controls'),
$i = $obj.find('> li'),
wrap = $obj.parent(),
eX = null,
eY = null;
// Previous
controls.find('.prev').on(o.controls.events, function (e) {
state.current = state.prev;
state.paused = false;
fn.go(state.current, $i, state);
});
// Next
controls.find('.next').on(o.controls.events, function (e) {
state.current = state.next;
state.paused = false;
fn.go(state.current, $i, state);
});
/*
// Pause
controls.find('.pause').on(o.controls.events, function (e) {
state.paused = state.paused ? false : true;
state.active = state.active ? ;
console.log(state.paused);
});
*/
wrap.on({
'mouseover': function () {
state.active = true;
o.controls.pauseonhover ? state.paused = true : null;
if (o.autodim)
wrap.activate();
window.clearTimeout(wrap.timeout);
},
'mouseout': function () {
state.active = false;
o.controls.pauseonhover ? state.paused = false : null;
o.autodim ? wrap.timeout = window.setTimeout(function () {
wrap.deactivate();
}, o.delay * 1000) : null;
},
'touchstart': function (e) {
eX = e.touches[0].clientX;
eY = e.touches[0].clientY;
state.active = true;
},
'touchmove': function (e) {
if (!eX || !eY) {
return;
}
var margin = 20,
Xdiff = eX - (e.touches[0].clientX),
Ydiff = eY - (e.touches[0].clientY);
// Detect horizontal or vertical swipe
if (Math.abs(Xdiff) > Math.abs(Ydiff)) {
// Horizontal (left : right)
state.current = Xdiff > margin ? state.prev : state.next;
} else {
// Vertical (up : down)
state.current = Ydiff > margin ? state.prev : state.next;
}
// Reset vars for next swipe
eX = null;
eY = null;
state.active = false;
// Move to next slide
fn.go(state.current, $i, state);
}
});
// Link markers to respective slides
if (o.controls.showmarkers) {
$obj.siblings().find('.marker').on('click', function () {
state.current = jQuery(this).attr('data-href');
state.paused = false;
fn.go(state.current, $i, state);
});
}
if (state.active) {
jQuery(document).on('keyup', function (e) {
console.log(e.which);
var keys = [
37, // left
38, // up
39, // right
40 // down
];
if (keys.indexOf(e.which) !== -1) {
console.log(e.which);
e.preventDefault();
state.paused = false;
switch (e.which) {
case 37:
state.current = state.prev;
break;
case 39:
state.current = state.next;
break;
}
fn.go(state.current, $i, state);
}
});
}
};
fn.init = function () {
var $obj = jQuery(this),
$i = $obj.find('> li'),
state = {
active: true,
paused: false,
animating: false,
count: $i.length - 1,
width: $obj.width(),
maxheight: 0,
interval: 0,
controls: 0,
caption: jQuery(o.caption.selector).html(),
current: o.active ? o.active : 0
};
state.prev = state.current - 1;
state.next = state.current + 1;
o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
$i.each(function () {
var $t = jQuery(this);
// Set maxheight equal to greatest element.
if ($t.height() > state.maxheight) {
state.maxheight = $t.height();
}
});
// Add markup
$obj.once(o.cclass, function () {
fn.style($obj, state);
});
// Add Event Listeners
fn.events($obj, state);
// Activate 1st slide
fn.go(state.current, $i, state);
// Start autoplay
if (o.controls.autoplay) {
fn.autoplay($i, state);
}
};
return this.each(fn.init);
};

 // :)
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

 // :)
jQuery.fn.extend(cellular);

 // :)
//Drupal.behaviors.cellular = {
//attach: function (context, settings) {
}
};

 // :)
})(jQuery);