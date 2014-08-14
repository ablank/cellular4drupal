/////
cellular.jBlocklink = function(opts) {
    var o = jQuery.extend({
        "cclass": "jBlocklink",
    }, opts);

    return this.each(function() {
        var $obj = jQuery(this);

        $obj.once(o.cclass, function() {
            var a = $obj.find('a').eq(0);
            var ahref = a.attr('href');

            if (ahref !== undefined) {
                var bl = jQuery('<a href="' + ahref + '" />');
                var classes = [
                    cellular.opts.cclass,
                    o.cclass,
                    a.attr('class') ? a.attr('class') : null
                ];
                bl.classify(classes);
                $obj.wrap(bl)
                        .find('h2, h3').addClass('title');

            }

        });

        $obj.hover(function() {
            jQuery(this).activate();
        }, function() {
            jQuery(this).deactivate();
        });
    });
};
