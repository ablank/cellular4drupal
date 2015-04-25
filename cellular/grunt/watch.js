/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  php: {
    files: [
      'preprocess/**/*.inc'
    ],
    tasks: ['concat']
  },
  javascript: {
    files: ['js/**/*.js'],
    tasks: [
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
