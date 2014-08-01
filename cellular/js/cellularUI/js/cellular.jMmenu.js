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
                    li.show();
                } else {
                    li.hide();
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