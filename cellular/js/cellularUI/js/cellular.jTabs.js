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
