cellular.jParallax = function(opts) {
var o = jQuery.extend({
speed: .1
}, opts);
        var fn = {};
        var fn.parallax = function($obj) {
        var winY = jQuery(window).scrollTop();
                var bg = split(parseInt($obj.css('background-position', ' ')));
                var bgPos = bg[0] + 'px ' + bg[1] + ((winY * ( - o.speed))) + 'px';
                $obj.css('background-position', bgPos);
        }

return this.each(function() {
var $obj = jQuery(this);
}
$(window).scroll(fn.parallax);
});
}
