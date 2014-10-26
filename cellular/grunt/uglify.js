/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  prod: {
    options: {
      mangle: true,
      beautify: false,
      preserveComments: 'some',
      compress: true,
      expand: true,
    },
    files: {
      'js/plugin.min.js': ['js/plugin.js'],
      'js/script.min.js': ['js/script.js']
    }
  },
  dev: {
    options: {
      mangle: false,
      beautify: true,
      preserveComments: 'all'
    },
    files: {
      'js/plugin.dev.js': ['js/plugin.js'],
      'js/script.dev.js': ['js/script.js']
    }
  }
};
