cellular.jFormal = function (opts) {
  var o = jQuery.extend({
    "inputs": [
      'input[type="text"]',
      'input[type="email"]',
      'input[type="password"]',
      'textarea'
    ]
  }, opts);
  return this.each(function () {
    var inputs = o.inputs.join(',');
    // get/set value of inputs
    jQuery(inputs).each(function () {
      var $t = jQuery(this);
      var $v = $t.val();
      $t. on('focus', function () {
            if (this.value == this.defaultValue) {
              this.value = '';
            }
      }).on('blur', function () {
        // Reset to default value if no changes were made.
            if (this.value == '') {
              this.value = this.defaultValue;
            }
      });
    });
  });
};