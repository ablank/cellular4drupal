<?php
/**
 * @file
 * Comment template.
 */
/*  Variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: An array of comment items. Use render($content) to print them
 *             all, or print a subset such as render($content['field_example']).
 *             Use hide($content['field_example']) to temporarily suppress the
 *             printing of a given element.
 * - $created: Formatted date and time for when the comment was created.
 *             Reformat by calling format_date() with the desired parameters on
 *             the $comment->created variable in a preprocess function..
 * - $changed: Formatted date and time for when the comment was last changed.
 *             Reformat by calling format_date() with the desired parameters
 *             on the $comment->changed variable in a preprocess function..
 * - $new: New comment marker.
 * - $permalink: Comment permalink.
 * - $submitted: Submission information created from $author & $created during
 *               template_preprocess_comment().
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *            comment-unpublished, comment-published or comment-preview.
 * - $title: Comment title.
 * - $classes: String of classes that can be used to style contextually through
 *             CSS. It can be manipulated through the variable $classes_array
 *             from preprocess functions. Default values can be one or more of:
 *   - comment: The current template type, i.e., "theming hook".
 *   - comment-by-anonymous: Comment by an unregistered user.
 *   - comment-by-node-author: Comment by the author of the parent node.
 *   - comment-preview: When previewing a new or edited comment.
 *   The following applies only to viewers who are registered users:
 *   - comment-unpublished: Unpublished comment visible only to administrators.
 *   - comment-by-viewer: Comment by the user currently viewing the page.
 *   - comment-new: New comment since last the visit.
 * - $title_prefix (array): An array containing additional output populated by
 *              modules, intended to be displayed in front of the main title
 *              tag that appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *              modules, intended to be displayed after the main title tag that
 *              appears in the template.
 *
 * These two variables are provided for context:
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_comment()
 * @see template_process()
 * @see theme_comment()
 */
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php ?>

  <?php print render($title_prefix); ?>
  <h3<?php print $title_attributes; ?>><?php print $title ?></h3>
  <?php print render($title_suffix); ?>

  <div class="post-info">
      <?php print $submitted; ?>
  </div>

  <div<?php print $content_attributes; ?>>
    <?php print render($content); ?>

    <?php if ($signature): ?>
      <div class="user-signature">
        <?php print $signature ?>
      </div>
    <?php endif; ?>
  </div>

  <?php //print render($content['links']); ?>
</div>
