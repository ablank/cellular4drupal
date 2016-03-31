/**
 * @file
 * Language formatting & selective content inclusion.
 *
 * @author Adam Blankenship
 * @copyright 2015 Adam Blankenship
 * @license GPL2 License
 */

'use strict';
exports.init = function (grunt) {
  // var util = require('util');
  var exports = {};

  exports.openTag = function (options) {
    var tag = '';

    if (options.opentag) {
      tag = options.opentag;
    }
    if (!options.opentag) {

      if (options.type === 'html') {
        var doctype = options.doctype ? options.doctype : '<!DOCTYPE html>';
        tag = '\n' + doctype + '<html>\n<body>';
      }

      if (options.type === 'php') {
        tag = '<?php';
      }

      if (options.type === 'xml') {
        // <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
        options.version = options.version ? options.version : '1.0';
        options.encoding = options.encoding ? options.encoding : 'UTF-8';
        options.standalone = options.doctype ? ' ' + 'no' : 'yes';

        // <!DOCTYPE root_element SYSTEM "DTD_location">
        options.doctype = options.doctype ? ' SYSTEM "' + options.doctype + '"' : ' []';
        options.docroot = options.docroot ? options.docroot : 'document';

        tag = '<?xml version="' + options.version +
          '" encoding="' + options.version +
          '" standalone="' + options.standalone + '" ?>\n';
        tag += '<!DOCTYPE ' + options.docroot + options.doctype + '>';
      }
    }
    if (tag !== '') {
      tag = tag + '\n';
    }

    grunt.log.writeln('Process as ' + options.type);

    return tag;
  };


  exports.closeTag = function (options) {
    var tag = '';

    if (options.closetag) {
      tag = options.closetag;
    }

    if (!options.closetag) {

      if (options.type === 'html') {
        tag = '</body>\n</html>';
      }
      if (options.type === 'php' && options.closetag === true) {
        tag = '?>\n';
      }
    }
    if (tag !== '') {
      tag = '\n' + tag;
    }

    return tag;
  };

  exports.format = function (filepath, src, options) {
    if (!options) {
      return src;
    }
    var nichts = [];

    grunt.log.writeln('Looking for ' + options.type + ' tags in ' + filepath);

    if (options.type === 'html') {
      src = src.match(/<body[^>]*>((.|[\n\r])*)<\/body>/im)[1];
      if (options.rmScript === true) {
        src = src.replace(/<script[^>]*>((.|[\n\r])*)<\/script>/igm, '');
      }
    }
    else {
      if (options.type === 'php') {
        // <?php ?>
        nichts.push('(\\<\\?php\\s)');
        if (options.rmClose !== false) {
          nichts.push('(\\s\\?\\>)');
        }
        // Replace docblock file comments
        src = src.replace(/^\/\*\*\s{2,}\W\s\@file/gm, '/*\n * @see file: ' + filepath);
      }
      if (options.type === 'xml') {
        // <?xml?>
        nichts.push('(\\<\\?xml.*)');
        nichts.push('(\\<\\!DOCTYPE.*)');
      }
    }

    if (options.expand === true) {
      src = src.replace(/\>+/g, '\>\n');
    }
    if (options.rmSpace === true) {
      src = src.replace(/([\r\n])+/gm, '\n');
      //src = src.replace(/ {2,}/g, ' ');
      nichts.push('((^\\s+)|(\\s+$))');
    }

    // Flatten array to single regex & remove content
    src = src.replace(new RegExp('(?:' + nichts.join('|') + ')', 'igm'), '');

    // grunt.log.writeln(util.inspect(renix, false, null));
    return src;
  };

  return exports;
};
