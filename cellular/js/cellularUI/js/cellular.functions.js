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
