/**
 * @file
 * Configure grunt cssComb.
 */

module.exports = {
  options: {
    config: 'config/csscomb.json'
  },
  all: {
    expand: true,
    cwd: 'css',
    src: ['*.css'],
    dest: 'css'
  }
};
