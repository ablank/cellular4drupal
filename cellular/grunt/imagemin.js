/**
 * @file
 * Configure grunt imagemin.
 */

module.exports = {
  options: {
    cache: false
  },
  images: {
    files: [
      {
        expand: true,
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
      }
    ]
  },
  icons: {
    files: [
      {
        expand: true,
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
      }
    ]
  }
};
