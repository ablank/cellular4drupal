/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  dev: {
    options: {
      compress: false,
      mangle: false,
      beautify: true,
      preserveComments: 'all',
      wrap: true
      // screwIE8: true
    },
    files: [{
        expand: true,
        cwd: 'js',
        src: ['**/*.js', '!**/*.min.js', '!**/CellularUI/**', '!**/dev/**'],
        dest: 'js/dev'
      }]
  }
};
