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
        cwd: 'src/assets/images',
        src: [
          'gif/**/*.gif',
          'jpg/**/*.jpg',
          'png/**/*.png',
          'svg/**/*.svg'
        ],
        dest: 'assets/images'
      }
    ]
  },
  icons: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/icons',
        src: [
          'png/**/*.png',
          'svg/**/*.svg'
        ],
        dest: 'assets/icons'
      }
    ]
  },
  favicons: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/favicons',
        src: [
          'png/**/*.png',
          'svg/**/*.ico'
        ],
        dest: 'assets/favicons'
      }
    ]
  }
};
