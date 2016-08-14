(function(a,b){/**
 * @file
 * Call javascript plugins used in theme.
 */
(function(a){Drupal.behaviors.plugins={attach:function(b,c){var d=Drupal.settings.cellular;
// CellularUI functions.
if(typeof d.ui!=="undefined"){a(".jAccordion").jAccordion({duration:500,// Duration of transition.
easing:"swing",// Type of easing.
single:false});a(".jCard").jCard();a("form").jFormal();a("#main-menu").jMmenu({animateclass:"slide-down"});a(".jSocial.share").jSocial({share:d.ui.jSocial_share});a(".jSocial.follow").jSocial({follow:d.ui.jSocial_follow});a(".jTabs").jTabs({active:0,// Array index of initially active content.
orient:"horizontal"});a(".jTabs.vertical").jTabs({active:0,// Array index of initially active content.
orient:"vertical"});a("[data-tooltip]").jTooltip();
//$('.jTooltip').jTooltip();
a(".jScrolli").jScrolli({transition:{background:"img:first",// Selector for applying background image
pause:8},autodim:true,delay:1.4})}
// Backstretch functions.
if(d.plugins.backstretch===true){a.backstretch(["http://lorempixel.com/800/600/abstract/1","http://lorempixel.com/800/600/abstract/2","http://lorempixel.com/800/600/abstract/3"],{duration:3e3,fade:750})}
// Flowtype functions.
if(d.plugins.flowtype===true){a("#content-wrap").flowtype({minimum:400,maximum:800,minFont:12,maxFont:40,fontRatio:45})}
// Freetile functions.
if(d.plugins.freetile===true){a(".view-content").freetile({selector:".views-row",animate:true,
// containerAnimate: true,
elementDelay:0})}
// jParallax functions.
if(d.plugins.jparallax===true){a(".parallax").parallax({xparallax:false,yparallax:true,freezeClass:"freeze",decay:.4})}
// Smoove functions.
if(d.plugins.smoove===true){a(".smoove").smoove({offset:"20%",
// skew: "20deg",
// moveX: "15%",
moveY:"20%"})}if(d.plugins.nprogress===true){a(document).on("ajaxStart",function(){NProgress.start()}).on("ajaxComplete",function(){NProgress.done().remove()})}}}})(jQuery);b["true"]=a})({},function(){return this}());