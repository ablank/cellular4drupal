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
<<<<<<< HEAD
  build: [
    'build/js/**/*.js',
    '!**/*.min.js'
  ]
  ,
  buildtest: [
    'buildtest/js/**/*.js',
    '!**/*.min.js'
  ]
=======
  js: [
    'js/*.js',
    '!js/**/*.min.js',
    'js/cellularUI/jquery.cellularUI.js'
  ]
  ,
  cellularUI: [
    'js/cellularUI/jquery.cellularUI.js',
    'js/cellularUI/src/*.js'
  ]

>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
};
