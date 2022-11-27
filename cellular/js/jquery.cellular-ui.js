(function($) {
    Drupal.behaviors.cellular = {
        attach: function(context, settings) {
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
            (function() {
                jQuery('a[href^="#"]').on("click", function(e) {
                    var target = jQuery(this).attr("href");
                    e.preventDefault();
                    jQuery("html, body").stop().animate({
                        scrollTop: jQuery(target).offset().top
                    }, 1500);
                });
            })();
            cellular.breakpoint = function() {
                var content = window.getComputedStyle(document.querySelector("body"), ":before").getPropertyValue("content"), obj;
                if (content) {
                    obj = {
                        size: content.match(/\d/g).join(""),
                        type: content.match(/\w*[^\"\'](?=-)/g).join("")
                    };
                } else {
                    var ww = jQuery(window).width();
                    console.log(ww);
                    obj = {
                        size: "",
                        type: ""
                    };
                }
                return obj;
            };
            cellular.activate = function(theclass) {
                theclass = theclass ? theclass : cellular.opts.activeclass;
                return this.each(function() {
                    var $t = jQuery(this);
                    if (!$t.hasClass(theclass)) {
                        $t.addClass(theclass).siblings().removeClass(theclass);
                    }
                });
            };
            cellular.deactivate = function(theclass) {
                theclass = theclass ? theclass : cellular.opts.activeclass;
                return this.each(function() {
                    jQuery(this).removeClass(theclass);
                });
            };
            cellular.kidWrap = function() {
                return this.each(function() {
                    var $t = jQuery(this);
                    if ($t.children().length > 1) {
                        $t.children(":gt(0)").wrapAll("<div>");
                    }
                });
            };
            cellular.classify = function($array) {
                return this.each(function() {
                    jQuery(this).addClass($array.join(" "));
                });
            };
            cellular.debounce = function(func, wait, immediate) {
                var timeout;
                return function() {
                    var context = this, args = arguments, later = function() {
                        timeout = null;
                        if (!immediate) {
                            func.apply(context, args);
                        }
                    }, callNow = immediate && !timeout;
                    clearTimeout(timeout);
                    timeout = setTimeout(later, wait);
                    if (callNow) {
                        func.apply(context, args);
                    }
                };
            };
            cellular.transitionend = function() {
                var t, el = document.createElement("test"), transitions = {
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
            cellular.scrolltimer = function(el, uc, dc) {
                window.clearTimeout(cellular.state.scrolltimer);
                cellular.state.scrolltimer = window.setTimeout(function() {
                    el.removeClass(uc + " " + dc);
                }, 2e3);
            };
            cellular.buttonize = function(href, title, classes) {
                var btn = $("<a />").attr("href", href).attr("title", title).text(title).classify(classes);
                return $(this).append(btn);
            };
            cellular.windowstate = cellular.debounce(function() {
                var ob = cellular.state.breakpoint;
                cellular.state.breakpoint = cellular.breakpoint().type;
                jQuery("body").removeClass(ob).addClass(cellular.state.breakpoint);
            }, 100);
            cellular.scrollstate = cellular.debounce(function(e, y) {
                var el = jQuery("body"), cclass = "scrolling", uc = cclass + "-up", dc = cclass + "-down", dst = jQuery(document).scrollTop(), region = el.height() / 3, scrolltimeout = null;
                if (dst > 30) {
                    el.addClass("scrolled");
                } else {
                    el.removeClass("scrolled");
                }
                if (dst > cellular.state.scrolltop) {
                    el.addClass(dc).removeClass(uc);
                } else {
                    el.addClass(uc).removeClass(dc);
                }
                if (dst < region) {
                    el.removeClass("page-middle page-bottom").addClass("page-top");
                } else if (dst > region && dst < region * 2) {
                    el.removeClass("page-top page-bottom").addClass("page-middle");
                } else {
                    el.removeClass("page-top page-middle").addClass("page-bottom");
                }
                cellular.state.scrolltop = dst;
                cellular.state.scrolled = dst / (el.height() - jQuery(window).height()) * 100;
            }, 0, true);
            (function state() {
                cellular.windowstate();
                cellular.scrollstate();
                jQuery(window).on("resize", cellular.windowstate);
                jQuery(document).on("scroll", cellular.scrollstate);
            })();
            cellular.jAccordion = function(opts) {
                var o = jQuery.extend({
                    active: 0,
                    duration: 500,
                    easing: "swing",
                    single: false,
                    pclass: "panel"
                }, opts), fn = {};
                o.pselect = "." + o.pclass;
                fn.showContent = function(li) {
                    if (o.single) {
                        li.siblings().find(o.pselect).slideUp(o.duration, o.easing);
                        li.activate().find(o.pselect).slideDown(o.duration, o.easing);
                    } else {
                        li.toggleClass(cellular.opts.activeclass).find(o.pselect).slideToggle(o.duration, o.easing);
                    }
                };
                fn.style = function($obj) {
                    $obj.once("jAccordion", function() {
                        $obj.find("> li").each(function() {
                            var li = jQuery(this);
                            li.kidWrap();
                            li.children().eq(0).addClass("title");
                            li.children().eq(1).classify([ cellular.opts.cclass, "panel" ]);
                            li.find(o.pselect).hide();
                            li.find(".title").click(function(e) {
                                e.preventDefault();
                                fn.showContent(li);
                            });
                        });
                    });
                };
                fn.init = function() {
                    var $obj = jQuery(this);
                    fn.style($obj);
                    fn.showContent($obj.children().eq(o.active));
                };
                return this.each(fn.init);
            };
            cellular.jCard = function(opts) {
                var o = jQuery.extend({
                    cclass: "jCard"
                }, opts), fn = {};
                fn.init = function() {
                    var $obj = jQuery(this);
                    $obj.once(o.cclass, function() {
                        var a1 = $obj.find("a").eq(0);
                        var href = a1.attr("href");
                        if (href !== undefined) {
                            var wrapperlink = jQuery('<a href="' + href + '" />').classify([ o.cclass + "-wrap", a1.attr("class") ? a1.attr("class") : null ]);
                            $obj.wrap(wrapperlink).find("h2, h3").addClass("title");
                        }
                    });
                    $obj.on("mouseenter touchstart", function() {
                        jQuery(this).activate();
                    }).on("mouseleave touchend", function() {
                        jQuery(this).deactivate();
                    });
                };
                return this.each(fn.init);
            };
            cellular.jFormal = function(opts) {
                var o = jQuery.extend({
                    inputs: [ 'input[type="text"]', 'input[type="email"]', 'input[type="password"]', "textarea" ]
                }, opts);
                return this.each(function() {
                    var inputs = o.inputs.join(",");
                    jQuery(inputs).each(function() {
                        var $t = jQuery(this), hold = holder = $t.attr("placeholder");
                        $t.on("focus", function() {
                            holder = "";
                            if (this.value === this.defaultValue) {
                                this.value = "";
                            }
                        }).on("blur", function() {
                            holder = hold;
                            if (this.value === "" || null) {
                                this.value = this.defaultValue;
                            }
                        });
                    });
                });
            };
            cellular.jMmenu = function(opts) {
                var o = jQuery.extend({
                    breakpoint: cellular.opts.breakpoint,
                    parent: jQuery("body"),
                    cclass: "jMmenu",
                    triggertext: "Menu",
                    animateclass: "slide-right",
                    throttle: 101
                }, opts), fn = {};
                fn.mediaQuery = cellular.debounce(function($obj, state) {
                    if (o.breakpoint === cellular.state.breakpoint) {
                        var $menu = $obj.children([ 0 ]), label = null;
                        state.mmenu = true;
                        o.parent.addClass(o.animateclass);
                        if (o.triggertext) {
                            label = '<span class="' + o.cclass + '-triggertext">' + o.triggertext + "</span>";
                        }
                        $obj.addClass(o.cclass + "-trigger").append(label);
                        $menu.addClass(o.cclass + "-menu").prependTo(o.parent);
                    } else {
                        state.mmenu = false;
                        state.active = false;
                        o.parent.removeClass(o.cclass + "-active " + o.cclass + "-inactive " + o.animateclass);
                        $obj.attr("aria-label", "Menu").removeClass(o.cclass + "-trigger");
                        jQuery("." + o.cclass + "-menu").removeClass(o.cclass + "-menu").prependTo($obj);
                        jQuery("." + o.cclass + "-triggertext").remove();
                    }
                    fn.menutrigger($obj, state);
                }, o.throttle);
                fn.menutrigger = function($obj, state) {
                    var classes = [ o.cclass + "-active", o.cclass + "-inactive" ];
                    if (state.active) {
                        $obj.activate().attr("aria-label", "Close Menu");
                        jQuery("." + o.cclass + "-menu").addClass("active");
                        o.parent.addClass(classes[0]).removeClass(classes[1]);
                    } else {
                        $obj.deactivate().attr("aria-label", "Open Menu");
                        jQuery("." + o.cclass + "-menu").removeClass("active");
                        if (state.mmenu) {
                            o.parent.addClass(classes[1]).removeClass(classes[0]);
                        }
                    }
                };
                fn.style = function($obj) {
                    var menu = $obj.find(">ul"), nested = menu.find("ul");
                    if (nested.length > 0) {
                        var child = menu.find("li ul");
                        child.addClass("child").parent().addClass("parent").css({
                            willChange: "contents"
                        });
                    }
                };
                fn.listen = function($obj, state) {
                    jQuery(window).on("resize", function() {
                        fn.mediaQuery($obj, state);
                    });
                    $obj.on("click", function() {
                        if (state.mmenu) {
                            state.active = state.active ? false : true;
                            fn.menutrigger($obj, state);
                        }
                    });
                    jQuery(document).on("keyup", function(e) {
                        if (state.active === true && e.which === 27) {
                            e.preventDefault();
                            state.active = false;
                            fn.menutrigger($obj, state);
                        }
                    });
                    jQuery(".parent > a").on("click", function(e) {
                        if (state.mmenu) {
                            var parent = jQuery(this).parent(), child = parent.children(":gt(0)");
                            if (child.length > 0) {
                                e.preventDefault();
                                if (child.hasClass("active")) {
                                    parent.removeClass("active");
                                    child.removeClass("active");
                                } else {
                                    parent.addClass("active");
                                    child.addClass("active");
                                }
                            }
                        }
                    });
                };
                fn.init = function() {
                    var $obj = jQuery(this), state = {
                        active: false,
                        mmenu: false
                    };
                    $obj.addClass(o.cclass).once(o.cclass, fn.style($obj));
                    fn.mediaQuery($obj, state);
                    fn.listen($obj, state);
                };
                return this.each(fn.init);
            };
            cellular.jScrolli = function(opts) {
                var o = $.extend({
                    cclass: "jScrolli",
                    active: 0,
                    background: "img:first",
                    title: "h2, h3",
                    height: "auto",
                    controls: {
                        showmarkers: true,
                        showcontrols: true,
                        keyboard: true,
                        swipe: true,
                        autoplay: true,
                        pauseonhover: true,
                        autodim: true,
                        delay: 1.4,
                        text: {
                            next: "Next",
                            prev: "Prev",
                            pause: "Pause",
                            play: "Play"
                        }
                    },
                    transition: {
                        pause: 5
                    },
                    caption: {
                        enable: true,
                        autohide: false,
                        selector: ".caption"
                    }
                }, opts), fn = {};
                fn.button = function($text) {
                    return '<a class="' + o.cclass + "-control " + $text.toLowerCase() + '">' + $text + "</a>";
                };
                fn.normalize = function(state) {
                    state.prev = state.current - 1;
                    state.next = state.current + 1;
                    if (state.prev < 0) {
                        state.prev = state.count;
                    }
                    if (state.next > state.count) {
                        state.next = 0;
                    }
                };
                fn.go = function(index, $obj, state) {
                    if (!state.paused) {
                        var tclass = "transition", li = $obj.find("." + o.cclass + "-slide");
                        state.current = parseInt(index);
                        fn.normalize(state);
                        jQuery(li[state.prev]).activate("previous");
                        jQuery(li[state.next]).activate("next");
                        jQuery(li[index]).activate();
                        $obj.parent().addClass(tclass).on(cellular.transitionend(), function() {
                            jQuery(this).removeClass(tclass);
                        });
                        if (o.controls.showmarkers) {
                            fn.mark($obj, state);
                        }
                        if (o.caption.enable) {
                            fn.caption(li, state);
                        }
                        if (o.controls.autoplay) {
                            fn.updateinterval($obj, state);
                        }
                    }
                };
                fn.mark = function($obj, state) {
                    $obj.siblings().find("." + o.cclass + "-marker").eq(state.current).activate();
                };
                fn.caption = function($obj, state) {
                    var wrap = $obj.parent().parent(), cap = wrap.find("> .caption p");
                    state.caption = wrap.find(o.caption.selector).eq(state.current).text();
                    cap.on(cellular.transitionend(), function() {
                        $(this).text(state.caption).activate();
                    });
                };
                fn.updateinterval = function($obj, state) {
                    if (o.controls.autoplay && !state.paused) {
                        clearInterval(state.interval);
                        state.interval = setInterval(function() {
                            state.current = state.next;
                            fn.go(state.current, $obj, state);
                        }, o.transition.pause * 1e3);
                    }
                };
                fn.events = function($obj, state) {
                    var controls = $obj.siblings(".controls"), wrap = $obj.parent(), eX = null, eY = null;
                    if (o.controls.showmarkers) {
                        $obj.siblings().find("." + o.cclass + "-marker").on("click", function() {
                            state.current = jQuery(this).attr("data-href");
                            state.paused = false;
                            fn.go(state.current, $obj, state);
                        });
                    }
                    wrap.find(".prev").on("click", function(e) {
                        state.current = state.prev;
                        state.paused = false;
                        fn.go(state.current, $obj, state);
                    });
                    wrap.find(".next").on("click", function(e) {
                        state.current = state.next;
                        state.paused = false;
                        fn.go(state.current, $obj, state);
                    });
                    wrap.on({
                        mouseover: function() {
                            state.active = true;
                            if (o.controls.pauseonhover) {
                                state.paused = true;
                            }
                            if (o.controls.autodim) {
                                wrap.activate();
                                window.clearTimeout(wrap.timeout);
                            }
                        },
                        mouseout: function() {
                            state.active = false;
                            if (o.controls.pauseonhover) {
                                state.paused = false;
                            }
                            if (o.controls.autodim) {
                                wrap.timeout = window.setTimeout(function() {
                                    wrap.deactivate();
                                }, o.controls.delay * 1e3);
                            }
                        }
                    });
                    if (o.controls.keyboard) {
                        jQuery(document).on("keyup", function(e) {
                            var keys = [ 37, 39 ];
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
                };
                fn.setheight = function($obj, state) {
                    jQuery(document).ready(function() {
                        if (o.height === "auto") {
                            $obj.find("> li").each(function() {
                                var tHeight = this.clientHeight;
                                if (tHeight > state.maxheight) {
                                    state.maxheight = tHeight;
                                }
                            });
                        } else {
                            state.maxheight = o.height;
                        }
                        $obj.height(state.maxheight);
                    });
                };
                fn.style = function($obj, state) {
                    var li = $obj.find("> li");
                    $obj.addClass(cellular.opts.cclass).wrap('<div class="' + cellular.opts.cclass + " " + o.cclass + '-wrap" />').parent().css({
                        willChange: "contents"
                    });
                    li.addClass(o.cclass + "-slide").each(function() {
                        var $t = jQuery(this);
                        $t.children().wrapAll('<div class="' + o.cclass + '-slide-content cell" />');
                        if (o.title) {
                            $t.find(o.title).addClass("title");
                        }
                        if (o.background) {
                            var background = $t.find(o.background);
                            if (background.length) {
                                background.hide();
                                $t.css({
                                    "background-image": "url(" + background.attr("src") + ")"
                                }).addClass(o.cclass + "-background");
                            }
                        }
                    });
                    fn.setheight($obj, state);
                    if (o.controls.showmarkers) {
                        var markers = jQuery('<ul class="' + o.cclass + '-markers"/>');
                        for (var i = 0; i < li.length; i += 1) {
                            markers.append('<li class="' + o.cclass + '-marker" data-href="' + i + '">' + (i + 1) + "</li>");
                        }
                        $obj.after(markers);
                        fn.mark($obj, state);
                    }
                    if (o.caption.enable) {
                        var cap = $obj.find(o.caption.selector);
                        if (cap.length) {
                            cap.hide();
                            $obj.after('<div class="' + o.cclass + '-caption"><p/></div>');
                        }
                    }
                    if (o.controls.showcontrols) {
                        var j, controls = [ fn.button(o.controls.text.prev), fn.button(o.controls.text.next) ];
                        for (j = 0; j < controls.length; j += 1) {
                            $obj.parent().prepend(controls[j]);
                        }
                    }
                };
                fn.init = function() {
                    var $obj = jQuery(this), state = {
                        active: true,
                        paused: false,
                        count: $obj.find("> li").length - 1,
                        width: o.width ? o.width : $obj.width(),
                        maxheight: 0,
                        interval: 0,
                        controls: 0,
                        caption: jQuery(o.caption.selector).html(),
                        current: o.active ? o.active : 0
                    };
                    $obj.once(o.cclass, function() {
                        fn.style($obj, state);
                    });
                    fn.events($obj, state);
                    fn.go(state.current, $obj, state);
                    fn.updateinterval($obj, state);
                };
                return this.each(fn.init);
            };
            cellular.jSocial = function(opts) {
                var doctitle = document.title, page = $("link[rel='canonical']") ? $("link[rel='canonical']").attr("href") : window.location;
                var o = jQuery.extend({
                    sharetitle: "",
                    followtitle: "",
                    buttonclass: "social",
                    share: [],
                    follow: {}
                }, opts), fn = {};
                fn.style = function($obj) {
                    $obj.once("jSocial", function() {
                        if (o.share) {
                            var sWrap = $('<div class="jSocial-share" />'), sharetitle, sharelinks = {
                                facebook: {
                                    title: "Facebook",
                                    url: "http://facebook.com/sharer/sharer.php?u=" + page
                                },
                                digg: {
                                    title: "Digg",
                                    url: "http://digg.com/submit?url=" + page + "&title=" + doctitle
                                },
                                google: {
                                    title: "Google",
                                    url: "https://plus.google.com/share?url=" + page
                                },
                                twitter: {
                                    title: "Twitter",
                                    url: "https://twitter.com/intent/tweet?url=" + page + "&text=" + doctitle
                                },
                                linkedin: {
                                    title: "LinkedIn",
                                    url: "http://linkedin.com/shareArticle?url=" + page + "&title=" + doctitle
                                },
                                pinterest: {
                                    title: "Pinterest",
                                    url: "http://pinterest.com/pin/create/bookmarklet/?url=" + page + "&description=" + doctitle
                                },
                                reddit: {
                                    title: "Reddit",
                                    url: "http://reddit.com/submit?url=" + page + "&title=" + doctitle
                                },
                                stumbleupon: {
                                    title: "StumbleUpon",
                                    url: "http://www.stumbleupon.com/submit?url=" + page + "&title=" + doctitle
                                },
                                tumblr: {
                                    title: "Tumblr",
                                    url: "https://www.tumblr.com/widgets/share/tool?canonicalUrl=" + page + "&title=" + doctitle
                                }
                            };
                            if (o.sharetitle) {
                                sWrap.append('<span class="title">' + o.sharetitle + "</span>");
                                sharetitle = o.sharetitle + " on ";
                            }
                            o.share.map(function(i) {
                                sWrap.buttonize(sharelinks[i].url, sharetitle + sharelinks[i].title, [ sharelinks[i].title.toLowerCase(), o.buttonclass, "icon" ]);
                            });
                            $obj.append(sWrap);
                        }
                        if (Object.keys(o.follow) !== "undefined") {
                            var fWrap = $('<div class="jSocial-follow" />'), followtitle = "";
                            if (o.followtitle) {
                                fWrap.append('<span class="title">' + o.followtitle + "</span>");
                                followtitle = o.followtitle + " on ";
                            }
                            $.each(o.follow, function() {
                                fWrap.buttonize(this.url, followtitle + this.title, [ this.title.replace(/ /g, "").toLowerCase(), o.buttonclass, "icon" ]);
                            });
                            $obj.append(fWrap);
                        }
                    });
                };
                fn.init = function() {
                    fn.style(jQuery(this));
                };
                return this.each(fn.init);
            };
            cellular.jTabs = function(opts) {
                var o = jQuery.extend({
                    active: 0,
                    orient: "horizontal",
                    cclass: "jTabs"
                }, opts), fn = {};
                fn.showContent = function($obj, li) {
                    var content = li.find(".content"), pan = $obj.parent().find(".panel-content");
                    li.activate();
                    pan.fadeOut("normal", function() {
                        jQuery(this).html(content.html()).fadeIn("normal");
                    });
                };
                fn.init = function() {
                    var $obj = jQuery(this), tab = $obj.find("> li"), wrap = jQuery("<div/>").classify([ o.orient, o.cclass + "-wrap" ]), panel = '<div class="panel"><div class="panel-content" /></div>';
                    $obj.once(o.cclass, function() {
                        $obj.wrap(wrap).after(panel);
                        tab.each(function() {
                            var li = jQuery(this);
                            li.addClass("tab").kidWrap();
                            li.children().eq(0).addClass("title");
                            li.children().eq(1).addClass("content").hide();
                        });
                    });
                    tab.each(function() {
                        var li = jQuery(this);
                        li.click(function(e) {
                            e.preventDefault();
                            fn.showContent($obj, li);
                        });
                    });
                    fn.showContent($obj, tab.eq([ o.active ]));
                };
                return this.each(fn.init);
            };
            jQuery.fn.extend(cellular);
        }
    };
})(jQuery);