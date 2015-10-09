/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  base: {
    expand: true,
    cwd: 'css',
    src: ['*.css', '!*.min.css'],
    dest: 'css',
    ext: '.min.css',
    banner: ''
  },
  jquery_ui: {
    expand: true,
    cwd: 'css/jquery-ui',
    src: ['*.css', '!*.min.css'],
    dest: 'css/jquery-ui',
    ext: '.min.css',
    banner: ''
  }
};
