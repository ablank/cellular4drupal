/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  build: {
    expand: true,
    cwd: 'css',
    src: ['*.css'],
    dest: 'css/',
    ext: '.min.css'
  }
};
