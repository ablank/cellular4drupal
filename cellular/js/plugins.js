(function($) {
    Drupal.behaviors.plugins = {
        attach: function(context, settings) {
            var opts = Drupal.settings.cellular;
            if (typeof opts.ui !== "undefined") {
                $(".jAccordion").jAccordion({
                    duration: 500,
                    easing: "swing",
                    single: false
                });
                $(".jcard").jCard();
                $("form").jFormal();
                $("#main-menu").jMmenu({
                    animateclass: "slide-down"
                });
                $(".jScrolli").jScrolli({
                    transition: {
                        background: "img:first",
                        pause: 8
                    },
                    autodim: true,
                    delay: 1.4
                });
                $(".jSocial.share").jSocial({
                    share: opts.ui.jSocial_share
                });
                $(".jSocial.follow").jSocial({
                    follow: opts.ui.jSocial_follow
                });
                $(".jTabs").jTabs({
                    active: 0,
                    orient: "horizontal"
                });
                $(".jTabs.vertical").jTabs({
                    active: 0,
                    orient: "vertical"
                });
            }
            if (opts.plugins.backstretch === true) {
                $.backstretch([ "http://lorempixel.com/800/600/abstract/1", "http://lorempixel.com/800/600/abstract/2", "http://lorempixel.com/800/600/abstract/3" ], {
                    duration: 3e3,
                    fade: 750
                });
            }
            if (opts.plugins.flowtype === true) {
                $("#content-wrap").flowtype({
                    minimum: 400,
                    maximum: 800,
                    minFont: 12,
                    maxFont: 40,
                    fontRatio: 45
                });
            }
            if (opts.plugins.freetile === true) {
                $(".view-content").freetile({
                    selector: ".views-row",
                    animate: true,
                    elementDelay: 0
                });
            }
            if (opts.plugins.jparallax === true) {
                $(".parallax").parallax({
                    xparallax: false,
                    yparallax: true,
                    freezeClass: "freeze",
                    decay: .4
                });
            }
            if (opts.plugins.smoove === true) {
                $(".smoove").smoove({
                    offset: "20%",
                    moveY: "20%"
                });
            }
            if (opts.plugins.nprogress === true) {
                $(document).on("ajaxStart", function() {
                    NProgress.start();
                }).on("ajaxComplete", function() {
                    NProgress.done().remove();
                });
            }
        }
    };
})(jQuery);