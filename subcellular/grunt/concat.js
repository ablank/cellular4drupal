/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */
module.exports = {
<<<<<<< HEAD
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
=======
  cellularUI: {
    src: [
      'js/cellularUI/src/init/jquery.init.js',
      'js/cellularUI/src/init/drupal.init.js',
      'js/cellularUI/src/init/cellular.init.js',
      'js/cellularUI/src/cellular.functions.js',
      'js/cellularUI/src/cellular.jAccordion.js',
      'js/cellularUI/src/cellular.jBlocklink.js',
      //'js/cellularUI/src/cellular.jCarousel.js',
      //'js/cellularUI/src/cellular.jEqualheight.js',
      'js/cellularUI/src/cellular.jFormal.js',
      'js/cellularUI/src/cellular.jMmenu.js',
      //'js/cellularUI/src/cellular.jParallax.js',
      'js/cellularUI/src/cellular.jScrolli.js',
      //'js/cellularUI/src/cellular.jScrolltrigger.js',
      //'js/cellularUI/src/cellular.jSticky.js',
      //'js/cellularUI/src/cellular.jStickyheader.js',
      'js/cellularUI/src/cellular.jTabs.js',
      'js/cellularUI/src/init/cellular.end.js',
      'js/cellularUI/src/init/drupal.end.js',
      'js/cellularUI/src/init/jquery.end.js'
    ],
    dest: 'js/jquery.cellularUI.js',
    options: {
      banner: '/**\n\
* @file\n\
* CellularUI Javascript Library\n\
* \n\
* @author Adam Blankenship\n\\n\
* \n\
* @see http://live-cellular.gotpantheon.com/cellular-ui\n\
* @see https://github.com/ablank/cellularUI\n\
*/\n',
      separator: '\n\n // :)\n'
    }
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
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
