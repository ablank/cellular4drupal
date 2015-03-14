/**
 * @file
 * Configure grunt cssComb.
 */

module.exports = {
  options: {
    config: 'config/csscomb.json'
  },
  css: {
    cwd: 'css',
        expand: true,
    src: ['*.css'],
    dest: 'css'
  },
  scss: {
    cwd: 'scss',
        expand: true,
    src: ['*.scss'],
    dest: 'scss'
  }
};
