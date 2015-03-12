/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  prod: {
    expand: true,
    cwd: 'css',
    src: ['*.css', '!*.min.css'],
    dest: 'css',
    ext: '.min.css',
    banner: ''
  }
};
