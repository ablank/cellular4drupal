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
tclass: "title",
bclass: "body",
wrapper: "<div />",
speed: 300,
breakpoint: 'mobile'
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
if ($t.hasClass('active')) {
return;
} else {
$t.addClass('active')
.siblings().removeClass('active');
}
});
};
cellular.deactivate = function () {
return this.each(function () {
var $t = jQuery(this);
if ($t.hasClass('active')) {
$t.removeClass('active');
}
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
var $t = jQuery(this);
var classes = $array.join(' ');
$t.addClass(classes);
});
};
cellular.throttle = function (fn, delay) {
var timer = null;
delay = delay ? delay : 250;
return function () {
var context = this, args = arguments;
clearTimeout(timer);
timer = setTimeout(function () {
fn.apply(context, args);
}, delay);
};
};
cellular.cycle = function (dir) {
var $obj = jQuery(this),
kids = $obj.children(),
count = -1,
next;
if (dir === "next") {
next = kids.next();
if (next.length < 1) {
next = kids[count += 1 % kids.length];
}
}
if (dir === "prev") {
next = kids.prev();
if (next.length < 1) {
next = kids[kids.length];
}
}
return next;
};

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
return this.each(function () {
var $obj = jQuery(this);
var li = $obj.find('li');
//fn.style($obj);
//Add classes/functions to each pane
$obj.once('jAccordion', function () {
$obj.addClass(cellular.opts.cclass);
li.each(function () {
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
//Set default content
fn.showContent($obj.children().eq(o.active));
});
};

 // :)
cellular.jBlocklink = function (opts) {
var o = jQuery.extend({
"cclass": "jBlocklink-link"
}, opts);
return this.each(function () {
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
});
};

 // :)
cellular.jEqualheight = function (opts) {
/*
var array = [267, 306, 108];
var largest = Math.max.apply(Math, array); // 306
*/
var o = jQuery.extend({
//"opt": val
}, opts);
return this.each(function () {
var $obj = jQuery(this);
var kids = $obj.find('>*');
var maxHeight = 0;
kids.each(function () {
$t = jQuery(this);
if ($t.height() > maxHeight) {
maxHeight = $t.height();
}
$t.height(maxHeight);
});
});
};

 // :)
cellular.jMmenu = function (opts) {
var o = jQuery.extend({
breakpoint: cellular.opts.breakpoint, // Window breakpoint trigger
parent: jQuery('body'), // Parent element used to attach menu
cclass: "jMmenu", // Menu class to test
type: "slide", // Type of animation
direction: "right" // Direction of animation
}, opts),
fn = {
classes: [
o.type + '-' + o.direction,
o.cclass + '-active',
o.cclass + '-inactive'
]
};
fn.mediaQuery = function ($obj) {
//console.log('break: ' + cellular.breakpoint());
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
return this.each(function () {
var $obj = jQuery(this);
var $window = jQuery(window);
fn.mediaQuery($obj);
$window.on('resize', function () {
fn.mediaQuery($obj);
});
$obj.on('click', function () {
if (o.parent.hasClass(fn.classes[0])) {
o.parent.toggleClass(fn.classes[1])
.toggleClass(fn.classes[2]);
$obj.toggleClass('active');
}
});
});
};

 // :)
cellular.jScrolli = function (opts) {
o = $.extend({
"active": 0,
"speed": 500, // Duration of cycle
"pause": 3000 // Time to pause between cycles
}, opts);
/*Math.max.apply(Math, array)*/
var fn = {};
//fn.style = function(){};
return this.each(function () {
var $obj = jQuery(this);
var $i = $obj.find('> li');
var active = o.active ? o.active : $i[0];
var maxHeight = 0;
$i.each(function () {
$t = jQuery(this);
// Set maxHeight equal to greatest element.
if ($t.height() > maxHeight) {
maxHeight = $t.height();
}
$t.hide();
});
$obj.addClass(cellular.opts.cclass)
.height(maxHeight)
.once(cellular.opts.cclass, function () {
$i.kidWrap();
});
jQuery(active).activate()
.fadeIn(o.speed, function () {
var $t = jQuery(this);
var next = $t.next();
if (next.length === 0) {
next = $i[0];
}
$t.delay(o.pause)
.fadeOut(o.speed, function () {
$t.deactivate();
$obj.jScrolli({
"active": next,
"speed": o.speed,
"pause": o.pause
});
});
});
});
};

 // :)
cellular.jTabs = function (opts) {
var o = jQuery.extend({
"active": 0, // Array index of initially active tab
"orient": "horizontal" // || 'vertical'
}, opts);
var fn = {};
fn.showContent = function (li) {
//Content
var c = li.find('.content');
//Display
var pan = li.parent().find('.panel-content');
li.activate();
pan.fadeOut('normal', function () {
jQuery(this).html(c.html())
.fadeIn('normal');
});
};
return this.each(function () {
var $obj = jQuery(this);
var tab = $obj.find('> li');
var maxHeight = 0;
$obj.addClass(cellular.opts.cclass)
.height(maxHeight);
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
});
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