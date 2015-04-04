/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */

module.exports = {
<<<<<<< HEAD
  themetemplatephp: {
=======
  cellularUI: {
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
      separator: '\n\n // :)\n',
    },
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
    dest: 'js/jquery.cellularUI.js'
  },
  template: {
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
    options: {
      banner: '/**\n\
 * @file\n\
 * Cellular Base Theme for Drupal 7.\n\
 *\n\
 * @author Adam Blankenship\n\
 * \n\
<<<<<<< HEAD
 * @see https://github.com/ablank/cellular\n\
 * @see http://live-cellular.gotpantheon.com\n\
 */\n\n',
      language: {
=======
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
      'preprocess/fn.inc',
      'preprocess/fn.css.inc',
      'preprocess/fn.menu.inc',
      'preprocess/fn.js.inc',
      'preprocess/fn.jquery.inc',
      'preprocess/fn.menu.inc',
      'preprocess/fn.preprocess.inc',
      'preprocess/alter.inc',
      'preprocess/css_alter.inc',
      'preprocess/form_alter.inc',
      'preprocess/js_alter.inc',
      'preprocess/js_plugins.inc',
      'preprocess/preprocess.inc',
      'preprocess/theme.inc',
      'preprocess/theme_form.inc',
      'preprocess/theme_pager.inc',
      'preprocess/social.inc',
      'preprocess/process.inc',
      'preprocess/views.inc'
    ],
    dest: 'template.php'
  },
  theme_settings: {
    options: {
      banner: '/**\n\
 * @file\n\
 * \n\
 * Cellular Theme Settings\n\
 */\n',
      language: {
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
        type: 'php',
        rmClose: true,
        rmSpace: true
      }
    },
<<<<<<< HEAD
    src: [// 'src/preprocess/*.inc'
      'src/preprocess/_init.inc',
      'src/preprocess/fn.inc',
      'src/preprocess/fn.css.inc',
      'src/preprocess/fn.menu.inc',
      'src/preprocess/fn.js.inc',
      'src/preprocess/fn.jquery.inc',
      'src/preprocess/fn.menu.inc',
      'src/preprocess/fn.preprocess.inc',
      'src/preprocess/alter.inc',
      'src/preprocess/css_alter.inc',
      'src/preprocess/form_alter.inc',
      'src/preprocess/js_alter.inc',
      'src/preprocess/js_plugins.inc',
      'src/preprocess/preprocess.inc',
      'src/preprocess/theme.inc',
      'src/preprocess/theme_form.inc',
      'src/preprocess/theme_pager.inc',
      'src/preprocess/social.inc',
      'src/preprocess/process.inc',
      'src/preprocess/views.inc'
    ],
    dest: 'template.php'
  },
  theme_settings: {
    options: {
      banner: '/**\n\
 * @file\n\
 * \n\
 * Cellular Theme Settings\n\
 */\n',
      language: {
        type: 'php',
        rmClose: true,
        rmSpace: true
      }
    },
    src: [
      'src/preprocess/theme-settings/_init_theme-settings.inc',
      'src/preprocess/theme-settings/meta.inc',
      'src/preprocess/theme-settings/markup.inc',
      'src/preprocess/theme-settings/style.inc',
      'src/preprocess/theme-settings/js.inc',
      'src/preprocess/theme-settings/social.inc',
      'src/preprocess/theme-settings/_end_theme-settings.inc'
    ],
    dest: 'theme-settings.php'
=======
    src: [
      'preprocess/theme-settings/_init_theme-settings.inc',
      'preprocess/theme-settings/meta.inc',
      'preprocess/theme-settings/markup.inc',
      'preprocess/theme-settings/style.inc',
      'preprocess/theme-settings/js.inc',
      'preprocess/theme-settings/social.inc',
      'preprocess/theme-settings/_end_theme-settings.inc'
    ],
    dest: 'test/theme-settings.php'
  },
  html: {
    options: {
      language: {
        type: 'html',
        rmSpace: true,
        rmScript: true,
        //doctype: 'dDoctype',
        opentag: '<hi />>>',
        closetag: '<<</, bye>',
        expand: true
      }
    },
    src: [
      'test/html/**/*.htm',
      'test/html/**/*.html'
    ],
    dest: 'test/test.html'
  },
  xml: {
    options: {
      language: {
        type: 'xml',
        version: '1.0',
        docroot: 'document',
        doctype: '',
        expand: true
      }
    },
    src: [
      'test/xml/**/*.xml'
    ],
    dest: 'test/test.xml'
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
  }
};
