/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  build: {
    options: {
      compress: false,
      beautify: false,
      preserveComments: true,
      screwIE8: false,
      wrap: false
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
      compress: {
        //https://github.com/mishoo/UglifyJS2#compressor-options
        unused: true,
        evaluate: true,
        sequences: true,
        properties: true,
        drop_debugger: true,
        conditionals: true,
        comparisons: true,
        booleans: true,
        hoist_funs: true,
        cascade: false,
        collapse_vars: true,
        warnings: true,
        negate_iife: false,
        drop_console: true,
        keep_fargs: false,
        keep_fnames: false
      },
      beautify: false,
      preserveComments: false,
      wrap: true
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