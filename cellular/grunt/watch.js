/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  php: {
    files: [
      'node_modules/grunt-contrib-concat/**/*.js',
      'preprocess/**/*.inc'
    ],
    tasks: ['concat:php']
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
    files: ['sass/*.scss', 'sass/**/*.scss'],
    tasks: ['compass']
  }
};
