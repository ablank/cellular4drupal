!function($){Drupal.behaviors.plugins={attach:function(a,e){var o=Drupal.settings.cellular;void 0!==o.ui&&($(".jAccordion").jAccordion({duration:500,easing:"swing",single:!1}),$(".jCard").jCard(),$("form").jFormal(),$("#main-menu").jMmenu({animateclass:"slide-down"}),$(".jScrolli").jScrolli({transition:{background:"img:first",pause:8},autodim:!0,delay:1.4}),$(".jSocial.share").jSocial({share:o.ui.jSocial_share}),$(".jSocial.follow").jSocial({follow:o.ui.jSocial_follow}),$(".jTabs").jTabs({active:0,orient:"horizontal"}),$(".jTabs.vertical").jTabs({active:0,orient:"vertical"})),!0===o.plugins.backstretch&&$.backstretch(["http://lorempixel.com/800/600/abstract/1","http://lorempixel.com/800/600/abstract/2","http://lorempixel.com/800/600/abstract/3"],{duration:3e3,fade:750}),!0===o.plugins.flowtype&&$("#content-wrap").flowtype({minimum:400,maximum:800,minFont:12,maxFont:40,fontRatio:45}),!0===o.plugins.freetile&&$(".view-content").freetile({selector:".views-row",animate:!0,elementDelay:0}),!0===o.plugins.jparallax&&$(".parallax").parallax({xparallax:!1,yparallax:!0,freezeClass:"freeze",decay:.4}),!0===o.plugins.smoove&&$(".smoove").smoove({offset:"20%",moveY:"20%"}),!0===o.plugins.nprogress&&$(document).on("ajaxStart",function(){NProgress.start()}).on("ajaxComplete",function(){NProgress.done().remove()})}}}(jQuery);