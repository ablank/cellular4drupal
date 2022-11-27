/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  build: {
    options: {
      compress: false,
      mangle: false,
      beautify: true,
      preserveComments: true,
        // screwIE8: true

    },
    files: [{
      expand: true,
      cwd: 'src/js',
      src: '*.js',
      dest: 'js'
    }]
  },
  dist: {
    options: {
      compress:true,
      preserveComments: false,
      mangle: {
        reserved: ['$', 'Drupal']
      }
        // screwIE8: true
    },
    files: [{
      expand: true,
      cwd: 'src/js',
      src: '*.js',
      dest: 'js'
    }]
  }
};
