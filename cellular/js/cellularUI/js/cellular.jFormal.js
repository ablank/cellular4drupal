cellular.jFormal = function(opts) {
    var o = jQuery.extend({
        "inputs": [
            'input[type="text"]',
            'input[type="email"]',
            'input[type="password"]',
            'textarea'
        ],
    }, opts);
    return this.each(function() {
        var $obj = jQuery(this);
        var inputs = o.inputs.join(',');
        // get/set value of inputs
        $(inputs).each(function() {
            var $t = jQuery(this);
            var $v = $t.val();
            $t.live('focus', function() {
                // clear the default value of an input on focus
                if ($t.val() === $v) {
                    $t.val("");
                }
            }).live('blur', function() {
                // reset to default value if no changes were made
                if ($t.val() === "") {
                    $t.val($v);
                }
            });
        });
    });
};