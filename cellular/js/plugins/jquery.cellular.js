/*!/////
 Cellular UI functions
 (c)2012 Adam Blankenship
 /////*/
(function($) {

    ///// :)
    Drupal.behaviors.cellular = {
        attach: function(context, settings) {

            ///// :)
            var cellular = {};

            cellular.opts = {
                "cclass": "cellular",
                "tclass": "title",
                "bclass": "body",
                "wrapper": '<div />',
                "speed": 300,
                "breakpoint": 650
            };

            ///// :)
            cellular.activate = function() {
                return this.each(function() {
                    var $t = jQuery(this);

                    if ($t.hasClass('active')) {
                        return;
                    } else {
                        $t.addClass('active')
                                .siblings().removeClass('active');
                    }
                });
            };
/////
            cellular.deactivate = function() {
                return this.each(function() {
                    var $t = jQuery(this);
                    if ($t.hasClass('active')) {
                        $t.removeClass('active');
                    }
                });
            };

            cellular.kidWrap = function() {
                // Wrap element's children with index gt 0
                return this.each(function() {
                    var $t = jQuery(this);

                    if ($t.children().length > 1) {
                        $t.children(':gt(0)').wrapAll('<div>');
                    }
                });
            };

            cellular.classify = function($array) {
                // Add array of classes to element
                return this.each(function() {
                    var $t = jQuery(this);
                    var classes = $array.join(' ');

                    $t.addClass(classes);
                });
            };


            /*////
             cellular.yPos = function() {
             return this.each(function() {
             var $t = jQuery(this);

             $t.offset();
             });
             };

             cellular.loop = function($obj, fn) {
             if ($obj.next().length === 0) {
             $obj.next = $obj.siblings(0);
             }
             };
             */


            ///// :)
            cellular.jAccordion = function(opts) {
                var o = jQuery.extend({
                    "active": 0,
                    "duration": 500,
                    "easing": "swing",
                    "single": false
                }, opts);

                var fn = {};

                fn.showContent = function($li) {

                    if (o.single === true) {
                        $li.siblings('.active').deactivate()
                                .find('.panel').slideUp(o.duration, o.easing);
                    }
                    else {
                        $li.activate()
                                .find('.panel').slideToggle(o.duration, o.easing);
                    }
                };

                return this.each(function() {
                    var $obj = jQuery(this);
                    var li = $obj.find('li');
                    //fn.style($obj);
                    //Add classes/functions to each pane

                    $obj.once('jAccordion', function() {

                        $obj.addClass(cellular.opts.cclass);

                        li.each(function() {
                            var $t = jQuery(this);

                            $t.kidWrap();
                            $t.children().eq(0).addClass('title');
                            $t.children().eq(1).classify([cellular.opts.cclass, 'panel']);
                            $t.find('.panel').hide();
                            $t.find('.title').click(function(e) {
                                e.preventDefault();
                                fn.showContent($t);
                            });
                        });
                    });

                    //Set default content
                    fn.showContent($obj.children().eq(o.active));
                });
            };


            ///// :)
/////
            cellular.jBlocklink = function(opts) {
                var o = jQuery.extend({
                    "cclass": "jBlocklink-link",
                }, opts);

                return this.each(function() {
                    var $obj = jQuery(this);

                    $obj.once(o.cclass, function() {
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

                    $obj.live('mouseenter touchstart', function() {
                        jQuery(this).activate();
                    }).live('mouseleave touchend', function() {
                        jQuery(this).deactivate();
                    });
                });
            };


            ///// :)
            cellular.jFormal = function(opts) {
                var o = jQuery.extend({
                    "inputs": [
                        'input[type="text"]',
                        'input[type="email"]',
                        'input[type="password"]',
                        'textarea'
                    ],
                }, opts);
                return this.each(function() {
                    var $obj = jQuery(this);
                    var inputs = o.inputs.join(',');
                    // get/set value of inputs
                    $(inputs).each(function() {
                        var $t = jQuery(this);
                        var $v = $t.val();
                        $t.live('focus', function() {
                            // clear the default value of an input on focus
                            if ($t.val() === $v) {
                                $t.val("");
                            }
                        }).live('blur', function() {
                            // reset to default value if no changes were made
                            if ($t.val() === "") {
                                $t.val($v);
                            }
                        });
                    });
                });
            };

            ///// :)
/////
            cellular.jMmenu = function(opts) {
                var o = jQuery.extend({
                    "breakpoint": cellular.opts.breakpoint // Window breakpoint trigger
                }, opts);

                var fn = {};
                fn.mediaQuery = function(menu) {
                    var li = menu.children();
                    if (window.innerWidth <= o.breakpoint) {
                        li.hide();
                        if (menu.hasClass('mini')) {
                            return;
                        } else {
                            menu.addClass('mini');
                        }

                        menu.click(function() {
                            if ((li.css('display')) === 'none') {
                                menu.addClass('active');
                                li.show();
                            } else {
                                li.hide();
                                menu.addClass('active');
                            }
                        });

                    } else {
                        menu.children().show();
                        if (menu.hasClass('mini')) {
                            menu.removeClass('mini');
                        }
                    }
                };

                return this.each(function() {
                    var $obj = jQuery(this);

                    $obj.addClass(cellular.opts.cclass + ' jMmenu');
                    fn.mediaQuery($obj);
                    jQuery(window).resize(function() {
                        fn.mediaQuery($obj);
                    });
                });
            };

            ///// :)
/////
            cellular.jScrolli = function(opts) {
                o = $.extend({
                    "active": 0,
                    "speed": 500, // Duration of cycle
                    "pause": 3000 // Time to pause between cycles
                }, opts);
                /*Math.max.apply(Math, array)*/
                var fn = {};
                //fn.style = function(){};
                return this.each(function() {
                    var $obj = jQuery(this);
                    var $i = $obj.find(jQuery($obj.children()));
                    var active = o.active ? o.active : $i[0];
                    var maxHeight = 0;


                    $i.each(function() {
                        $t = jQuery(this);
                        if ($t.height() > maxHeight) {
                            maxHeight = $t.height();
                        }
                        $t.hide();
                    });

                    $obj.addClass(cellular.opts.cclass)
                            .height(maxHeight);

                    jQuery(active).addClass('active')
                            .fadeIn(o.speed, function() {
                                var $t = jQuery(this);
                                var next = $t.next();
                                if (next.length === 0) {
                                    next = $i[0];
                                }
                                $t.delay(o.pause)
                                        .fadeOut(o.speed, function() {
                                            $t.removeClass('');
                                            $obj.jScrolli({
                                                "active": next,
                                                "speed": o.speed,
                                                "pause": o.pause
                                            });
                                        });
                            });
                });
            };

            ///// :)
/////
            cellular.jTabs = function(opts) {
                var o = jQuery.extend({
                    "active": 0, // Array index of initially active tab
                    "orient": "horizontal", // || 'vertical'
                }, opts);

                var fn = {};

                fn.showContent = function(li) {
                    //Content
                    var c = li.find('.content');
                    //Display
                    var pan = li.parent().find('.panel-content');

                    li.activate();
                    pan.fadeOut('normal', function() {
                        jQuery(this).html(c.html())
                                .fadeIn('normal');
                    });
                };

                return this.each(function() {

                    var $obj = jQuery(this);
                    var tab = $obj.find('> li');

                    $obj.once('jTabs', function() {

                        $obj.addClass(cellular.opts.cclass + ' ' + o.orient)
                                .append('<div class="' + cellular.opts.cclass + ' panel" />');
                        $obj.find('.panel').append('<div class="panel-content" />');

                        tab.each(function() {
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
                    tab.each(function() {
                        var li = jQuery(this);

                        li.click(function(e) {
                            e.preventDefault();
                            fn.showContent(li);
                        });
                    });

                    //Set default content
                    fn.showContent(tab.eq([o.active]));
                });
            };

            ///// :)
            jQuery.fn.extend(cellular);

            ///// :)
//Drupal.behaviors.cellular = {
//attach: function (context, settings) {
        }
    };

    ///// :)
})(jQuery);