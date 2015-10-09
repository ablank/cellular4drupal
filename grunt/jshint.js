/**
 * @file
 * Configure grunt jshint.
 */

module.exports = {
  options: {
    curly: true,
    eqeqeq: true,
    eqnull: true,
    browser: true,
    globals: {
      jQuery: true
    }
  },
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

};
