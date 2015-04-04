/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */
module.exports = {
  templatephp: {
    options: {
      language: {
        type: 'php',
        rmClose: true,
        rmSpace: true
      }
    },
    src: [
      "src/preprocess/alter.css.inc",
      "src/preprocess/alter.js.inc"
    ],
    dest: 'template.php'
  },
  ui: {
    options: {
      language: {
        rmClose: true,
        rmSpace: true
      }
    },
    src: [
      'src/js/CellularUI/src/js/init/jquery.init.js',
      'src/js/CellularUI/src/js/init/drupal.init.js',
      'src/js/CellularUI/src/js/init/cellular.init.js',
      'src/js/CellularUI/src/js/cellular.functions.js',
      'src/js/CellularUI/src/js/cellular.jAccordion.js',
      'src/js/CellularUI/src/js/cellular.jBlocklink.js',
      //'src/js/CellularUI/src/js/cellular.jCarousel.js',
      //'src/js/CellularUI/src/js/cellular.jEqualheight.js',
      'src/js/CellularUI/src/js/cellular.jFormal.js',
      'src/js/CellularUI/src/js/cellular.jMmenu.js',
      //'src/js/CellularUI/src/js/cellular.jParallax.js',
      'src/js/CellularUI/src/js/cellular.jScrolli.js',
      //'src/js/CellularUI/src/js/cellular.jScrolltrigger.js',
      //'src/js/CellularUI/src/js/cellular.jSticky.js',
      //'src/js/CellularUI/src/js/cellular.jStickyheader.js',
      'src/js/CellularUI/src/js/cellular.jTabs.js',
      'src/js/CellularUI/src/js/init/cellular.end.js',
      'src/js/CellularUI/src/js/init/drupal.end.js',
      'src/js/CellularUI/src/js/init/jquery.end.js'
    ],
    dest: 'buildtest/js/jquery.cellularUI.js'
  }
};

/*
 var path = function (grunt) {
 var path = {
 "template": "src/preprocess",
 "ui": "src/js/CellularUI/src/js/"
 }

 return path;
 };*/
/*
 var path = {
 "template": "src/preprocess/",
 "ui": "src/js/CellularUI/src/js/"
 };
 console.log('<%= path.template %>');
 */
