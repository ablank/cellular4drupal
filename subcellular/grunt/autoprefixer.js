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
<<<<<<< HEAD
    cwd: 'src/css',
    src: '**/*.css',
    dest: 'buildtest/css'
=======
    cwd: 'css',
    src: '*.css',
    dest: 'css'
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
  }
};
