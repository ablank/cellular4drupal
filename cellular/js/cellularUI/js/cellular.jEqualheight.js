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