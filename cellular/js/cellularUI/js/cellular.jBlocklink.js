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
