/**
 * @file
 * Custom javascript for use in your theme.
 */

(function ($, Drupal) {
  Drupal.behaviors.cellular = {
    attach: function (context, settings) {
      
      /* Init cellular functions */
      $('a[href^=tel]').each(function () {
        var num = $(this).attr('href').match(/\d+/g);
        $(this).attr('href', 'tel:' + num.join(''));
      });

      /* End cellular functions */
    }
  };
})(jQuery, Drupal);
