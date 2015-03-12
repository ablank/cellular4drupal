/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  prod: {
    options: {
      compress: true,
      mangle: true,
      beautify: false,
      preserveComments: 'some',
      wrap: true,
      // screwIE8: true
    },
    files: [{
        expand: true,
        cwd: 'js',
        src: ['*.js'],
        dest: 'js/min'
      }]
  },
  dev: {
    options: {
      compress: false,
      mangle: false,
      beautify: true,
      preserveComments: 'all',
      wrap: true,
      // screwIE8: true
    },
    files: [{
        expand: true,
        cwd: 'js',
        src: [
          '*.js',
            //'!*.min.js'
        ],
        dest: 'js/dev'
      }]
  }
};
