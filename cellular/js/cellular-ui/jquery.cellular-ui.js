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
breakpoint: "window_mobile"
};
cellular.state = {
breakpoint: 0,
scrolltop: 0,
scrolltimer: 0
};

 // :)
/**
* Cellular utility functions
*/
/**
* Get the breakpoints specified in CSS
*/
cellular.breakpoint = function () {
var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content');
return {
size: content.match(/\d/g).join(""),
type: content.match(/\w*[^\"\'](?=-)/g).join("")
};
};
/**
* Add active class to element, remove active class from element siblings
*/
cellular.activate = function (theclass) {
theclass = theclass ? theclass : cellular.opts.activeclass;
return this.each(function () {
var $t = jQuery(this);
if (!$t.hasClass(theclass)) {
$t.addClass(theclass)
.siblings().removeClass(theclass);
}
});
};
/**
* Remove 'active' class
*/
cellular.deactivate = function (theclass) {
theclass = theclass ? theclass : cellular.opts.activeclass;
return this.each(function () {
jQuery(this).removeClass(theclass);
});
};
/**
* Wrap element's children after 1st child
*/
cellular.kidWrap = function () {
return this.each(function () {
var $t = jQuery(this);
if ($t.children().length > 1) {
$t.children(':gt(0)').wrapAll('<div>');
}
});
};
/**
* Add array of classes to element
*/
cellular.classify = function ($array) {
return this.each(function () {
jQuery(this).addClass($array.join(' '));
});
};
/**
* Debounce fn borrowed from Underscore.js
*/
cellular.debounce = function (func, wait, immediate) {
var timeout;
return function () {
var context = this,
args = arguments,
later = function () {
timeout = null;
if (!immediate)
func.apply(context, args);
},
callNow = immediate && !timeout;
clearTimeout(timeout);
timeout = setTimeout(later, wait);
if (callNow)
func.apply(context, args);
};
};
/**
* Detect css transition end event.
* @see Function from David Walsh: http://davidwalsh.name/css-animation-callback
*/
cellular.transitionend = function () {
var t,
el = document.createElement("test"),
transitions = {
transition: "transitionend",
OTransition: "oTransitionEnd",
MozTransition: "transitionend",
WebkitTransition: "webkitTransitionEnd"
};
for (t in transitions) {
if (el.style[t] !== undefined) {
return transitions[t];
}
}
};
/**
* Set state on window resize
*/
cellular.windowstate = cellular.debounce(function () {
var ob = cellular.state.breakpoint;
cellular.state.breakpoint = cellular.breakpoint().type;
jQuery('body').removeClass(ob)
.addClass(cellular.state.breakpoint);
}, 500);
/**
* Set state on document scroll
*/
cellular.scrollstate = cellular.debounce(function (e, y) {
var el = jQuery('body'),
cclass = 'scrolled',
uc = cclass + '-up',
dc = cclass + '-down',
y = cellular.state.scrolltop,
scrolltimeout = null;
cellular.state.scrolltop = $(document).scrollTop();
cellular.scrolltimer(el, uc, dc);
// Detect if page is scrolled
if (cellular.state.scrolltop > 0) {
el.addClass(cclass);
}
else {
el.removeClass(cclass);
}
// Detect scroll direction
if (cellular.state.scrolltop > y) {
if (!el.hasClass(dc)) {
el.removeClass(uc)
.addClass(dc);
}
}
else {
if (!el.hasClass(uc)) {
el.removeClass(dc)
.addClass(uc);
}
}
}, 0, true);
/**
* Reset scroll timer
*/
cellular.scrolltimer = function (el, uc, dc) {
window.clearTimeout(cellular.state.scrolltimer);
cellular.state.scrolltimer = window.setTimeout(function () {
el.removeClass(uc + ' ' + dc);
}, 2000);
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
*/

 // :)
(function state() {
// Get initial state
cellular.windowstate();
cellular.scrollstate();
// Update state on user interaction
$(window).on('resize', cellular.windowstate);
$(document).on('scroll', cellular.scrollstate);
})();

 // :)
cellular.jAccordion = function (opts) {
var o = jQuery.extend({
active: 0, // Index value of initial content to display.
duration: 500, // Duration of transition.
easing: "swing", // Type of easing.
single: false, // Allow multiple panels to be opened or only 1?
pclass: "panel"
}, opts),
fn = {};
o.pselect = '.' + o.pclass;
/**
* The <li> object to show.
*
* @param object li
*  $('<li>')
*/
fn.showContent = function (li) {
if (o.single) {
li.siblings().find(o.pselect).slideUp(o.duration, o.easing);
li.activate()
.find(o.pselect).slideDown(o.duration, o.easing);
}
else {
li.toggleClass(cellular.opts.activeclass)
.find(o.pselect).slideToggle(o.duration, o.easing);
}
};
/**
* Generate markup for controls & other elements.
*
* @param object $obj
*/
fn.style = function ($obj) {
$obj.once('jAccordion', function () {
$obj.addClass(cellular.opts.cclass)
.find('> li').each(function () {
var li = jQuery(this);
li.kidWrap();
li.children().eq(0).addClass('title');
li.children().eq(1).classify([cellular.opts.cclass, 'panel']);
li.find(o.pselect).hide();
li.find('.title').click(function (e) {
e.preventDefault();
fn.showContent(li);
});
});
});
};
/**
* Init jAccordion
*/
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
var a1 = $obj.find('a').eq(0);
var href = a1.attr('href');
if (href !== undefined) {
var blink = jQuery('<a href="' + href + '" />');
blink.classify([
cellular.opts.cclass,
o.cclass,
a1.attr('class') ? a1.attr('class') : null
]);
// .data(a.data());
$obj.wrap(blink)
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
/**
* jEqualheight: Set children to equal height
*/
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
/**
* jMmenu: Hamburger menu for mobile devices
*/
cellular.jMmenu = function (opts) {
var o = jQuery.extend({
breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
parent: jQuery('body'), // Parent element used to attach menu
cclass: "jMmenu", // Menu class to test
type: "slide", // Type of animation
direction: "right" // Direction of animation
}, opts),
fn = {};
fn.mediaQuery = cellular.debounce(function ($obj, state) {
if (o.breakpoint === cellular.state.breakpoint) {
var $menu = $obj.children([0]);
state.mmenu = true;
o.parent.addClass(o.type + '-' + o.direction);
$menu.addClass(o.cclass)
.prependTo(o.parent);
fn.trigger($obj, state);
}
}, 500);
fn.trigger = function ($obj, state) {
var classes = [
o.cclass + '-active',
o.cclass + '-inactive'
];
if (state.active) {
$obj.activate();
o.parent.addClass(classes[0])
.removeClass(classes[1]);
}
else {
$obj.deactivate();
o.parent.addClass(classes[1])
.removeClass(classes[0]);
}
};
fn.init = function () {
var $obj = jQuery(this),
state = {
active: false,
mmenu: false
};
fn.mediaQuery($obj, state);
jQuery(window).on('resize', function () {
fn.mediaQuery($obj, state);
});
$obj.on('click', function () {
if (state.mmenu) {
state.active = state.active ? false : true;
fn.trigger($obj, state);
}
});
};
return this.each(fn.init);
};

 // :)
/**
* jScrolli : Content carousel/slider
*/
cellular.jScrolli = function (opts) {
var o = $.extend({
cclass: "jScrolli", // Object class selector
active: 0, // Index of initially selected slide
//width: "100%", // 'auto' or '[value]', i.e. '300px'
height: "auto", // 'auto' or '[value]', i.e. '300px'
controls: {
showmarkers: true,
showcontrols: true,
keyboard: true,
swipe: true,
autoplay: true,
pauseonhover: true,
autodim: true,
delay: 1.4, // Time (seconds) to wait before dimming.
text: {
next: "Next",
prev: "Prev",
pause: "Pause",
play: "Play"
}
},
transition: {
pause: 5 // Time (seconds) to pause between slides.
//speed: 500 // Animation speed (milliseconds).
},
caption: {
enable: true,
autohide: false,
selector: ".caption" // 'auto' or '.selector' used to generate caption
}
}, opts),
fn = {};
/**
* Format html buttons for controls.
*
* @param string $text
* @returns string
*/
fn.button = function ($text) {
return '<a class="control ' + $text.toLowerCase() + '">' + $text + '</a>';
};
/**
* Update next/prev slides.
*
* @param object state
*/
fn.normalize = function (state) {
state.prev = state.current - 1;
state.next = state.current + 1;
if (state.prev < 0) {
state.prev = state.count;
}
if (state.next > state.count) {
state.next = 0;
}
};
/**
* Activate selected slide & corresponding marker.
*
* @param int index
* @param object $obj
* @param object state
*/
fn.go = function (index, $obj, state) {
if (!state.paused) {
var tclass = 'transition',
li = $obj.find('.slide');
state.current = parseInt(index);
// Normalize state
fn.normalize(state);
// Update classes on slides for css transition
jQuery(li[state.prev]).activate('previous');
jQuery(li[state.next]).activate('next');
jQuery(li[index]).activate();
// Listen for transition to complete & update classes
$obj.parent().addClass(tclass)
.one(cellular.transitionend(), function () {
jQuery(this).removeClass(tclass);
});
// Update the marker
if (o.controls.showmarkers) {
fn.mark($obj, state);
}
// Update the caption
if (o.caption.enable) {
fn.caption(li, state);
}
// Reset the autoplay timer
if (o.controls.autoplay) {
fn.updateinterval($obj, state);
}
}
};
/**
* Update the current marker.
*/
fn.mark = function ($obj, state) {
$obj.siblings().find('.marker')
.eq(state.current).activate();
};
/**
* Update slide caption
*/
fn.caption = function ($obj, state) {
var wrap = $obj.parent().parent(),
cap = wrap.find('> .caption p');
// Get current slide's caption
state.caption = wrap.find(o.caption.selector).eq(state.current).text();
// Update the active caption
cap.text(state.caption);
};
fn.updateinterval = function ($obj, state) {
if (o.controls.autoplay && !state.paused) {
clearInterval(state.interval);
state.interval = setInterval(function () {
state.current = state.next;
fn.go(state.current, $obj, state);
}, o.transition.pause * 1000);
}
};
/**
* Add event listeners
*
* @param {type} $obj
* @param {type} state
*/
fn.events = function ($obj, state) {
var controls = $obj.siblings('.controls'),
wrap = $obj.parent(),
eX = null,
eY = null;
// Link markers to respective slides
if (o.controls.showmarkers) {
$obj.siblings().find('.marker').on('click', function () {
state.current = jQuery(this).attr('data-href');
state.paused = false;
fn.go(state.current, $obj, state);
});
}
// Previous
wrap.find('.prev').on('click', function (e) {
state.current = state.prev;
state.paused = false;
fn.go(state.current, $obj, state);
});
// Next
wrap.find('.next').on('click', function (e) {
state.current = state.next;
state.paused = false;
fn.go(state.current, $obj, state);
});
/*
// Play/Pause
wrap.find('.pause').on('click', function (e) {
jQuery(this).activate('play')
.deactivate('pause')
.text('Play');
state.paused = true;
clearInterval(state.interval);
console.log(state.paused);
});
wrap.find('.play').on('click', function (e) {
jQuery(this).activate('pause')
.deactivate('play')
.text('Pause');
state.paused = false;
fn.updateinterval($obj, state);
console.log(state.paused);
});
*/
// Pause/showcontrols
wrap.on({
'mouseover': function () {
state.active = true;
if (o.controls.pauseonhover) {
state.paused = true;
}
if (o.controls.autodim)
wrap.activate();
window.clearTimeout(wrap.timeout);
},
'mouseout': function () {
state.active = false;
if (o.controls.pauseonhover) {
state.paused = false;
}
if (o.controls.autodim) {
wrap.timeout = window.setTimeout(function () {
wrap.deactivate();
}, o.controls.delay * 1000);
}
}
});
// Keyboard
if (o.controls.keyboard) {
jQuery(document).on('keyup', function (e) {
// console.log(e.which);
var keys = [
37, // left
39 // right
//38, // up
//40 // down
];
if (keys.indexOf(e.which) !== -1) {
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
fn.go(state.current, $obj, state);
}
});
}
/*
// Swipe
if (o.controls.swipe) {
$obj.on({
'mousedown touchstart': function (e) {
state.paused = true;
if (e.touches) {
eX = e.touches[0].clientX;
eY = e.touches[0].clientY;
}
else {
eX = e.pageX;
eY = e.pageY;
}
},
'mouseup touchmove': function (e) {
if (!eX || !eY) {
return;
}
var margin = 20,
Xdiff,
Ydiff;
if (e.touches) {
Xdiff = eX - e.touches[0].clientX;
Ydiff = eY - e.touches[0].clientY;
}
else {
Xdiff = eX - e.pageX;
Ydiff = eY - e.pageY;
}
// Detect horizontal or vertical
if (Math.abs(Xdiff) > Math.abs(Ydiff)) {
// Horizontal (left : right)
if (Xdiff < margin) {
// right
state.current = state.next;
}
else if (Xdiff > margin) {
// left
state.current = state.prev;
}
} else {
if (Ydiff < margin) {
// down
state.current = state.next;
}
else if (Ydiff > margin) {
// up
state.current = state.prev;
}
}
// Reset vars for next swipe
eX = null;
eY = null;
// Move to next slide
state.paused = false;
fn.go(state.current, $obj, state);
}
});
}
*/
};
/**
* Set height explicitly to prevent 'jumping' content.
*
* @param object $obj
* @param object state
*/
fn.setheight = function ($obj, state) {
jQuery(window).on('load', function () {
if (o.height === 'auto') {
$obj.find('.content').each(function () {
var tHeight = jQuery(this).height();
if (tHeight > state.maxheight) {
state.maxheight = tHeight;
}
});
}
else {
state.maxheight = o.height;
}
$obj.height(state.maxheight);
});
};
/**
* Generate markup for controls & other elements.
*
* @param object $obj
* @param object state
*/
fn.style = function ($obj, state) {
var li = $obj.find('> li');
$obj.addClass(cellular.opts.cclass)
.wrap('<div class="' + cellular.opts.cclass + ' ' + o.cclass + '-wrap" />');
li.addClass('slide')
.each(function () {
jQuery(this).children().wrapAll('<div class="content cell" />');
});
fn.setheight($obj, state);
if (o.controls.showmarkers) {
var markers = jQuery('<ul class="markers"/>');
for (var i = 0; i < li.length; i += 1) {
markers.append('<li class="marker" data-href="' + i + '">' + (i + 1) + '</li>');
}
$obj.after(markers);
fn.mark($obj, state);
}
if (o.caption.enable) {
/*
if (o.caption.selector === 'auto') {
// o.caption.selector = what?
}
else {
$obj.find(o.caption.selector).hide();
}
*/
$obj.find(o.caption.selector).hide();
$obj.after('<div class="caption"><p/></div>');
}
if (o.controls.showcontrols) {
var controls = [
fn.button(o.controls.text.prev),
fn.button(o.controls.text.next)
//o.autoplay ? fn.button(o.controls.text.pause) : null
],
i;
for (i = 0; i < controls.length; i += 1) {
$obj.parent().prepend(controls[i]);
}
}
};
/**
* Init jScrolli
*/
fn.init = function () {
var $obj = jQuery(this),
state = {
active: true,
paused: false,
count: $obj.find('> li').length - 1,
//height: o.height ? o.height : fn.setheight($obj, state),
width: o.width ? o.width : $obj.width(),
maxheight: 0,
interval: 0,
controls: 0,
caption: jQuery(o.caption.selector).html(),
current: o.active ? o.active : 0
};
// o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
// Add markup
$obj.once(o.cclass, function () {
fn.style($obj, state);
});
// Add Event Listeners
fn.events($obj, state);
// Activate 1st slide
fn.go(state.current, $obj, state);
// Start autoplay
fn.updateinterval($obj, state);
};
return this.each(fn.init);
};

 // :)
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

 // :)
jQuery.fn.extend(cellular);

 // :)
//Drupal.behaviors.cellular = {
//attach: function (context, settings) {
}
};

 // :)
})(jQuery);