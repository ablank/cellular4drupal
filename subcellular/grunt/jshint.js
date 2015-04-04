/**
 * @file
 * Configure grunt jshint.
 */

module.exports = {
  options: {
    force: true,
    curly: true,
    eqeqeq: true,
    eqnull: true,
    browser: true,
    globals: {
      jQuery: true
    }
  },
  build: [
    'build/js/**/*.js',
    '!**/*.min.js'
  ]
  ,
  buildtest: [
    'buildtest/js/**/*.js',
    '!**/*.min.js'
  ]
};
