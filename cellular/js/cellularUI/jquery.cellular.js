/*!/////
 Cellular UI functions
 (c)2012 Adam Blankenship
 /////*/
(function ($) {
 
 ///// 
Drupal.behaviors.cellular = {
    attach: function(context, settings) {
 
 ///// 
var cellular = {};

cellular.opts = {
    "cclass": "cellular",
    "tclass": "title",
    "bclass": "body",
    "wrapper": '<div />',
    "speed": 300,
    "breakpoint": 650
};
 
 ///// 
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
    return this.each(function() {
        var $t = jQuery(this);

        if ($t.children().length > 1) {
            $t.children(':gt(0)').wrapAll('<div>');
        }
    });
};

/////
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

 
 ///// 
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

        $li.activate()
                .find('.panel').slideToggle(o.duration, o.easing);
    };

    return this.each(function() {
        var $obj = jQuery(this);
        var li = $obj.find('li');

        $obj.addClass(cellular.opts.cclass);
        //fn.style($obj);
        //Add classes/functions to each panel
        li.each(function() {
            var $t = jQuery(this);

            $t.kidWrap();

            $t.children().eq(0).addClass('title');
            $t.children().eq(1).addClass('panel');

            $t.find('.panel').hide();

            $t.find('.title').click(function(e) {
                e.preventDefault();
                fn.showContent($t);
            });
        });

        //Set default content
        fn.showContent($obj.children().eq(o.active));
    });
};

 
 ///// 
/////
cellular.jBlocklink = function(opts) {
    var o = jQuery.extend({
        //opt : "val",
    }, opts);

    return this.each(function() {
        var $obj = jQuery(this);
        var a = $obj.find('a').eq(0);
        var c = a.attr('class') ? a.attr('class') : '';
        var bl = jQuery('<a href="' + a.attr('href') + '" class="' + cellular.opts.cclass + ' jBlocklink ' + c + '" />');

        $obj.wrap(bl);
        bl.hover(function() {
            bl.activate();
        }, function() {
            bl.deactivate();
        });
    });
};

 
 ///// 
/////
cellular.jEqualheight = function(opts) {
    var o = jQuery.extend({
        "height": true
    }, opts);
    return this.each(function() {
        var $obj = jQuery(this);
        var kids = $obj.find('>*');
        var kheight = 0;

        kids.each(function() {
            var $k = jQuery(this);
            var kh = $k.height();

            if (kh > kheight) {
                kheight = kh;
            }
        });
        kids.css({
            "height": kheight
        });
    });
};
 
 ///// 
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
 
 ///// 
/////
cellular.jScrolli = function(opts) {
    o = $.extend({
        "speed": 500, // Duration of cycle
        "pause": 3000 // Time to pause between cycles
    }, opts);
    /**/
    var fn = {};
    //fn.style = function(){};
    fn.showContent = function($obj) {

    };

    return this.each(function() {
        var $obj = jQuery(this);
        var $i = $obj.find(jQuery($obj.children()));
        var active = o.active ? o.active : $i[0];

        $i.each(function() {
            jQuery(this).hide();
        });

        jQuery(active).fadeToggle(o.speed, function() {
                    var $t = jQuery(this);
                    var next = $t.next();
                    if (next.length === 0) {
                        next = $i[0];
                    }
                    $t.delay(o.pause).fadeToggle(o.speed, function() {
                        $obj.jScrolli({
                            "active": next,
                            "speed": o.speed,
                            "pause": o.pause
                        });
                    });
                });
    });
};
 
 ///// 
/////
cellular.jTabs = function(opts) {
    var o = jQuery.extend({
        "active": 0
    }, opts);

    var fn = {};
    fn.style = function($obj) {
        //Add element to display content
        $obj.addClass(cellular.opts.cclass)
                .append('<div class="panel" />');
    };
    fn.showContent = function(li) {
        //Content
        var c = li.find('.content');
        //Display
        var pan = li.parent().find('.panel');

        li.activate();
        pan.html(c.html());
    };

    return this.each(function() {
        var $obj = jQuery(this);
        var tab = $obj.find('> li');

        fn.style($obj);
        //Add classes/functions to each panel
        tab.addClass('tab')
                .each(function() {
                    var li = jQuery(this);
                    var con = li.children();

                    li.kidWrap();
                    //Set 1st child as title
                    li.children().eq(0).addClass('title')
                            .click(function() {
                                fn.showContent(li);
                            });
                    //Set 2nd child as content
                    li.children().eq(1).addClass('content')
                            .hide();
                });

        //Set default content
        fn.showContent(tab.eq([o.active]));
    });
};

 
 ///// 
jQuery.fn.extend(cellular);
 
 ///// 
//Drupal.behaviors.cellular = {
//attach: function (context, settings) {
}
};
 
 ///// 
})(jQuery);