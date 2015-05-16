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
* @see https://github.com/ablank/cellularUI\n\
*/\n',
      separator: '\n\n // :)\n',
      language: {
        rmSpace: true
      }
    },
    src: [
      'js/cellularUI/src/init/jquery.init.js',
      'js/cellularUI/src/init/drupal.init.js',
      'js/cellularUI/src/init/cellular.init.js',
      'js/cellularUI/src/cellular.functions.js',
      'js/cellularUI/src/cellular.jAccordion.js',
      'js/cellularUI/src/cellular.jBlocklink.js',
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
      'preprocess/panels.inc',
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
        type: 'php',
        rmClose: true,
        rmSpace: true
      }
    },
    src: [
      'preprocess/theme-settings/_init_theme-settings.inc',
      'preprocess/theme-settings/meta.inc',
      'preprocess/theme-settings/markup.inc',
      'preprocess/theme-settings/style.inc',
      'preprocess/theme-settings/js.inc',
      'preprocess/theme-settings/social.inc',
      'preprocess/theme-settings/_end_theme-settings.inc'
    ],
    dest: 'theme-settings.php'
  }
};
