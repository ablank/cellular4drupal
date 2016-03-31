/**
 * @file
 * Configure grunt cssComb.
 */

module.exports = {
  options: {
    config: 'grunt/config/csscomb.json'
  },
  all: {
    expand: true,
    cwd: 'css',
    src: ['**/*.css', '!**/*.min.css'],
    dest: 'css/'
  }
};
