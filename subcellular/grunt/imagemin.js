/**
 * @file
 * Configure grunt imagemin.
 */

module.exports = {
  options: {
    cache: false
  },
  jpg: {
    files: [
      {
        expand: true,
<<<<<<< HEAD
        cwd: 'src/assets/',
        src: ['**/*.jpg'],
        dest: 'buildtest/assets/'
=======
        cwd: 'assets/images',
        src: ['**/*.{gif, jpg, png}', '!**/min/**'],
        dest: './assets/images/min/'
      }
    ]
  },
  images_svg: {
    files: [
      {
        expand: true,
        cwd: 'assets/images',
        src: ['**/*.svg', '!**/min/**'],
        dest: './assets/images/min/'
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
      }
    ]
  },
  png: {
    files: [
      {
        expand: true,
<<<<<<< HEAD
        cwd: 'src/assets/',
        src: ['**/*.png'],
        dest: 'buildtest/assets/'
=======
        cwd: 'assets/icons',
        src: ['**/*.png', '!**/min/**'],
        dest: './assets/icons/min/'
      }
    ]
  },
  icons_svg: {
    files: [
      {
        expand: true,
        cwd: 'assets/icons',
        src: ['**/*.svg', '!**/min/**'],
        dest: './assets/icons/min/'
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
      }
    ]
  },
  svg: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/',
        src: ['**/*.svg'],
        dest: 'buildtest/assets/'
      }
    ]
  },

};
