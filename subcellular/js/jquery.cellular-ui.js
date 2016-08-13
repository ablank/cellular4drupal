(function(a,b){/**
* @file
* CellularUI Javascript Library
* 
* @author Adam Blankenship <i.adambear@gmail.com>
* 
* @see http://live-cellular.gotpantheon.com/cellular-ui
*/
(function(a){var b={};b.opts={cclass:"cellular",activeclass:"active",breakpoint:"window_mobile"};b.state={breakpoint:0,scrolltop:0,scrolltimer:0};/**
* Cellular utility functions
*/
/**
* Auto invoke
*/
(function(){
// Scroll to page anchors.
jQuery('a[href^="#"]').on("click",function(a){var b=jQuery(this).attr("href");a.preventDefault();jQuery("html, body").stop().animate({scrollTop:jQuery(b).offset().top},1500)})})();/**
* Get the breakpoints specified in CSS
*/
b.breakpoint=function(){var a=window.getComputedStyle(document.querySelector("body"),":before").getPropertyValue("content");return{size:a.match(/\d/g).join(""),type:a.match(/\w*[^\"\'](?=-)/g).join("")}};/**
* Add active class to element, remove active class from element siblings
*/
b.activate=function(a){a=a?a:b.opts.activeclass;return this.each(function(){var b=jQuery(this);if(!b.hasClass(a)){b.addClass(a).siblings().removeClass(a)}})};/**
* Remove 'active' class
*/
b.deactivate=function(a){a=a?a:b.opts.activeclass;return this.each(function(){jQuery(this).removeClass(a)})};/**
* Wrap element's children after 1st child
*/
b.kidWrap=function(){return this.each(function(){var a=jQuery(this);if(a.children().length>1){a.children(":gt(0)").wrapAll("<div>")}})};/**
* Add array of classes to element
*/
b.classify=function(a){return this.each(function(){jQuery(this).addClass(a.join(" "))})};/**
* Debounce fn borrowed from Underscore.js
*/
b.debounce=function(a,b,c){var d;return function(){var e=this,f=arguments,g=function(){d=null;if(!c){a.apply(e,f)}},h=c&&!d;clearTimeout(d);d=setTimeout(g,b);if(h){a.apply(e,f)}}};/**
* Detect css transition end event.
* @see Function from David Walsh: http://davidwalsh.name/css-animation-callback
*/
b.transitionend=function(){var a,b=document.createElement("test"),c={transition:"transitionend",OTransition:"oTransitionEnd",MozTransition:"transitionend",WebkitTransition:"webkitTransitionEnd"};for(a in c){if(b.style[a]!==undefined){return c[a]}}};/**
* Reset scroll timer
*/
b.scrolltimer=function(a,c,d){window.clearTimeout(b.state.scrolltimer);b.state.scrolltimer=window.setTimeout(function(){a.removeClass(c+" "+d)},2e3)};/**
*
* @param {string} href
* @param {string} title
* @param {array} classes
* @returns {string}
*/
b.buttonize=function(b,c,d){var e=a("<a />").attr("href",b).attr("title",c).text(c).classify(d);return a(this).append(e)};/**
* Set state on window resize
*/
b.windowstate=b.debounce(function(){var a=b.state.breakpoint;b.state.breakpoint=b.breakpoint().type;jQuery("body").removeClass(a).addClass(b.state.breakpoint)},100);/**
* Set state on document scroll
*/
b.scrollstate=b.debounce(function(a,c){var d=jQuery("body"),e="scrolling",f=e+"-up",g=e+"-down",h=jQuery(document).scrollTop(),i=d.height()/3,
//y = cellular.state.scrolltop,
j=null;if(h>30){d.addClass("scrolled")}else{d.removeClass("scrolled")}if(h>b.state.scrolltop){d.addClass(g).removeClass(f)}else{d.addClass(f).removeClass(g)}
// Detect if page is scrolled
if(h<i){d.removeClass("page-middle page-bottom").addClass("page-top")}else if(h>i&&h<i*2){d.removeClass("page-top page-bottom").addClass("page-middle")}else{d.removeClass("page-top page-middle").addClass("page-bottom")}
//Update global state
b.state.scrolltop=h;
// % of doc scrolled
b.state.scrolled=h/(d.height()-jQuery(window).height())*100},0,true);(function c(){
// Get initial state
b.windowstate();b.scrollstate();
// Update state on user interaction
jQuery(window).on("resize",b.windowstate);jQuery(document).on("scroll",b.scrollstate)})();b.jAccordion=function(a){var c=jQuery.extend({active:0,// Index value of initial content to display.
duration:500,// Duration of transition.
easing:"swing",// Type of easing.
single:false,// Allow multiple panels to be opened or only 1?
pclass:"panel"},a),d={};c.pselect="."+c.pclass;/**
* The <li> object to show.
*
* @param object li
*  $('<li>')
*/
d.showContent=function(a){if(c.single){a.siblings().find(c.pselect).slideUp(c.duration,c.easing);a.activate().find(c.pselect).slideDown(c.duration,c.easing)}else{a.toggleClass(b.opts.activeclass).find(c.pselect).slideToggle(c.duration,c.easing)}};/**
* Generate markup for controls & other elements.
*
* @param object $obj
*/
d.style=function(a){a.once("jAccordion",function(){a.find("> li").each(function(){var a=jQuery(this);a.kidWrap();a.children().eq(0).addClass("title");a.children().eq(1).classify([b.opts.cclass,"panel"]);a.find(c.pselect).hide();a.find(".title").click(function(b){b.preventDefault();d.showContent(a)})})})};/**
* Init jAccordion
*/
d.init=function(){var a=jQuery(this);
// Generate markup for accordion
d.style(a);
//Set default content
d.showContent(a.children().eq(c.active))};return this.each(d.init)};b.jCard=function(a){var b=jQuery.extend({cclass:"jCard"},a),c={};c.init=function(){var a=jQuery(this);a.once(b.cclass,function(){var c=a.find("a").eq(0);var d=c.attr("href");if(d!==undefined){var e=jQuery('<a href="'+d+'" />').classify([b.cclass+"-wrap",c.attr("class")?c.attr("class"):null]);
// .data(a.data());
a.wrap(e).find("h2, h3").addClass("title")}});a.on("mouseenter touchstart",function(){jQuery(this).activate()}).on("mouseleave touchend",function(){jQuery(this).deactivate()})};return this.each(c.init)};/**
* jMmenu: Hamburger menu for mobile devices
*/
b.jMmenu=function(a){var c=jQuery.extend({breakpoint:b.opts.breakpoint,// Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
parent:jQuery("body"),// Parent element used to attach menu
cclass:"jMmenu",// Menu class to test
triggertext:"Menu",animateclass:"slide-right",// Type of animation
throttle:101},a),d={};d.mediaQuery=b.debounce(function(a,e){if(c.breakpoint===b.state.breakpoint){var f=a.children([0]),g=null;e.mmenu=true;c.parent.addClass(c.animateclass);if(c.triggertext){g='<span class="'+c.cclass+'-triggertext">'+c.triggertext+"</span>"}a.addClass(c.cclass+"-trigger").append(g);f.addClass(c.cclass+"-menu").prependTo(c.parent)}else{e.mmenu=false;e.active=false;c.parent.removeClass(c.cclass+"-active "+c.cclass+"-inactive "+c.animateclass);a.attr("aria-label","Menu").removeClass(c.cclass+"-trigger");jQuery("."+c.cclass+"-menu").removeClass(c.cclass+"-menu").prependTo(a);jQuery("."+c.cclass+"-triggertext").remove()}d.menutrigger(a,e)},c.throttle);d.menutrigger=function(a,b){var d=[c.cclass+"-active",c.cclass+"-inactive"];if(b.active){a.activate().attr("aria-label","Close Menu");jQuery("."+c.cclass+"-menu").addClass("active");c.parent.addClass(d[0]).removeClass(d[1])}else{a.deactivate().attr("aria-label","Open Menu");jQuery("."+c.cclass+"-menu").removeClass("active");if(b.mmenu){c.parent.addClass(d[1]).removeClass(d[0])}}};d.style=function(a){var b=a.find(">ul"),c=b.find("ul");if(c.length>0){var d=b.find("li ul");d.addClass("child").parent().addClass("parent")}};d.init=function(){var a=jQuery(this),b={active:false,mmenu:false};a.addClass(c.cclass).once(c.cclass,d.style(a));d.mediaQuery(a,b);jQuery(window).on("resize",function(){d.mediaQuery(a,b)});a.on("click",function(){
//console.log(this);
if(b.mmenu){b.active=b.active?false:true;d.menutrigger(a,b)}});jQuery(document).on("keyup",function(c){if(b.active===true&&c.which===27){c.preventDefault();b.active=false;d.menutrigger(a,b)}});jQuery("."+c.cclass+" .parent").on("mouseenter focus",function(a){jQuery(this).addClass("active").children(":gt(0)").addClass("active")});jQuery("."+c.cclass+" .parent").on("mouseleave blur",function(a){jQuery(this).removeClass("active").children(":gt(0)").removeClass("active")});jQuery("."+c.cclass+"-menu .parent a").on("click",function(a){var b=jQuery(this).parent(),c=b.children(":gt(0)");//find('> .child');
if(c.length){a.preventDefault();if(c.hasClass("active")){b.removeClass("active");c.removeClass("active")}else{b.addClass("active");c.addClass("active")}}})};return this.each(d.init)};/**
* jScrolli : Content carousel/slider
*/
b.jScrolli=function(c){var d=a.extend({cclass:"jScrolli",// Object class selector
active:0,// Index of initially selected slide
background:"img:first",// Selector for applying background image
title:"h2, h3",// Selector for applying title class
//width: "100%", // 'auto' or '[value]', i.e. '300px'
height:"auto",// 'auto' or '[value]', i.e. '300px'
controls:{showmarkers:true,showcontrols:true,keyboard:true,swipe:true,autoplay:true,pauseonhover:true,autodim:true,delay:1.4,// Time (seconds) to wait before dimming.
text:{next:"Next",prev:"Prev",pause:"Pause",play:"Play"}},transition:{pause:5},caption:{enable:true,autohide:false,selector:".caption"}},c),e={};/**
* Format html buttons for controls.
*
* @param string $text
* @returns string
*/
e.button=function(a){return'<a class="'+d.cclass+"-control "+a.toLowerCase()+'">'+a+"</a>"};/**
* Update next/prev slides.
*
* @param object state
*/
e.normalize=function(a){a.prev=a.current-1;a.next=a.current+1;if(a.prev<0){a.prev=a.count}if(a.next>a.count){a.next=0}};/**
* Activate selected slide & corresponding marker.
*
* @param int index
* @param object $obj
* @param object state
*/
e.go=function(a,c,f){if(!f.paused){var g="transition",h=c.find("."+d.cclass+"-slide");f.current=parseInt(a);
// Normalize state
e.normalize(f);
// Update classes on slides for css transition
jQuery(h[f.prev]).activate("previous");jQuery(h[f.next]).activate("next");jQuery(h[a]).activate();
// Listen for transition to complete & update classes
c.parent().addClass(g).on(b.transitionend(),function(){jQuery(this).removeClass(g)});
// Update the marker
if(d.controls.showmarkers){e.mark(c,f)}
// Update the caption
if(d.caption.enable){e.caption(h,f)}
// Reset the autoplay timer
if(d.controls.autoplay){e.updateinterval(c,f)}}};/**
* Update the current marker.
*/
e.mark=function(a,b){a.siblings().find("."+d.cclass+"-marker").eq(b.current).activate()};/**
* Update slide caption
*/
e.caption=function(c,e){var f=c.parent().parent(),g=f.find("> .caption p");
// Get current slide's caption
e.caption=f.find(d.caption.selector).eq(e.current).text();g.on(b.transitionend(),function(){
// Update the active caption
a(this).text(e.caption).activate()})};/**
* Reset autoplay timer.
*/
e.updateinterval=function(a,b){if(d.controls.autoplay&&!b.paused){clearInterval(b.interval);b.interval=setInterval(function(){b.current=b.next;e.go(b.current,a,b)},d.transition.pause*1e3)}};/**
* Add event listeners
*
* @param {type} $obj
* @param {type} state
*/
e.events=function(a,b){var c=a.siblings(".controls"),f=a.parent(),g=null,h=null;
// Link markers to respective slides
if(d.controls.showmarkers){a.siblings().find("."+d.cclass+"-marker").on("click",function(){b.current=jQuery(this).attr("data-href");b.paused=false;e.go(b.current,a,b)})}
// Previous
f.find(".prev").on("click",function(c){b.current=b.prev;b.paused=false;e.go(b.current,a,b)});
// Next
f.find(".next").on("click",function(c){b.current=b.next;b.paused=false;e.go(b.current,a,b)});/*
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
f.on({mouseover:function(){b.active=true;if(d.controls.pauseonhover){b.paused=true}if(d.controls.autodim){f.activate();window.clearTimeout(f.timeout)}},mouseout:function(){b.active=false;if(d.controls.pauseonhover){b.paused=false}if(d.controls.autodim){f.timeout=window.setTimeout(function(){f.deactivate()},d.controls.delay*1e3)}}});
// Keyboard
if(d.controls.keyboard){jQuery(document).on("keyup",function(c){var d=[37,// left
39];if(d.indexOf(c.which)!==-1){c.preventDefault();b.paused=false;switch(c.which){case 37:b.current=b.prev;break;case 39:b.current=b.next;break}e.go(b.current,a,b)}})}};/**
* Set height explicitly to prevent 'jumping' content.
*
* @param object $obj
* @param object state
*/
e.setheight=function(a,b){jQuery(document).ready(function(){if(d.height==="auto"){a.find("> li").each(function(){var a=this.clientHeight;if(a>b.maxheight){b.maxheight=a}})}else{b.maxheight=d.height}a.height(b.maxheight)})};/**
* Generate markup for controls & other elements.
*
* @param object $obj
* @param object state
*/
e.style=function(a,c){var f=a.find("> li");a.addClass(b.opts.cclass).wrap('<div class="'+b.opts.cclass+" "+d.cclass+'-wrap" />');f.addClass(d.cclass+"-slide").each(function(){var a=jQuery(this);a.children().wrapAll('<div class="'+d.cclass+'-slide-content cell" />');if(d.title){a.find(d.title).addClass("title")}if(d.background){var b=a.find(d.background);if(b.length){b.hide();a.css({"background-image":"url("+b.attr("src")+")"}).addClass(d.cclass+"-background")}}});e.setheight(a,c);if(d.controls.showmarkers){var g=jQuery('<ul class="'+d.cclass+'-markers"/>');for(var h=0;h<f.length;h+=1){g.append('<li class="'+d.cclass+'-marker" data-href="'+h+'">'+(h+1)+"</li>")}a.after(g);e.mark(a,c)}if(d.caption.enable){var i=a.find(d.caption.selector);if(i.length){i.hide();a.after('<div class="'+d.cclass+'-caption"><p/></div>')}}if(d.controls.showcontrols){var j,k=[e.button(d.controls.text.prev),e.button(d.controls.text.next)];for(j=0;j<k.length;j+=1){a.parent().prepend(k[j])}}};/**
* Init jScrolli
*/
e.init=function(){var a=jQuery(this),b={active:true,paused:false,count:a.find("> li").length-1,
//height: o.height ? o.height : fn.setheight($obj, state),
width:d.width?d.width:a.width(),maxheight:0,interval:0,controls:0,caption:jQuery(d.caption.selector).html(),current:d.active?d.active:0};
// o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
// Add markup
a.once(d.cclass,function(){e.style(a,b)});
// Add Event Listeners
e.events(a,b);
// Activate 1st slide
e.go(b.current,a,b);
// Start autoplay
e.updateinterval(a,b)};return this.each(e.init)};b.jSocial=function(b){var c=document.title,d=a("link[rel='canonical']")?a("link[rel='canonical']").attr("href"):window.location;var e=jQuery.extend({sharetitle:"",// "Share this page",
followtitle:"",// "Follow Us",
buttonclass:"social",share:[],follow:{}},b),f={};/**
* Generate markup for buttons.
*
* @param object $obj
*/
f.style=function(b){b.once("jSocial",function(){if(e.share){var f=a('<div class="jSocial-share" />'),g,h={facebook:{title:"Facebook",url:"http://facebook.com/sharer/sharer.php?u="+d},digg:{title:"Digg",url:"http://digg.com/submit?url="+d+"&title="+c},google:{title:"Google",url:"https://plus.google.com/share?url="+d},twitter:{title:"Twitter",url:"https://twitter.com/intent/tweet?url="+d+"&text="+c},linkedin:{title:"LinkedIn",url:"http://linkedin.com/shareArticle?url="+d+"&title="+c},pinterest:{title:"Pinterest",url:"http://pinterest.com/pin/create/bookmarklet/?url="+d+"&description="+c},reddit:{title:"Reddit",url:"http://reddit.com/submit?url="+d+"&title="+c},stumbleupon:{title:"StumbleUpon",url:"http://www.stumbleupon.com/submit?url="+d+"&title="+c},tumblr:{title:"Tumblr",url:"https://www.tumblr.com/widgets/share/tool?canonicalUrl="+d+"&title="+c}};if(e.sharetitle){f.append('<span class="title">'+e.sharetitle+"</span>");g=e.sharetitle+" on "}e.share.map(function(a){f.buttonize(h[a].url,g+h[a].title,[h[a].title.toLowerCase(),e.buttonclass,"icon"])});b.append(f)}if(Object.keys(e.follow)!=="undefined"){var i=a('<div class="jSocial-follow" />'),j="";if(e.followtitle){i.append('<span class="title">'+e.followtitle+"</span>");j=e.followtitle+" on "}a.each(e.follow,function(){i.buttonize(this.url,j+this.title,[this.title.replace(/ /g,"").toLowerCase(),e.buttonclass,"icon"])});b.append(i)}})};/**
* Init jSocial
*/
f.init=function(){
// Generate markup for links.
f.style(jQuery(this))};return this.each(f.init)};/**
* jTabs : Tabify a list of content
*/
b.jTabs=function(a){var b=jQuery.extend({active:0,// Array index of initially active tab
orient:"horizontal",// || "vertical"
cclass:"jTabs"},a),c={};/**
*
*
* @param object $obj
* @param object li
*/
c.showContent=function(a,b){var c=b.find(".content"),d=a.parent().find(".panel-content");b.activate();d.fadeOut("normal",function(){jQuery(this).html(c.html()).fadeIn("normal")})};/**
* Init jTabs
*/
c.init=function(){var a=jQuery(this),d=a.find("> li"),e=jQuery("<div/>").classify([b.orient,b.cclass+"-wrap"]),f='<div class="panel"><div class="panel-content" /></div>';a.once(b.cclass,function(){a.wrap(e).after(f);d.each(function(){var a=jQuery(this);a.addClass("tab").kidWrap();
//Set 1st child as title
a.children().eq(0).addClass("title");
//Set wrapper as content
a.children().eq(1).addClass("content").hide()})});
//Add classes/functions to each panel
d.each(function(){var b=jQuery(this);b.click(function(d){d.preventDefault();c.showContent(a,b)})});
//Set default content
c.showContent(a,d.eq([b.active]))};return this.each(c.init)};b.jTooltip=function(a){var b=jQuery.extend({trigger:"jTooltip-trigger",// Class used to trigger tooltip.
triggerbtn:"jTooltip-trigger-btn",// OR false, used to trigger tooltip
triggerbtntext:"About this",cclass:"jTooltip-tooltip",dataattr:"data-tooltip",bindto:"btn",// OR 'event' OR {}
wrap:true,offsetX:10,offsetY:5},a),c={};/**
* Generate markup for buttons.
*
* @param object $obj
*/
c.style=function(a,c){var d=jQuery("<div>"+a.attr(b.dataattr)+"</div>");if(b.wrap){a.wrap('<div class="'+b.cclass+'-wrap" />')}d.classify([b.cclass]);a.after(d);if(b.triggerbtn!==false){var e=jQuery('<span aria-label="'+b.triggerbtntext+'" />');e.classify([b.trigger,b.triggerbtn]).prop("tabindex",a.prop("tabindex"));a.before(e)}else{a.addClass(b.trigger)}c(a)};c.events=function(a){jQuery("."+b.trigger).on("mouseenter focus",function(a){var c=jQuery(this),d=c.nextAll("."+b.cclass+":first"),e={},f={};switch(b.bindto){case"event":f={top:parseInt(a.clientY)+b.offsetY+"px",left:parseInt(a.clientX)+b.offsetX+"px"};break;case"btn":e=this.getBoundingClientRect();f={top:e.top+c.height()/2+b.offsetY+"px",left:e.left+c.width()+b.offsetX+"px"};break;default:case{}:e={}.getBoundingClientRect();f={top:e.top+c.height()/2+b.offsetY+"px",left:e.left+c.width()/2+b.offsetX+"px"};break}d.css(f).activate()}).on("mouseleave blur",function(a){jQuery(this).nextAll("."+b.cclass+":first").deactivate()})};/**
* Init jSocial
*/
c.init=function(){c.style(jQuery(this),c.events)};return this.each(c.init)};b.jScrollindicator=function(a){var c=jQuery.extend({cclass:"jScrollindicator",orient:"horizontal",// horizontal || vertical
attach:"body",parent:null},a),d={};d.init=function(){var a=jQuery(this),d={scrolled:0};a.once(c.cclass,function(){});a.on("scroll",b.debounce(function(a,b){if(c.parent){console.log(c.parent);var d=jQuery("."+c.cclass),e=d.parent(c.parent),f=jQuery(document).scrollTop();b.scrolled=f/(a.height()-e.height())*100;console.log("scrolled: "+b.scrolled)}},100))};return this.each(d.init)};jQuery.fn.extend(b)})(jQuery);b["true"]=a})({},function(){return this}());