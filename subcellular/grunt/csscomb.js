/**
 * @file
 * Configure grunt cssComb.
 */

module.exports = {
  options: {
    config: 'config/csscomb.json'
  },
  css: {
<<<<<<< HEAD
    expand: true,
    cwd: 'src/css',
    src: ['**/*.css'],
    dest: 'src/css'
=======
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
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
  }
};
