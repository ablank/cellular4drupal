/*!/////
 Cellular UI functions
 (c)2012 Adam Blankenship
 /////*/
!function(a) {
    Drupal.behaviors.cellular = {attach: function() {
            var b = {};
            b.opts = {cclass: "cellular", tclass: "title", bclass: "body", wrapper: "<div />", speed: 300, breakpoint: 650}, b.activate = function() {
                return this.each(function() {
                    var a = jQuery(this);
                    a.hasClass("active") || a.addClass("active").siblings().removeClass("active")
                })
            }, b.deactivate = function() {
                return this.each(function() {
                    var a = jQuery(this);
                    a.hasClass("active") && a.removeClass("active")
                })
            }, b.kidWrap = function() {
                return this.each(function() {
                    var a = jQuery(this);
                    a.children().length > 1 && a.children(":gt(0)").wrapAll("<div>")
                })
            }, b.classify = function(a) {
                var b = jQuery(this), c = a.join(" ");
                b.addClass(c)
            }, b.jAccordion = function(a) {
                var c = jQuery.extend({active: 0, duration: 500, easing: "swing", single: !1}, a), d = {};
                return d.showContent = function(a) {
                    c.single === !0 && a.siblings(".active").deactivate().find(".panel").slideUp(c.duration, c.easing).fadeOut(c.duration, c.easing), a.activate().find(".panel").slideToggle(c.duration, c.easing)
                }, this.each(function() {
                    var a = jQuery(this);
                    a.once("jAccordion", function() {
                        a.addClass(b.opts.cclass), a.find("li").each(function() {
                            var a = jQuery(this);
                            a.kidWrap(), a.children().eq(0).addClass("title"), a.children().eq(1).addClass(b.opts.cclass + " panel"), a.find(".panel").hide(), a.find(".title").click(function(b) {
                                b.preventDefault(), d.showContent(a)
                            })
                        })
                    }), d.showContent(a.children().eq(c.active))
                })
            }, b.jBlocklink = function(a) {
                var c = jQuery.extend({"class": "jBlocklink"}, a);
                return this.each(function() {
                    var a = jQuery(this);
                    a.once("jBlocklink", function() {
                        var d = a.find("a").eq(0), e = jQuery('<a href="' + d.attr("href") + '" />'), f = [b.opts.cclass, c.class, d.attr("class") ? d.attr("class") : ""];
                        void 0 !== d && (e.classify(f), a.wrap(e).find("h2, h3").addClass("title"))
                    }), a.hover(function() {
                        a.activate()
                    }, function() {
                        a.deactivate()
                    })
                })
            }, b.jFormal = function(b) {
                var c = jQuery.extend({inputs: ['input[type="text"]', 'input[type="email"]', 'input[type="password"]', "textarea"]}, b);
                return this.each(function() {
                    var b = (jQuery(this), c.inputs.join(","));
                    a(b).each(function() {
                        var a = jQuery(this), b = a.val();
                        a.live("focus", function() {
                            a.val() === b && a.val("")
                        }).live("blur", function() {
                            "" === a.val() && a.val(b)
                        })
                    })
                })
            }, b.jMmenu = function(a) {
                var c = jQuery.extend({breakpoint: b.opts.breakpoint}, a), d = {};
                return d.mediaQuery = function(a) {
                    var b = a.children();
                    if (window.innerWidth <= c.breakpoint) {
                        if (b.hide(), a.hasClass("mini"))
                            return;
                        a.addClass("mini"), a.click(function() {
                            "none" === b.css("display") ? b.activate().show() : b.deactivate().hide()
                        })
                    } else
                        a.children().show(), a.hasClass("mini") && a.removeClass("mini")
                }, this.each(function() {
                    var a = jQuery(this);
                    a.addClass(b.opts.cclass + " jMmenu"), d.mediaQuery(a), jQuery(window).resize(function() {
                        d.mediaQuery(a)
                    })
                })
            }, b.jScrolli = function(c) {
                o = a.extend({speed: 500, pause: 3e3}, c);
                var d = {};
                return d.showContent = function() {
                }, this.each(function() {
                    var a = jQuery(this), c = a.find(jQuery(a.children())), d = o.active ? o.active : c[0], e = 0;
                    c.each(function() {
                        var a = jQuery(this), b = a.height();
                        b > e && (e = b), a.hide()
                    }), a.addClass(b.opts.cclass).css({height: e}), jQuery(d).fadeIn(o.speed, function() {
                        var b = jQuery(this), d = b.next();
                        0 === d.length && (d = c[0]), b.delay(o.pause).fadeOut(o.speed, function() {
                            a.jScrolli({active: d, speed: o.speed, pause: o.pause})
                        })
                    })
                })
            }, b.jTabs = function(a) {
                var c = jQuery.extend({active: 0}, a), d = {};
                return d.showContent = function(a) {
                    var b = a.find(".content"), c = a.parent().find(".panel-content");
                    a.activate(), c.fadeOut("normal", function() {
                        jQuery(this).html(b.html()).fadeIn("normal")
                    })
                }, this.each(function() {
                    var a = jQuery(this), e = a.find("> li");
                    a.once("jTabs", function() {
                        a.addClass(b.opts.cclass).append('<div class="' + b.opts.cclass + ' panel" />').find(".panel").append('<div class="panel-content" />'), e.addClass("tab"), e.each(function() {
                            {
                                var a = jQuery(this);
                                a.children()
                            }
                            a.kidWrap(), a.children().eq(0).addClass("title"), a.children().eq(1).addClass("content").hide()
                        })
                    }), e.each(function() {
                        var a = jQuery(this);
                        a.find(".title").click(function(b) {
                            b.preventDefault(), d.showContent(a)
                        })
                    }), d.showContent(e.eq([c.active]))
                })
            }, jQuery.fn.extend(b)
        }}
}(jQuery);