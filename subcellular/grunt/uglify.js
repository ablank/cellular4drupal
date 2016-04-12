/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  options: {
    compress: true,
    beautify: false,
    preserveComments: false,
    wrap: true
            // screwIE8: true
  },
  build: {
    files: {
      'js/script.js': ['js/script.js'],
      'js/plugins.js': ['js/plugins.js'],
      'js/jquery.cellular-ui.js': ['js/jquery.cellular-ui.js']
    }
  }
};
