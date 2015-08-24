/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */

module.exports = {
  cellularUI: {
    options: {
      banner: '/**\n\
* @file\n\
* CellularUI Javascript Library\n\
* \n\
* @author Adam Blankenship <i.adambear@gmail.com>\n\\n\
* \n\
* @see http://live-cellular.gotpantheon.com/cellular-ui\n\
*/\n',
      separator: '\n\n // :)\n',
      language: {
        rmSpace: true
      }
    },
    src: [
      'js/cellular-ui/src/init/jquery.init.js',
      'js/cellular-ui/src/init/drupal.init.js',
      'js/cellular-ui/src/init/cellular.init.js',
      'js/cellular-ui/src/cellular.functions.js',
      'js/cellular-ui/src/cellular.jAccordion.js',
      'js/cellular-ui/src/cellular.jBlocklink.js',
      'js/cellular-ui/src/cellular.jEqualheight.js',
      'js/cellular-ui/src/cellular.jMmenu.js',
      'js/cellular-ui/src/cellular.jScrolli.js',
      'js/cellular-ui/src/cellular.jTabs.js',
      //'js/cellular-ui/src/cellular.jFormal.js',
      //'js/cellular-ui/src/dev/cellular.jParallax.js',
      //'js/cellular-ui/src/dev/cellular.jScrolltrigger.js',
      //'js/cellular-ui/src/dev/cellular.jSticky.js',
      //'js/cellular-ui/src/dev/cellular.jStickyheader.js',
      'js/cellular-ui/src/init/cellular.end.js',
      'js/cellular-ui/src/init/drupal.end.js',
      'js/cellular-ui/src/init/jquery.end.js'
    ],
    dest: 'js/cellular-ui/jquery.cellular-ui.js'
  },
  template: {
    options: {
      banner: '/**\n\
 * @file\n\
 * SubCellular Starter Theme for Drupal 7.\n\
 *\n\
 * @author Adam Blankenship\n\
 * \n\
 * @see http://live-cellular.gotpantheon.com\n\
 * @see https://github.com/ablank/cellular\n\
 */\n\n',
      language: {
        type: 'php'
      }
    },
    src: [
      // 'preprocess/*.inc',
      'preprocess/_init.inc',
      'preprocess/css_alter.inc',
      'preprocess/js_alter.inc',
      'preprocess/preprocess.inc',
    ],
    dest: 'template.php'
  }
};
