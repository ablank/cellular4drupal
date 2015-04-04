/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
<<<<<<< HEAD
  php: {
    files: ['src/preprocess/**/*.inc'],
    tasks: ['concat']
=======

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
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
  }
};
