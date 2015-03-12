/**
 * @file
 * Configure grunt concat.
 */

module.exports = {
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
    dest: 'test/js/jquery.cellularUI.js',
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
  }
};
