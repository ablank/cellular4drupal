/**
 * @file
 * Custom javascript for use in your theme.
 */
(function(a){Drupal.behaviors.cellular_user = {attach:function(b, c){var d = 'input[type="checkbox"], input[type="radio"]'; /* Check for checkboxes/radios without labels & add if necessary */
  jQuery(d).once(d, function(){var b = a(this); if (b.attr("type") === "checkbox" || "radio"){if (b.next("label").length < 1 && typeof b.attr("id") !== "undefined"){var c = a('<label for="' + b.attr("id") + '" />').css({padding:"0.15em", "vertical-align":"top"}); b.after(c)}}var d = a('label[for="repeat-settings-fieldset"]'), e = d.prev().find("label"); d.prev().nextAll().wrapAll('<div class="daterepeat" />'); a(".daterepeat").hide(); e.on("click", function(){a(".daterepeat").slideToggle()})})}}})(jQuery);