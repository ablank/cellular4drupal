/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  javascript: {
    files: ['src/js/**/*'],
    tasks: [
      'concat',
      'jshint'
    ],
    options: {
      interrupt: false
    }
  },
  stylesheets: {
    files: ['src/sass/**/*'],
    tasks: ['compass', 'px_to_rem']
  }
};
