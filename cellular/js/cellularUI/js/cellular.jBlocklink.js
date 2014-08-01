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
