/*
 Copyright (c) 2003-2013, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */
/*
 WARNING: clear browser's cache after you modify this file.
 If you don't do this, you may notice that browser is ignoring all your changes.
 */
CKEDITOR.editorConfig = function (a) {
  a.indentClasses = ["rteindent1", "rteindent2", "rteindent3", "rteindent4"];
// [ Left, Center, Right, Justified ]
  a.justifyClasses = ["rteleft", "rtecenter", "rteright", "rtejustify"];
// The minimum editor width, in pixels, when resizing it with the resize handle.
  a.resize_minWidth = 450;
// Protect PHP code tags (<?...?>) so CKEditor will not break them when
// switching from Source to WYSIWYG.
// Uncommenting this line doesn't mean the user will not be able to type PHP
// code in the source. This kind of prevention must be done in the server
// side
// (as does Drupal), so just leave this line as is.
  a.protectedSource.push(/<\?[\s\S]*?\?>/g);// PHP Code
  a.extraPlugins = "";/*
   * Append here extra CSS rules that should be applied into the editing area.
   * Example:
   * config.extraCss = 'body {color:#FF0000;}';
   */
  a.extraCss = "body{min-width: 24em}";/**
   * CKEditor's editing area body ID & class.
   * See http://drupal.ckeditor.com/tricks
   * This setting can be used if CKEditor does not work well with your theme by default.
   */
  a.bodyClass = "";
  a.bodyId = "";/**
   * Sample extraCss code for the "marinelli" theme.
   */
  if (Drupal.settings.ckeditor.theme == "marinelli") {
    a.extraCss += "body{background:#FFF;text-align:left;font-size:0.8em;}";
    a.extraCss += "#primary ol, #primary ul{margin:10px 0 10px 25px;}"
  }/**
   * Sample bodyClass and BodyId for the "marinelli" theme.
   */
  if (Drupal.settings.ckeditor.theme == "marinelli") {
    a.bodyClass = "singlepage";
    a.bodyId = "primary"
  }
};/*
 * Sample toolbars
 */
//Toolbar definition for basic buttons
Drupal.settings.cke_toolbar_DrupalBasic = [["Format", "Bold", "Italic", "-", "NumberedList", "BulletedList", "-", "Link", "Unlink", "Image"]];
//Toolbar definition for Advanced buttons
Drupal.settings.cke_toolbar_DrupalAdvanced = [["Source"],
//['Cut','Copy','Paste','PasteText','PasteFromWord','-','SpellChecker', 'Scayt'],
  ["Undo", "Redo", "Find", "Replace"], ["NumberedList", "BulletedList", "Table", "HorizontalRule", "-", "Image", "SpecialChar"],
//['Maximize', 'ShowBlocks'],
  "/", ["Format", "-", "RemoveFormat"], ["Bold", "Italic", "Underline", "Strike", "Blockquote", "-", "Subscript", "Superscript", "-"],
// ['JustifyLeft','JustifyCenter','JustifyRight','JustifyBlock','-','BidiLtr','BidiRtl'],
  ["Anchor", "LinkToNode", "Link", "Unlink"]];
// Toolbar definition for all buttons
Drupal.settings.cke_toolbar_DrupalFull = [["Source"], ["Cut", "Copy", "Paste", "PasteText", "PasteFromWord", "-", "SpellChecker", "Scayt"], ["Undo", "Redo", "Find", "Replace", "-", "SelectAll"], ["Image", "Flash", "Table", "HorizontalRule", "Smiley", "SpecialChar", "Iframe"], "/", ["Bold", "Italic", "Underline", "Strike", "-", "Subscript", "Superscript", "-", "RemoveFormat"], ["NumberedList", "BulletedList", "-", "Outdent", "Indent", "Blockquote", "CreateDiv"], ["JustifyLeft", "JustifyCenter", "JustifyRight", "JustifyBlock", "-", "BidiLtr", "BidiRtl", "-", "Language"], ["Link", "Unlink", "Anchor", "Linkit", "LinkToNode", "LinkToMenu"], "/", ["Format", "Font", "FontSize"], ["TextColor", "BGColor"], ["Maximize", "ShowBlocks"], ["DrupalBreak", "DrupalPageBreak"]];