!function(a,b){/**
 * @file
 * Call javascript plugins used in theme.
 */
!function(a){Drupal.behaviors.plugins={attach:function(b,c){
// CellularUI functions.
Drupal.settings.cellular.cellularui===!0&&(a(".jAccordion").jAccordion({duration:500,// Duration of transition.
easing:"swing",// Type of easing.
single:!1}),a(".jBlocklink").jBlocklink({cclass:"jBlocklink-link"}),a("#nav").jMmenu({
// Window breakpoint trigger:
// "breakpoint": cellular.opts.breakpoint, // "mobile"
cclass:"jMmenu",// default
// Classes added for styling- CSS classes control position & animation.
// <element class="$type-$direction">
type:"push",direction:"down"}),a(".jTabs").jTabs({active:0,// Array index of initially active content.
orient:"horizontal"}),a(".jTabs-vertical").jTabs({active:0,// Array index of initially active content.
orient:"vertical"}),a(".jScrolli").jScrolli()),
// Backstretch functions.
Drupal.settings.cellular.backstretch===!0&&a.backstretch(["http://lorempixel.com/800/600/abstract/1","http://lorempixel.com/800/600/abstract/2","http://lorempixel.com/800/600/abstract/3"],{duration:3e3,fade:750}),
// Flowtype functions.
Drupal.settings.cellular.flowtype===!0&&a("#content-wrap").flowtype({minimum:400,maximum:800,minFont:12,maxFont:40,fontRatio:45}),
// Freetile functions.
Drupal.settings.cellular.freetile===!0&&a(".view-content").freetile({selector:".views-row",animate:!0,
// containerAnimate: true,
elementDelay:0}),
// jParallax functions.
Drupal.settings.cellular.jparallax===!0&&a(".parallax").parallax({xparallax:!1,yparallax:!0,freezeClass:"freeze",decay:.4}),
// Smoove functions.
Drupal.settings.cellular.smoove===!0&&a(".smoove").smoove({offset:"20%",
// skew: "20deg",
// moveX: "15%",
moveY:"20%"})}}}(jQuery),b["true"]=a}({},function(){return this}());