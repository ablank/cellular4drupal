(function(a,b){/**
* @file
* CellularUI Javascript Library
* 
* @author Adam Blankenship <i.adambear@gmail.com>
* 
* @see http://live-cellular.gotpantheon.com/cellular-ui
*/
(function(a){Drupal.behaviors.cellular={attach:function(b,c){var d={};d.opts={cclass:"cellular",activeclass:"active",breakpoint:"window_mobile"};d.state={breakpoint:0,scrolltop:0,scrolltimer:0};/**
* Cellular utility functions
*/
/**
* Get the breakpoints specified in CSS
*/
d.breakpoint=function(){var a=window.getComputedStyle(document.querySelector("body"),":before").getPropertyValue("content"),b;if(a){b={size:a.match(/\d/g).join(""),type:a.match(/\w*[^\"\'](?=-)/g).join("")}}else{
// Provide default breakpoints if they aren't set by css.
var c=jQuery(window).width(),d=[""];switch(c){case c>650&&c<800:
//console.log(ww);
b={size:"",type:""};break;default:b={size:"",type:""};break}}return b};/**
* Add active class to element, remove active class from element siblings
*/
d.activate=function(a){a=a?a:d.opts.activeclass;return this.each(function(){var b=jQuery(this);if(!b.hasClass(a)){b.addClass(a).siblings().removeClass(a)}})};/**
* Remove 'active' class
*/
d.deactivate=function(a){a=a?a:d.opts.activeclass;return this.each(function(){jQuery(this).removeClass(a)})};/**
* Wrap element's children after 1st child
*/
d.kidWrap=function(){return this.each(function(){var a=jQuery(this);if(a.children().length>1){a.children(":gt(0)").wrapAll("<div>")}})};/**
* Add array of classes to element
*/
d.classify=function(a){return this.each(function(){jQuery(this).addClass(a.join(" "))})};/**
* Debounce fn borrowed from Underscore.js
*/
d.debounce=function(a,b,c){var d;return function(){var e=this,f=arguments,g=function(){d=null;if(!c){a.apply(e,f)}},h=c&&!d;clearTimeout(d);d=setTimeout(g,b);if(h){a.apply(e,f)}}};/**
* Detect css transition end event.
* @see Function from David Walsh: http://davidwalsh.name/css-animation-callback
*/
d.transitionend=function(){var a,b=document.createElement("test"),c={transition:"transitionend",OTransition:"oTransitionEnd",MozTransition:"transitionend",WebkitTransition:"webkitTransitionEnd"};for(a in c){if(b.style[a]!==undefined){return c[a]}}};/**
* Reset scroll timer
*/
d.scrolltimer=function(a,b,c){window.clearTimeout(d.state.scrolltimer);d.state.scrolltimer=window.setTimeout(function(){a.removeClass(b+" "+c)},2e3)};/**
*
* @param {string} href
* @param {string} title
* @param {array} classes
* @returns {string}
*/
d.buttonize=function(b,c,d){var e=a("<a />").prop({href:b,title:c,tabindex:"0"}).text(c).classify(d);return a(this).append(e)};/**
*
*/
d.scrollto=function(a,b){a=a||jQuery(this).attr("href");
// Scroll to page anchors.
jQuery('a[href^="#"]').on("click",function(c){c.preventDefault();jQuery("html, body").stop().animate({scrollTop:jQuery(a).offset().top},b)})};/**
* Set state on window resize
*/
d.windowstate=d.debounce(function(){var a=d.state.breakpoint;d.state.breakpoint=d.breakpoint().type;jQuery("body").removeClass(a).addClass(d.state.breakpoint)},100);/**
* Set state on document scroll
*/
d.scrollstate=d.debounce(function(a,b){var c=jQuery("body"),e="scrolling",f=e+"-up",g=e+"-down",h=jQuery(document).scrollTop(),i=c.height()/3,
//y = cellular.state.scrolltop,
j=null;if(h>30){c.addClass("scrolled")}else{c.removeClass("scrolled")}if(h>d.state.scrolltop){c.addClass(g).removeClass(f)}else{c.addClass(f).removeClass(g)}
// Detect if page is scrolled
if(h<i){c.removeClass("page-middle page-bottom").addClass("page-top")}else if(h>i&&h<i*2){c.removeClass("page-top page-bottom").addClass("page-middle")}else{c.removeClass("page-top page-middle").addClass("page-bottom")}
//Update global state
d.state.scrolltop=h;
// % of doc scrolled
d.state.scrolled=h/(c.height()-jQuery(window).height())*100},0,true);(function e(){
// Get initial state
d.windowstate();d.scrollstate();
// Update state on user interaction
jQuery(window).on("resize",d.windowstate);jQuery(document).on("scroll",d.scrollstate)})();d.jAccordion=function(a){var b=jQuery.extend({active:0,// Index value of initial content to display.
duration:500,// Duration of transition.
easing:"swing",// Type of easing.
single:false,// Allow multiple panels to be opened or only 1?
pclass:"panel"},a),c={};b.pselect="."+b.pclass;/**
* The <li> object to show.
*
* @param object li
*  $('<li>')
*/
c.showContent=function(a){if(b.single){a.siblings().find(b.pselect).slideUp(b.duration,b.easing);a.activate().find(b.pselect).slideDown(b.duration,b.easing)}else{a.toggleClass(d.opts.activeclass).find(b.pselect).slideToggle(b.duration,b.easing)}};/**
* Generate markup for controls & other elements.
*
* @param object $obj
*/
c.style=function(a){a.once("jAccordion",function(){a.prop("tabindex","0").find("> li").each(function(){var a=jQuery(this);a.kidWrap();a.children().eq(0).addClass("title");a.children().eq(1).classify([d.opts.cclass,"panel"]);a.find(b.pselect).hide();a.find(".title").click(function(b){b.preventDefault();c.showContent(a)})})})};/**
* Init jAccordion
*/
c.init=function(){var a=jQuery(this);
// Generate markup for accordion
c.style(a);
//Set default content
c.showContent(a.children().eq(b.active))};return this.each(c.init)};d.jCard=function(a){var b=jQuery.extend({cclass:"jCard"},a),c={};c.init=function(){var a=jQuery(this);a.once(b.cclass,function(){var c=a.find("a").eq(0);var d=c.attr("href");if(d!==undefined){var e=jQuery('<a href="'+d+'" tabindex="0" />').classify([b.cclass+"-wrap",c.attr("class")?c.attr("class"):null]);a.wrap(e).find("h2, h3").addClass("title")}});a.on("mouseenter touchstart",function(){a.activate()}).on("mouseleave touchend",function(){a.deactivate()})};return this.each(c.init)};/**
* jFormal: Improve form interaction
*/
d.jFormal=function(a){var b=jQuery.extend({inputs:['input[type="text"]','input[type="email"]','input[type="password"]',"textarea"]},a);return this.each(function(){var a=b.inputs.join(",");
// get/set value of inputs
jQuery(a).each(function(){var a=jQuery(this),b=holder=a.attr("placeholder");a.on("focus",function(){holder="";if(this.value===this.defaultValue){this.value=""}}).on("blur",function(){
// Reset to default value if no changes were made.
holder=b;if(this.value===""||null){this.value=this.defaultValue}})})})};/**
* jMmenu: Hamburger menu for mobile devices
*/
d.jMmenu=function(a){var b=jQuery.extend({breakpoint:d.opts.breakpoint,// 'window_mobile'|| 'window_narrow' || 'window_default'
parent:jQuery("body"),// Parent element used to attach menu
cclass:"jMmenu",// Menu class to test
triggertext:"Menu",animateclass:"slide-right",// Type of animation
throttle:101},a),c={};c.mediaQuery=d.debounce(function(a,e){
//console.log(cellular.opts.breakpoint);
if(b.breakpoint===d.state.breakpoint){var f=a.children([0]),g=null;e.mmenu=true;b.parent.addClass(b.animateclass);if(b.triggertext){g='<span class="'+b.cclass+'-triggertext">'+b.triggertext+"</span>"}a.prop("tabindex","0").addClass(b.cclass+"-trigger").append(g);f.addClass(b.cclass+"-menu").prependTo(b.parent)}else{e.mmenu=false;e.active=false;b.parent.removeClass(b.cclass+"-active "+b.cclass+"-inactive "+b.animateclass);a.attr("aria-label","Menu").removeClass(b.cclass+"-trigger");jQuery("."+b.cclass+"-menu").removeClass(b.cclass+"-menu").prependTo(a);jQuery("."+b.cclass+"-triggertext").remove()}c.menutrigger(a,e)},b.throttle);c.menutrigger=function(a,c){var d=[b.cclass+"-active",b.cclass+"-inactive"];if(c.active){a.activate().attr("aria-label","Close Menu");jQuery("."+b.cclass+"-menu").addClass("active");b.parent.addClass(d[0]).removeClass(d[1])}else{a.deactivate().attr("aria-label","Open Menu");jQuery("."+b.cclass+"-menu").removeClass("active");if(c.mmenu){b.parent.addClass(d[1]).removeClass(d[0])}}};c.style=function(a){var b=a.find(">ul"),c=b.find("ul");
// Add classes for parent/child.
if(c.length>0){var d=b.find("li ul");d.addClass("child").parent().addClass("parent").css({willChange:"contents"})}};c.listen=function(a,d){jQuery(window).on("resize",function(){c.mediaQuery(a,d)});a.on("click",function(){if(d.mmenu){d.active=d.active?false:true;c.menutrigger(a,d)}});jQuery(document).on("keyup",function(e){
// ENTER opens menu.
if(jQuery("."+b.cclass+"-trigger").is(":focus")&&e.which===13){e.preventDefault();d.active=d.active===false?true:false;c.menutrigger(a,d)}
// ESC closes menu.
if(d.active===true&&e.which===27){e.preventDefault();d.active=false;c.menutrigger(a,d)}});jQuery(".parent > a").click(function(a){if(d.mmenu){var b=jQuery(this).parent(),c=b.children(":gt(0)");if(c.length>0){a.preventDefault();if(c.hasClass("active")){b.removeClass("active");c.removeClass("active")}else{b.addClass("active");c.addClass("active")}}}})};c.init=function(){var a=jQuery(this),d={active:false,mmenu:false};a.addClass(b.cclass).once(b.cclass,c.style(a));c.mediaQuery(a,d);c.listen(a,d)};return this.each(c.init)};/**
* jScrolli : Content carousel/slider
*/
d.jScrolli=function(b){var c=a.extend({cclass:"jScrolli",// Object class selector
active:0,// Index of initially selected slide
background:"img:first",// Selector for applying background image
title:"h2, h3",// Selector for applying title class
//width: "100%", // 'auto' or '[value]', i.e. '300px'
height:"auto",// 'auto' or '[value]', i.e. '300px'
controls:{showmarkers:true,showcontrols:true,keyboard:true,swipe:true,autoplay:true,pauseonhover:true,autodim:true,delay:1.4,// Time (seconds) to wait before dimming.
text:{next:"Next",prev:"Prev",pause:"Pause",play:"Play"}},transition:{pause:5},caption:{enable:true,autohide:false,selector:".caption"}},b),e={};/**
* Format html buttons for controls.
*
* @param string $text
* @returns string
*/
e.button=function(a){return'<a class="'+c.cclass+"-control "+a.toLowerCase()+'">'+a+"</a>"};/**
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
e.go=function(a,b,f){if(!f.paused){var g="transition",h=b.find("."+c.cclass+"-slide");
// Unset tabindexes
h.find("a").prop("tabindex","-1");
// Get current slide.
f.current=parseInt(a);
// Normalize state.
e.normalize(f);
// Update classes on slides for css transition.
jQuery(h[f.prev]).activate("previous");jQuery(h[f.next]).activate("next");jQuery(h[a]).activate().find("a").prop("tabindex","-1");
// Listen for transition to complete & update classes.
b.parent().addClass(g).on(d.transitionend(),function(){jQuery(this).removeClass(g)});
// Update the marker
if(c.controls.showmarkers){e.mark(b,f)}
// Update the caption
if(c.caption.enable){e.caption(h,f)}
// Reset the autoplay timer
if(c.controls.autoplay){e.updateinterval(b,f)}}};/**
* Update the current marker.
*/
e.mark=function(a,b){a.siblings().find("."+c.cclass+"-marker").eq(b.current).activate()};/**
* Update slide caption
*/
e.caption=function(b,e){var f=b.parent().parent(),g=f.find("> .caption p");
// Get current slide's caption
e.caption=f.find(c.caption.selector).eq(e.current).text();g.on(d.transitionend(),function(){
// Update the active caption
a(this).text(e.caption).activate()})};/**
* Reset autoplay timer.
*/
e.updateinterval=function(a,b){if(c.controls.autoplay&&!b.paused){clearInterval(b.interval);b.interval=setInterval(function(){b.current=b.next;e.go(b.current,a,b)},c.transition.pause*1e3)}};/**
* Add event listeners
*
* @param {type} $obj
* @param {type} state
*/
e.events=function(a,b){var d=a.siblings(".controls"),f=a.parent(),g=null,h=null;
// Link markers to respective slides
if(c.controls.showmarkers){a.siblings().find("."+c.cclass+"-marker").on("click",function(){b.current=jQuery(this).attr("data-href");b.paused=false;e.go(b.current,a,b)})}
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
f.on({mouseover:function(){b.active=true;if(c.controls.pauseonhover){b.paused=true}if(c.controls.autodim){f.activate();window.clearTimeout(f.timeout)}},mouseout:function(){b.active=false;if(c.controls.pauseonhover){b.paused=false}if(c.controls.autodim){f.timeout=window.setTimeout(function(){f.deactivate()},c.controls.delay*1e3)}}});
// Keyboard
if(c.controls.keyboard){jQuery(document).on("keyup",function(c){var d=[37,// left
39];if(d.indexOf(c.which)!==-1){c.preventDefault();b.paused=false;switch(c.which){case 37:b.current=b.prev;break;case 39:b.current=b.next;break}e.go(b.current,a,b)}})}};/**
* Set height explicitly to prevent 'jumping' content.
*
* @param object $obj
* @param object state
*/
e.setheight=function(a,b){jQuery(document).ready(function(){if(c.height==="auto"){a.find("> li").each(function(){var a=this.clientHeight;if(a>b.maxheight){b.maxheight=a}})}else{b.maxheight=c.height}a.height(b.maxheight)})};/**
* Generate markup for controls & other elements.
*
* @param object $obj
* @param object state
*/
e.style=function(a,b){var f=a.find("> li");a.prop("tabindex","0").addClass(d.opts.cclass).wrap('<div class="'+d.opts.cclass+" "+c.cclass+'-wrap" />').parent().css({willChange:"contents"});f.prop("tabindex","-1").addClass(c.cclass+"-slide").each(function(){var a=jQuery(this);a.children().wrapAll('<div class="'+c.cclass+'-slide-content cell" />');if(c.title){a.find(c.title).addClass("title")}if(c.background){var b=a.find(c.background);if(b.length){b.hide();a.css({"background-image":"url("+b.attr("src")+")"}).addClass(c.cclass+"-background")}}});e.setheight(a,b);if(c.controls.showmarkers){var g=jQuery('<ul class="'+c.cclass+'-markers"/>');for(var h=0;h<f.length;h+=1){g.append('<li class="'+c.cclass+'-marker" data-href="'+h+'">'+(h+1)+"</li>")}a.after(g);e.mark(a,b)}if(c.caption.enable){var i=a.find(c.caption.selector);if(i.length){i.hide();a.after('<div class="'+c.cclass+'-caption"><p/></div>')}}if(c.controls.showcontrols){var j,k=[e.button(c.controls.text.prev),e.button(c.controls.text.next)];for(j=0;j<k.length;j+=1){a.parent().prepend(k[j])}}};/**
* Init jScrolli
*/
e.init=function(){var a=jQuery(this),b={active:true,paused:false,count:a.find("> li").length-1,
//height: o.height ? o.height : fn.setheight($obj, state),
width:c.width?c.width:a.width(),maxheight:0,interval:0,controls:0,caption:jQuery(c.caption.selector).html(),current:c.active?c.active:0};
// o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
// Add markup
a.once(c.cclass,function(){e.style(a,b)});
// Add Event Listeners
e.events(a,b);
// Activate 1st slide
e.go(b.current,a,b);
// Start autoplay
e.updateinterval(a,b)};return this.each(e.init)};d.jSocial=function(b){var c=document.title,d=a("link[rel='canonical']")?a("link[rel='canonical']").attr("href"):window.location;var e=jQuery.extend({sharetitle:"",// "Share this page",
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
d.jTabs=function(a){var b=jQuery.extend({active:0,// Array index of initially active tab
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
c.showContent(a,d.eq([b.active]))};return this.each(c.init)};d.jModal=function(b){var c=jQuery.extend({cclass:"jModal",dataattr:"data-modal",groupattr:"data-album",offsetX:10,// % or vw
offsetY:10,// % or vh
//caption: "data-caption",
//timeout: 10000,
//fitImg: true, // Scale images to user viewport.
trigger:"click"},b),d={};/**
*
*/
d.load=function(b,d){var e=jQuery("."+c.cclass+"-window"),f=jQuery("#"+c.cclass+"-overlay"),g=e.find("."+c.cclass+"-content"),h;
// show loading icon
d.active=true;f.activate();
// determine content source
if(typeof b.attr(c.dataattr)!=="undefined"){h=b.attr(c.dataattr)}else if(b.attr("href")!=="undefined"){h=b.attr("href")}
// load content
a.ajax({url:h,context:document.body,timeout:c.timeout,success:function(a){console.log(a);
// Remove loading icon
// Re-position/re-size window to fit content
e.css({height:100-c.offsetY*2+"vh",width:100-c.offsetX*2+"vw",top:c.offsetY+"vh",left:c.offsetX+"vw"});
// Show content
g.html(a).activate()},error:function(a,b){d.activate=false;f.deactivate();console.log("AJAX Request failed: "+b)}})};d.close=function(a){var b=jQuery("#"+c.cclass+"-overlay");a.active=false;b.deactivate().find("."+c.cclass+"-window").deactivate();b.find("."+c.cclass+"-content").deactivate().html("")};/**
* Generate markup for controls & other elements.
*
* @param object $obj
*/
d.style=function(a){var b=jQuery('<div class="'+c.cclass+'-window" />').append('<div class="'+c.cclass+'-content" />').append('<span class="'+c.cclass+'-close" aria-label="Close" />'),d=jQuery('<div id="'+c.cclass+'-overlay" />').append(b);if(!jQuery("#"+c.cclass+"-overlay").length){jQuery("body").append(d)}};/**
*
*/
d.events=function(a,b){a.on("click",function(c){c.preventDefault();d.load(a,b)});jQuery(document).on("keyup",function(a){if(b.active===true&&a.which===27){d.close(b)}});jQuery("#"+c.cclass+"-overlay, ."+c.cclass+"-close").on("click",function(){d.close(b)})};/**
* Init jModal
*/
d.init=function(){var a=jQuery(this),b={active:false,group:c.groupattr.length?c.groupattr:null};
// Generate markup for modal
jQuery("."+c.cclass).once(c.cclass,d.style(a));
// Listen for events
d.events(a,b)};return this.each(d.init)};jQuery.fn.extend(d)}}})(jQuery);b["true"]=a})({},function(){return this}());