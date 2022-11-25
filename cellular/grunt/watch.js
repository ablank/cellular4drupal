/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  info: {
    files: ['src/info/**/*'],
    tasks: [
      'concat:theme_info'
    ]
  },
  php: {
    files: ['src/preprocess/**/*'],
    tasks: [
      'concat:templatephp',
      'concat:theme_settings'
    ]
  },
  stylesheets: {
    files: ['src/sass/**/*'],
    tasks: [
      'compass',
      'autoprefixer',
      'px_to_rem',
      'csscomb'
        //'cssmin'
    ]
  },
  javascript: {
    files: ['src/js/**/*'],
    tasks: [
      'concat',
      'uglify:build',
      'jshint'
    ],
    options: {
      interrupt: false
    }
  }
};
