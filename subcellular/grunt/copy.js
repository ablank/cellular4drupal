/**
 * @file
 * Configure grunt copy.
 */

module.exports = {
  main: {
    files: [
      // includes files within path
      {
        expand: true,
        cwd: 'src/js',
        src: ['*.js'],
        dest: 'js/'
      },
      {
        expand: true,
        cwd: 'src/assets/icons/jquery-ui',
        src: ['*.gif', '*.png'],
        dest: 'assets/icons/jquery-ui/'
      }
    ]
  }
};
