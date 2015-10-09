/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  php: {
    files: [
      'preprocess/**/*.inc'
    ],
    tasks: [
      'concat:template',
      'concat:theme_settings'
    ]
  },
  javascript: {
    files: ['js/**/*.js'],
    tasks: [
      'concat:cellularUI',
      // 'uglify',
      'jshint'
    ],
    options: {
      interrupt: false
    }
  },
  stylesheets: {
    files: ['sass/**/*.scss'],
    tasks: ['compass']
  }
};
