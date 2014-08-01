/////
cellular.jSticky = function(opts) {
    o = jQuery.extend({
        "sspeed": 500,
        "delay": 200
    }, opts);

    var fn = {};

    fn.style = function($obj) {
        $obj.addClass(cellular.opts.cclass);
    };

    fn.update = function($obj, offset, ostyle) {
        var scroll = jQuery(window).scrollTop();

        if (scroll >= offset) {
            $obj.addClass("mini")
                    .css({
                        "position": "absolute",
                        "left": $obj.offset().left
                    })
                    .stop().animate({
                "top": scroll
            })
                    .minimenu();

        } else {
            $obj.removeClass("mini");
            jQuery.each(ostyle, function(prop, value) {
                $obj.css(prop + ": " + value);
            });
        }
    };

    return this.each(function() {
        var $obj = jQuery(this);
        var ostyle = $obj.css(["position", "left", "top", "z-index"]);
        var offset = $obj.offset().top; // - $obj.height();


        fn.style($obj);
        $(window).scroll(function() {
            fn.update($obj, offset, ostyle);
        });
    });
};