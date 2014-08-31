<?php
/**
 * @file
 * Theme the more link rendered by views.
 */
/* - $view: The view object.
 * - $more_url: the url for the more link.
 * - $link_text: the text for the more link.
 * @ingroup views_templates
 */

?>

<a href="<?php print $more_url ?>"
   class="button more-link"><?php print $link_text; ?></a>
