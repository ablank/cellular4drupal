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
    'src/js/*.js'
  ],
  cellularUI: [
    'src/js/cellular-ui/jquery.cellular-ui.js'
  ]
};
