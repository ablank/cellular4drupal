/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  prod: {
    expand: true,
    cwd: 'buildtest/css',
    src: ['*.css', '!*.min.css'],
    dest: 'buildtest/css',
    ext: '.min.css',
    banner: ''
  }
};
