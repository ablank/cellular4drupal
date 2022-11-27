(function($) {
    Drupal.behaviors.theme = {
        attach: function(context, settings) {
            $("a[href^=tel]").each(function() {
                var num = $(this).attr("href").match(/\d+/g);
                $(this).attr("href", "tel:" + num.join(""));
            });
        }
    };
})(jQuery);