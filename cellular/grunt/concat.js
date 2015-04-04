/**
 * @file
 * Configure grunt concat.
 *
 * Requires grunt-contrib-concat + .lib/language
 * https://github.com/ablank/grunt-contrib-concat
 */

module.exports = {
  themetemplatephp: {
    options: {
      banner: '/**\n\
 * @file\n\
 * Cellular Base Theme for Drupal 7.\n\
 *\n\
 * @author Adam Blankenship\n\
 * \n\
 * @see https://github.com/ablank/cellular\n\
 * @see http://live-cellular.gotpantheon.com\n\
 */\n\n',
      language: {
        type: 'php',
        rmClose: true,
        rmSpace: true
      }
    },
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
  }
};
