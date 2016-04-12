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
    files: [{
        expand: true,
        cwd: 'js',
        src: ['*.js'],
        dest: 'js/'
      }]
  }
};
