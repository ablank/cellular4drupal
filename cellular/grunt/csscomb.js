/**
 * @file
 * Configure grunt cssComb.
 */

module.exports = {
  options: {
    config: 'config/csscomb.json'
  },
  css: {
    expand: true,
    cwd: 'buildtest/css',
    src: ['**/*.css'],
    dest: 'buildtest/css'
  }
};
