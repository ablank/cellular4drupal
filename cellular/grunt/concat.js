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
      // 'src/preprocess/*.inc',
      'src/preprocess/_init.inc',
      'src/preprocess/fn.inc',
      'src/preprocess/fn.css.inc',
      'src/preprocess/fn.form.inc',
      'src/preprocess/fn.js.inc',
      'src/preprocess/fn.menu.inc',
      'src/preprocess/fn.preprocess.inc',
      'src/preprocess/jquery.inc',
      'src/preprocess/plugin_js.inc',
      'src/preprocess/plugin_css.inc',
      'src/preprocess/alter.inc',
      'src/preprocess/alter_css.inc',
      'src/preprocess/alter_js.inc',
      'src/preprocess/alter_form.inc',
      'src/preprocess/preprocess_html.inc',
      'src/preprocess/preprocess_node.inc',
      'src/preprocess/preprocess_page.inc',
      'src/preprocess/preprocess_block.inc',
      'src/preprocess/preprocess_comments.inc',
      'src/preprocess/theme.inc',
      'src/preprocess/theme_form.inc',
      'src/preprocess/theme_pager.inc',
      'src/preprocess/panels.inc',
      'src/preprocess/social.inc',
      'src/preprocess/views.inc',
      'src/preprocess/process.inc'
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
      'src/preprocess/theme-settings/_config.inc',
      'src/preprocess/theme-settings/meta.inc',
      'src/preprocess/theme-settings/markup.inc',
      'src/preprocess/theme-settings/style.inc',
      'src/preprocess/theme-settings/js.inc',
      'src/preprocess/theme-settings/social.inc',
      'src/preprocess/theme-settings/_end_theme-settings.inc'
    ],
    dest: 'theme-settings.php'
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
      'src/js/cellular-ui/init/jquery.init.js',
      'src/js/cellular-ui/init/drupal.init.js',
      'src/js/cellular-ui/init/cellular.init.js',
      'src/js/cellular-ui/functions.js',
      'src/js/cellular-ui/state.js',
      'src/js/cellular-ui/cellular.jAccordion.js',
      'src/js/cellular-ui/cellular.jCard.js',
      'src/js/cellular-ui/cellular.jEqualheight.js',
      'src/js/cellular-ui/cellular.jMmenu.js',
      //'src/js/cellular-ui/cellular.jModal.js',
      'src/js/cellular-ui/cellular.jScrolli.js',
      'src/js/cellular-ui/cellular.jSocial.js',
      'src/js/cellular-ui/cellular.jTabs.js',
      'src/js/cellular-ui/cellular.jTooltip.js',
      //'src/js/cellular-ui/cellular.jZoom.js',
      //'src/js/cellular-ui/cellular.jFormal.js',
      //'src/js/cellular-ui/dev/cellular.jParallax.js',
      //'src/js/cellular-ui/dev/cellular.jScrolltrigger.js',
      //'src/js/cellular-ui/dev/cellular.jSticky.js',
      'src/js/cellular-ui/init/cellular.end.js',
      'src/js/cellular-ui/init/drupal.end.js',
      'src/js/cellular-ui/init/jquery.end.js'
    ],
    dest: 'src/js/jquery.cellular-ui.js'
  },
  /*
   lib: {
   src: [
   //'src/js/lib/jquery-1.11.1.js',
   //'src/js/lib/jquery.once.js',
   //'src/js/lib/jquery.migrate.js',
   //'src/js/lib/plugins/jquery.backstretch.js',
   //'src/js/lib/plugins/jquery.flowtype.js',
   //'src/js/lib/plugins/jquery.freetile.js',
   //'src/js/lib/plugins/jquery.parallax.js',
   //'src/js/lib/plugins/jquery.smoove.js',
   //'src/js/lib/plugins/prism.js',
   //'src/js/lib/plugins/snap.svg.js',
   ],
   dest: 'js/lib.js'
   },
   */
};
