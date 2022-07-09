/**
 * @file
 * Custom javascript for use in your theme.
 */

(function ($) {
  Drupal.behaviors.cellular_user = {
    attach: function (context, settings) {
      var maybeEmptyInput = 'input[type="checkbox"], input[type="radio"]';
      /* Check for checkboxes/radios without labels & add if necessary */
      jQuery(maybeEmptyInput).once(maybeEmptyInput, function () {
        var $t = $(this);
        if ($t.attr('type') === 'checkbox' || 'radio') {
          if ($t.next('label').length < 1 && typeof ($t.attr('id')) !== 'undefined') {
            var $box = $('<label for="' + $t.attr('id') + '" />').css({
              "padding": "0.15em",
              "vertical-align": "top"
            });
            $t.after($box);
          }
        }

        var daterepeat = $('label[for="repeat-settings-fieldset"]'),
          daterepeat_trigger = daterepeat.prev().find('label');

        daterepeat.prev().nextAll().wrapAll('<div class="daterepeat" />');

        $('.daterepeat').hide();

        daterepeat_trigger.on('click', function () {
          $('.daterepeat').slideToggle();
        });
      });

      /*
       'container-inline-date'
       $('.date--fieldset').find();
       */

      /* End Drupal.behaviors.cellular_user */
    }
  };
})(jQuery);
