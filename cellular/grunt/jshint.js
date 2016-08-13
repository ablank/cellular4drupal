/**
 * @file
 * Configure grunt jshint.
 */

module.exports = {
  options: {
    browser: true,
    curly: true,
    eqeqeq: true,
    eqnull: true,
    force: true,
    globals: {
      jQuery: true
    },
    undef: true,
    unused: true
  },
  js: [
    'src/js/*.js'
  ],
  cellularUI: [
    'src/js/cellular-ui/jquery.cellular-ui.js'
  ]
};
