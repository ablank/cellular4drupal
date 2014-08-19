cellular.jParallax = function(opts) {
    var o = jQuery.extend({
        "speed": .1
    }, opts);
    var fn = {};
    fn.update = function($obj){
       var bg = $obj.css('background-position').split(' ');
       var xPos = bg[0];
       var yPos = parseInt(bg[1]);
       var winY = $(window).scrollTop();

        var bgPos = xPos + ' ' + yPos + (jQuery(window).scrollTop() * (-o.speed)) + 'px';

        console.log(bgPos);

        $obj.css({'background-position': bgPos});

function parallax(){
            var yPos = $(window).scrollTop();
            var bgPos = '-120px ' + ((yPos * (-.1)) -70) + 'px';
$('#app').css('background-position', bgPos);
}
    };

    return this.each(function() {
        var $obj = jQuery(this);

        $obj.addClass(cellular.opts.cclass);

    });
$(window).scroll(jParallax);
};