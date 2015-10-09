/**
 * jFormal: Improve form interaction
 */

cellular.jFormal = function (opts) {
  var o = jQuery.extend({
    inputs: [
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
      var $t = jQuery(this),
      hold = holder = $t.attr('placeholder');
      $t.on('focus', function () {
        holder = '';
        if (this.value === this.defaultValue) {
          this.value = '';
        }
      }).on('blur', function () {
        // Reset to default value if no changes were made.
        holder = hold;
        if (this.value === '' || null) {
          this.value = this.defaultValue;
        }
      });
    });
  });
};
