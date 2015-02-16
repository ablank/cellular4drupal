/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  scripts: {
    files: ['js/*.js', 'js/**/*.js'],
    tasks: [
      // 'uglify',
      'jshint'
    ],
    options: {
      interrupt: false
    }
  },
  styles: {
    files: ['sass/*.scss', 'sass/**/*.scss'],
    tasks: ['compass:dev']
  }
};
