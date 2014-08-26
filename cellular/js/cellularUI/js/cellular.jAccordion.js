cellular.jAccordion = function (opts) {
    var o = jQuery.extend({
        "active": 0,
        "duration": 500,
        "easing": "swing",
        "single": false
    }, opts);

    var fn = {};

    fn.showContent = function ($li) {

        if (o.single === true) {
            $li.siblings('.active').deactivate()
                .find('.panel').slideUp(o.duration, o.easing);
        }
        else {
            $li.activate()
                .find('.panel').slideToggle(o.duration, o.easing);
        }
    };

    return this.each(function () {
        var $obj = jQuery(this);
        var li = $obj.find('li');
        //fn.style($obj);
        //Add classes/functions to each pane    

        $obj.once('jAccordion', function () {

            $obj.addClass(cellular.opts.cclass);

            li.each(function () {
                var $t = jQuery(this);

                $t.kidWrap();
                $t.children().eq(0).addClass('title');
                $t.children().eq(1).classify([cellular.opts.cclass, 'panel']);
                $t.find('.panel').hide();
                $t.find('.title').click(function (e) {
                    e.preventDefault();
                    fn.showContent($t);
                });
            });
        });

        //Set default content
        fn.showContent($obj.children().eq(o.active));
    });
};
