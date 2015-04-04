/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  prod: {
    expand: true,
<<<<<<< HEAD
    cwd: 'buildtest/css',
    src: ['*.css', '!*.min.css'],
    dest: 'buildtest/css',
=======
    cwd: 'css',
    src: ['*.css', '!*.min.css'],
    dest: 'css',
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
    ext: '.min.css',
    banner: ''
  }
};
