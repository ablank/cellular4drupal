/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  all: {
    expand: true,
    flatten: true,
    cwd: 'css',
    src: '**/*.css',
    dest: 'css'
  }
};
