/**
 * @file
 * Custom javascript for use in your theme.
 */

(function ($) {
  Drupal.behaviors.theme = {
    attach: function (context, settings) {

      $('a[href^=tel]').each(function () {
        var num = $(this).attr('href').match(/\d+/g);

        $(this).attr('href', 'tel:' + num.join(''));
      });

      /* End Drupal.behaviors.theme */
    }
  };
})(jQuery);
