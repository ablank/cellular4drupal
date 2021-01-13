/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */

module.exports = {
  theme_info: {
    src: [
      'src/info/info.txt',
      'src/info/opts.txt'
    ],
    dest: 'cellular.info'
  },
  templatephp: {
    options: {
      banner: '/**\n\
    * @file\n\
    * Cellular Base Theme for Drupal 7.\n\
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
      'src/preprocess/_init.inc',
      'src/preprocess/alter.inc',
      'src/preprocess/alter_css.inc',
      'src/preprocess/alter_js.inc',
      'src/preprocess/preprocess_html.inc',
      'src/preprocess/preprocess_hooks.inc',
    ],
    dest: 'template.php'
  },
  cellularUI: {
    options: {
      banner: '/**\n\
* @file\n\
* CellularUI Javascript Library\n\
* \n\
* @author Adam Blankenship <i.adambear@gmail.com>\n\
* \n\
* @see http://live-cellular.gotpantheon.com/cellular-ui\n\
*/\n',
      language: {
        rmSpace: true
      }
    },
    src: [
      /**
       * Init Objects
       */
      'src/js/cellular-ui/init/jquery.init.js',
      'src/js/cellular-ui/init/drupal.init.js',
      'src/js/cellular-ui/init/cellular.init.js',
      /**
       * Components
       */
      'src/js/cellular-ui/functions.js',
      'src/js/cellular-ui/cellular.body.js',
      'src/js/cellular-ui/cellular.jAccordion.js',
      'src/js/cellular-ui/cellular.jCard.js',
      'src/js/cellular-ui/cellular.jFormal.js',
      'src/js/cellular-ui/cellular.jMmenu.js',
      'src/js/cellular-ui/cellular.jScrolli.js',
      'src/js/cellular-ui/cellular.jSocial.js',
      'src/js/cellular-ui/cellular.jTabs.js',
      /**
       * Under Development...
       */
      //'src/js/cellular-ui/dev/cellular.jAV.js',
      //'src/js/cellular-ui/dev/cellular.jModal.js',
      //'src/js/cellular-ui/dev/cellular.jZoom.js',
      //'src/js/cellular-ui/dev/cellular.jParallax.js',
      //'src/js/cellular-ui/dev/cellular.jScrollindicator.js',
      //'src/js/cellular-ui/dev/cellular.jScrolltrigger.js',
      //'src/js/cellular-ui/dev/cellular.jSticky.js',
      //'src/js/cellular-ui/dev/cellular.jTooltip.js',

      /**
       * Close objects
       */
      'src/js/cellular-ui/init/cellular.end.js',
      'src/js/cellular-ui/init/drupal.end.js',
      'src/js/cellular-ui/init/jquery.end.js'
    ],
    dest: 'src/js/jquery.cellular-ui.js'
  },
};
