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
    cwd: 'src/css',
    src: ['**/*.css'],
    dest: 'src/css'
  }
};
