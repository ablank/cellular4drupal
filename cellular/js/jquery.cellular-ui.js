!function(a,b){/**
* @file
* CellularUI Javascript Library
* 
* @author Adam Blankenship <i.adambear@gmail.com>
* 
* @see http://live-cellular.gotpantheon.com/cellular-ui
*/
!function(a){Drupal.behaviors.cellular={attach:function(b,c){var d={};d.opts={cclass:"cellular",activeclass:"active",breakpoint:"window_mobile"},d.state={breakpoint:0,scrolltop:0,scrolltimer:0},/**
* Cellular utility functions
*/
/**
* Auto invoke
*/
function(){
// Scroll to page anchors.
jQuery('a[href^="#"]').on("click",function(a){var b=jQuery(this).attr("href");a.preventDefault(),jQuery("html, body").stop().animate({scrollTop:jQuery(b).offset().top},1500)})}(),/**
* Get the breakpoints specified in CSS
*/
d.breakpoint=function(){var a=window.getComputedStyle(document.querySelector("body"),":before").getPropertyValue("content");return{size:a.match(/\d/g).join(""),type:a.match(/\w*[^\"\'](?=-)/g).join("")}},/**
* Add active class to element, remove active class from element siblings
*/
d.activate=function(a){return a=a?a:d.opts.activeclass,this.each(function(){var b=jQuery(this);b.hasClass(a)||b.addClass(a).siblings().removeClass(a)})},/**
* Remove 'active' class
*/
d.deactivate=function(a){return a=a?a:d.opts.activeclass,this.each(function(){jQuery(this).removeClass(a)})},/**
* Wrap element's children after 1st child
*/
d.kidWrap=function(){return this.each(function(){var a=jQuery(this);a.children().length>1&&a.children(":gt(0)").wrapAll("<div>")})},/**
* Add array of classes to element
*/
d.classify=function(a){return this.each(function(){jQuery(this).addClass(a.join(" "))})},/**
* Debounce fn borrowed from Underscore.js
*/
d.debounce=function(a,b,c){var d;return function(){var e=this,f=arguments,g=function(){d=null,c||a.apply(e,f)},h=c&&!d;clearTimeout(d),d=setTimeout(g,b),h&&a.apply(e,f)}},/**
* Detect css transition end event.
* @see Function from David Walsh: http://davidwalsh.name/css-animation-callback
*/
d.transitionend=function(){var a,b=document.createElement("test"),c={transition:"transitionend",OTransition:"oTransitionEnd",MozTransition:"transitionend",WebkitTransition:"webkitTransitionEnd"};for(a in c)if(void 0!==b.style[a])return c[a]},/**
* Reset scroll timer
*/
d.scrolltimer=function(a,b,c){window.clearTimeout(d.state.scrolltimer),d.state.scrolltimer=window.setTimeout(function(){a.removeClass(b+" "+c)},2e3)},/**
*
* @param {string} href
* @param {string} title
* @param {array} classes
* @returns {string}
*/
d.buttonize=function(b,c,d){var e=a("<a />").attr("href",b).attr("title",c).text(c).classify(d);return a(this).append(e)},/**
* Set state on window resize
*/
d.windowstate=d.debounce(function(){var a=d.state.breakpoint;d.state.breakpoint=d.breakpoint().type,jQuery("body").removeClass(a).addClass(d.state.breakpoint)},100),/**
* Set state on document scroll
*/
d.scrollstate=d.debounce(function(b,c){var e=jQuery("body"),f="scrolled";d.state.scrolltop=a(document).scrollTop(),e.attr("data-scrolltop",d.state.scrolltop),
// Detect if page is scrolled
d.state.scrolltop<10?e.removeClass(f):e.addClass(f)},0,!0),function(){
// Get initial state
d.windowstate(),d.scrollstate(),
// Update state on user interaction
jQuery(window).on("resize",d.windowstate),jQuery(document).on("scroll",d.scrollstate)}(),d.jAccordion=function(a){var b=jQuery.extend({active:0,// Index value of initial content to display.
duration:500,// Duration of transition.
easing:"swing",// Type of easing.
single:!1,// Allow multiple panels to be opened or only 1?
pclass:"panel"},a),c={};/**
* The <li> object to show.
*
* @param object li
*  $('<li>')
*/
/**
* Generate markup for controls & other elements.
*
* @param object $obj
*/
/**
* Init jAccordion
*/
return b.pselect="."+b.pclass,c.showContent=function(a){b.single?(a.siblings().find(b.pselect).slideUp(b.duration,b.easing),a.activate().find(b.pselect).slideDown(b.duration,b.easing)):a.toggleClass(d.opts.activeclass).find(b.pselect).slideToggle(b.duration,b.easing)},c.style=function(a){a.once("jAccordion",function(){a.find("> li").each(function(){var a=jQuery(this);a.kidWrap(),a.children().eq(0).addClass("title"),a.children().eq(1).classify([d.opts.cclass,"panel"]),a.find(b.pselect).hide(),a.find(".title").click(function(b){b.preventDefault(),c.showContent(a)})})})},c.init=function(){var a=jQuery(this);
// Generate markup for accordion
c.style(a),
//Set default content
c.showContent(a.children().eq(b.active))},this.each(c.init)},d.jCard=function(a){var b=jQuery.extend({cclass:"jCard"},a),c={};return c.init=function(){var a=jQuery(this);a.once(b.cclass,function(){var c=a.find("a").eq(0),d=c.attr("href");if(void 0!==d){var e=jQuery('<a href="'+d+'" />').classify([b.cclass+"-wrap",c.attr("class")?c.attr("class"):null]);
// .data(a.data());
a.wrap(e).find("h2, h3").addClass("title")}}),a.on("mouseenter touchstart",function(){jQuery(this).activate()}).on("mouseleave touchend",function(){jQuery(this).deactivate()})},this.each(c.init)},/**
* jMmenu: Hamburger menu for mobile devices
*/
d.jMmenu=function(a){var b=jQuery.extend({breakpoint:d.opts.breakpoint,// Window breakpoint trigger: 'mobile', 'narrow', 'default', 'large'
parent:jQuery("body"),// Parent element used to attach menu
cclass:"jMmenu",// Menu class to test
triggertext:"Menu",animateclass:"slide-right",// Type of animation
throttle:101},a),c={};return c.mediaQuery=d.debounce(function(a,e){if(b.breakpoint===d.state.breakpoint){var f=a.children([0]),g=null;e.mmenu=!0,b.parent.addClass(b.animateclass),b.triggertext&&(g='<span class="'+b.cclass+'-triggertext">'+b.triggertext+"</span>"),a.addClass(b.cclass+"-trigger").append(g),f.addClass(b.cclass+"-menu").prependTo(b.parent)}else e.mmenu=!1,e.active=!1,b.parent.removeClass(b.cclass+"-active "+b.cclass+"-inactive "+b.animateclass),a.attr("aria-label","Menu").removeClass(b.cclass+"-trigger"),jQuery("."+b.cclass+"-menu").removeClass(b.cclass+"-menu").prependTo(a),jQuery("."+b.cclass+"-triggertext").remove();c.trigger(a,e)},b.throttle),c.trigger=function(a,c){var d=[b.cclass+"-active",b.cclass+"-inactive"];c.active?(a.activate().attr("aria-label","Close Menu"),jQuery("."+b.cclass+"-menu").addClass("active"),b.parent.addClass(d[0]).removeClass(d[1])):(a.deactivate().attr("aria-label","Open Menu"),jQuery("."+b.cclass+"-menu").removeClass("active"),c.mmenu&&b.parent.addClass(d[1]).removeClass(d[0]))},c.init=function(){var a=jQuery(this),b={active:!1,mmenu:!1};c.mediaQuery(a,b),jQuery(window).on("resize",function(){c.mediaQuery(a,b)}),a.on("click",function(){
//console.log(this);
b.mmenu&&(b.active=!b.active,c.trigger(a,b))}),jQuery(document).on("keyup",function(d){b.active===!0&&27===d.which&&(d.preventDefault(),b.active=!1,c.trigger(a,b))})},this.each(c.init)},/**
* jScrolli : Content carousel/slider
*/
d.jScrolli=function(b){var c=a.extend({cclass:"jScrolli",// Object class selector
active:0,// Index of initially selected slide
//width: "100%", // 'auto' or '[value]', i.e. '300px'
height:"auto",// 'auto' or '[value]', i.e. '300px'
controls:{showmarkers:!0,showcontrols:!0,keyboard:!0,swipe:!0,autoplay:!0,pauseonhover:!0,autodim:!0,delay:1.4,// Time (seconds) to wait before dimming.
text:{next:"Next",prev:"Prev",pause:"Pause",play:"Play"}},transition:{pause:5},caption:{enable:!0,autohide:!1,selector:"p"}},b),e={};/**
* Format html buttons for controls.
*
* @param string $text
* @returns string
*/
/**
* Update next/prev slides.
*
* @param object state
*/
/**
* Activate selected slide & corresponding marker.
*
* @param int index
* @param object $obj
* @param object state
*/
/**
* Update the current marker.
*/
/**
* Update slide caption
*/
/**
* Reset autoplay timer.
*/
/**
* Add event listeners
*
* @param {type} $obj
* @param {type} state
*/
/**
* Set height explicitly to prevent 'jumping' content.
*
* @param object $obj
* @param object state
*/
/**
* Generate markup for controls & other elements.
*
* @param object $obj
* @param object state
*/
/**
* Init jScrolli
*/
return e.button=function(a){return'<a class="control '+a.toLowerCase()+'">'+a+"</a>"},e.normalize=function(a){a.prev=a.current-1,a.next=a.current+1,a.prev<0&&(a.prev=a.count),a.next>a.count&&(a.next=0)},e.go=function(a,b,f){if(!f.paused){var g="transition",h=b.find(".slide");f.current=parseInt(a),
// Normalize state
e.normalize(f),
// Update classes on slides for css transition
jQuery(h[f.prev]).activate("previous"),jQuery(h[f.next]).activate("next"),jQuery(h[a]).activate(),
// Listen for transition to complete & update classes
b.parent().addClass(g).on(d.transitionend(),function(){jQuery(this).removeClass(g)}),
// Update the marker
c.controls.showmarkers&&e.mark(b,f),
// Update the caption
c.caption.enable&&e.caption(h,f),
// Reset the autoplay timer
c.controls.autoplay&&e.updateinterval(b,f)}},e.mark=function(a,b){a.siblings().find(".marker").eq(b.current).activate()},e.caption=function(b,e){var f=b.parent().parent(),g=f.find("> .caption p");
// Get current slide's caption
e.caption=f.find(c.caption.selector).eq(e.current).text(),g.on(d.transitionend(),function(){
// Update the active caption
a(this).text(e.caption)})},e.updateinterval=function(a,b){c.controls.autoplay&&!b.paused&&(clearInterval(b.interval),b.interval=setInterval(function(){b.current=b.next,e.go(b.current,a,b)},1e3*c.transition.pause))},e.events=function(a,b){var d=(a.siblings(".controls"),a.parent());
// Link markers to respective slides
c.controls.showmarkers&&a.siblings().find(".marker").on("click",function(){b.current=jQuery(this).attr("data-href"),b.paused=!1,e.go(b.current,a,b)}),
// Previous
d.find(".prev").on("click",function(c){b.current=b.prev,b.paused=!1,e.go(b.current,a,b)}),
// Next
d.find(".next").on("click",function(c){b.current=b.next,b.paused=!1,e.go(b.current,a,b)}),/*
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
d.on({mouseover:function(){b.active=!0,c.controls.pauseonhover&&(b.paused=!0),c.controls.autodim&&(d.activate(),window.clearTimeout(d.timeout))},mouseout:function(){b.active=!1,c.controls.pauseonhover&&(b.paused=!1),c.controls.autodim&&(d.timeout=window.setTimeout(function(){d.deactivate()},1e3*c.controls.delay))}}),
// Keyboard
c.controls.keyboard&&jQuery(document).on("keyup",function(c){var d=[37,// left
39];if(-1!==d.indexOf(c.which)){switch(c.preventDefault(),b.paused=!1,c.which){case 37:b.current=b.prev;break;case 39:b.current=b.next}e.go(b.current,a,b)}})},e.setheight=function(a,b){jQuery(document).ready(function(){"auto"===c.height?a.find("> li").each(function(){var a=this.clientHeight;a>b.maxheight&&(b.maxheight=a)}):b.maxheight=c.height,a.height(b.maxheight)})},e.style=function(a,b){var f=a.find("> li");if(a.addClass(d.opts.cclass).wrap('<div class="'+d.opts.cclass+" "+c.cclass+'-wrap" />'),f.addClass("slide").each(function(){jQuery(this).children().wrapAll('<div class="content cell" />')}),e.setheight(a,b),c.controls.showmarkers){for(var g=jQuery('<ul class="markers"/>'),h=0;h<f.length;h+=1)g.append('<li class="marker" data-href="'+h+'">'+(h+1)+"</li>");a.after(g),e.mark(a,b)}if(c.caption.enable&&(a.find(c.caption.selector).hide(),a.after('<div class="caption"><p/></div>')),c.controls.showcontrols){var i,j=[e.button(c.controls.text.prev),e.button(c.controls.text.next)];for(i=0;i<j.length;i+=1)a.parent().prepend(j[i])}},e.init=function(){var a=jQuery(this),b={active:!0,paused:!1,count:a.find("> li").length-1,
//height: o.height ? o.height : fn.setheight($obj, state),
width:c.width?c.width:a.width(),maxheight:0,interval:0,controls:0,caption:jQuery(c.caption.selector).html(),current:c.active?c.active:0};
// o.caption.selector = o.caption.selector === 'auto' ? '[title]' : o.caption.selector;
// Add markup
a.once(c.cclass,function(){e.style(a,b)}),
// Add Event Listeners
e.events(a,b),
// Activate 1st slide
e.go(b.current,a,b),
// Start autoplay
e.updateinterval(a,b)},this.each(e.init)},d.jSocial=function(b){var c=document.title,d=a("link[rel='canonical']")?a("link[rel='canonical']").attr("href"):window.location,e=jQuery.extend({showshare:!0,showfollow:!1,sharetitle:"Share this page",followtitle:"Follow Us",buttonclass:"social",share:["facebook","digg","google","twitter","linkedin","pinterest","reddit","stumbleupon","tumblr"],sharelinks:{facebook:{title:"Facebook",url:"http://facebook.com/sharer/sharer.php?u="+d},digg:{title:"Digg",url:"http://digg.com/submit?url="+d+"&title="+c},google:{title:"Google",url:"https://plus.google.com/share?url="+d},twitter:{title:"Twitter",url:"https://twitter.com/intent/tweet?url="+d+"&text="+c},linkedin:{title:"LinkedIn",url:"http://linkedin.com/shareArticle?url="+d+"&title="+c},pinterest:{title:"Pinterest",url:"http://pinterest.com/pin/create/bookmarklet/?url="+d+"&description="+c},reddit:{title:"Reddit",url:"http://reddit.com/submit?url="+d+"&title="+c},stumbleupon:{title:"StumbleUpon",url:"http://www.stumbleupon.com/submit?url="+d+"&title="+c},tumblr:{title:"Tumblr",url:"https://www.tumblr.com/widgets/share/tool?canonicalUrl="+d+"&title="+c}},follow:{facebook:{title:"Facebook",url:"https://facebook.com"},google:{title:"Google",url:"https://plus.google.com"},twitter:{title:"Twitter",url:"https://twitter.com"},linkedin:{title:"LinkedIn",url:"https://linkedin.com"},pinterest:{title:"Pinterest",url:"https://pinterest.com"},yelp:{title:"Yelp",url:"https://yelp.com"}}},b),f={};/**
* Generate markup for buttons.
*
* @param object $obj
*/
/**
* Init jSocial
*/
return f.style=function(b){b.once("jSocial",function(){if(e.showshare){var c=a('<div class="jSocial-share" />'),d="";0!==e.sharetitle.length&&(c.append('<span class="title">'+e.sharetitle+"</span>"),d=e.sharetitle+" on "),e.share.map(function(a){c.buttonize(e.sharelinks[a].url,d+e.sharelinks[a].title,[e.sharelinks[a].title.toLowerCase(),e.buttonclass,"icon"])}),b.append(c)}if(e.showfollow){var f=a('<div class="jSocial-follow" />'),g="";0!==e.followtitle.length&&(f.append('<span class="title">'+e.followtitle+"</span>"),g=e.followtitle+" on "),a.each(e.follow,function(){f.buttonize(this.url,g+this.title,[this.title.replace(/ /g,"").toLowerCase(),e.buttonclass,"icon"])}),b.append(f)}})},f.init=function(){
// Generate markup for links.
f.style(jQuery(this))},this.each(f.init)},/**
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
/**
* Init jTabs
*/
return c.showContent=function(a,b){var c=b.find(".content"),d=a.parent().find(".panel-content");b.activate(),d.fadeOut("normal",function(){jQuery(this).html(c.html()).fadeIn("normal")})},c.init=function(){var a=jQuery(this),d=a.find("> li"),e=jQuery("<div/>").classify([b.orient,b.cclass+"-wrap"]),f='<div class="panel"><div class="panel-content" /></div>';a.once(b.cclass,function(){a.wrap(e).after(f),d.each(function(){var a=jQuery(this);a.addClass("tab").kidWrap(),
//Set 1st child as title
a.children().eq(0).addClass("title"),
//Set wrapper as content
a.children().eq(1).addClass("content").hide()})}),
//Add classes/functions to each panel
d.each(function(){var b=jQuery(this);b.click(function(d){d.preventDefault(),c.showContent(a,b)})}),
//Set default content
c.showContent(a,d.eq([b.active]))},this.each(c.init)},d.jTooltip=function(a){var b=jQuery.extend({trigger:"jTooltip-trigger",// Class used to trigger tooltip.
triggerbtn:"jTooltip-trigger-btn",// OR false, used to trigger tooltip
triggerbtntext:"About this",cclass:"jTooltip-tooltip",dataattr:"data-tooltip",bindto:"btn",// OR 'event' OR {}
wrap:!0,offsetX:10,offsetY:5},a),c={};/**
* Generate markup for buttons.
*
* @param object $obj
*/
/**
* Init jSocial
*/
return c.style=function(a,c){var d=jQuery("<div>"+a.attr(b.dataattr)+"</div>");if(b.wrap&&a.wrap('<div class="'+b.cclass+'-wrap" />'),d.classify([b.cclass]),a.after(d),b.triggerbtn!==!1){var e=jQuery('<span aria-label="'+b.triggerbtntext+'" />');e.classify([b.trigger,b.triggerbtn]).prop("tabindex",a.prop("tabindex")),a.before(e)}else a.addClass(b.trigger);c(a)},c.events=function(a){jQuery("."+b.trigger).on("mouseenter focus",function(a){var c=jQuery(this),d=c.nextAll("."+b.cclass+":first"),e={},f={};switch(b.bindto){case"event":f={top:parseInt(a.clientY)+b.offsetY+"px",left:parseInt(a.clientX)+b.offsetX+"px"};break;case"btn":e=this.getBoundingClientRect(),f={top:e.top+c.height()/2+b.offsetY+"px",left:e.left+c.width()+b.offsetX+"px"};break;default:case{}:e={}.getBoundingClientRect(),f={top:e.top+c.height()/2+b.offsetY+"px",left:e.left+c.width()/2+b.offsetX+"px"}}d.css(f).activate()}).on("mouseleave blur",function(a){jQuery(this).nextAll("."+b.cclass+":first").deactivate()})},c.init=function(){c.style(jQuery(this),c.events)},this.each(c.init)},jQuery.fn.extend(d)}}}(jQuery),b["true"]=a}({},function(){return this}());