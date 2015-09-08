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
      'preprocess/fn.form.inc',
      'preprocess/fn.js.inc',
      'preprocess/fn.menu.inc',
      'preprocess/fn.preprocess.inc',
      'preprocess/jquery.inc',
      'preprocess/plugin_js.inc',
      'preprocess/plugin_css.inc',
      'preprocess/alter.inc',
      'preprocess/alter_css.inc',
      'preprocess/alter_js.inc',
      'preprocess/alter_form.inc',
      'preprocess/preprocess.inc',
      'preprocess/preprocess_page.inc',
      'preprocess/theme.inc',
      'preprocess/theme_form.inc',
      'preprocess/theme_pager.inc',
      'preprocess/panels.inc',
      'preprocess/social.inc',
      'preprocess/views.inc',
      'preprocess/process.inc'
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
      'preprocess/theme-settings/jquery_settings.inc',
      'preprocess/theme-settings/js.inc',
      'preprocess/theme-settings/social.inc',
      'preprocess/theme-settings/views_default.inc',
      'preprocess/theme-settings/_end_theme-settings.inc'
    ],
    dest: 'theme-settings.php'
  }
};
