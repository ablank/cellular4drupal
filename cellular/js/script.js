(function(a,b){/**
 * @file
 * Custom javascript for use in your theme.
 */
(function(a){Drupal.behaviors.theme={attach:function(b,c){a("a[href^=tel]").each(function(){var b=a(this).attr("href").match(/\d+/g);a(this).attr("href","tel:"+b.join(""))})}}})(jQuery);b["true"]=a})({},function(){return this}());