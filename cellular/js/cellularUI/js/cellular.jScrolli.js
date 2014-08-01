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

        jQuery(active).fadeIn(o.speed, function() {
                    var $t = jQuery(this);
                    var next = $t.next();
                    if (next.length === 0) {
                        next = $i[0];
                    }
                    $t.delay(o.pause).fadeOut(o.speed, function() {
                        $obj.jScrolli({
                            "active": next,
                            "speed": o.speed,
                            "pause": o.pause
                        });
                    });
                });
    });
};