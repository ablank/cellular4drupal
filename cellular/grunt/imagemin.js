/**
 * @file
 * Configure grunt imagemin.
 */

module.exports = {
  options: {
    cache: false
  },
  buildtest: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/',
        src: ['**/*.{svg,png}'],
        dest: 'buildtest/assets/'
      }
    ]
  }
};
