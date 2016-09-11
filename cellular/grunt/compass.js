/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  compile: {
    options: {
      config: 'grunt/config/compass.rb'
    }
  },
  dist: {
    raw: "http_path = '/'; css_dir = 'src/css'; sass_dir = 'src/sass'; images_dir = 'assets/images'; javascripts_dir = 'js'; output_style = :compressed;"
  }
};
