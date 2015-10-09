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
        src: [
          'gif/**/*.gif',
          'jpg/**/*.jpg',
          'png/**/*.png',
          'svg/**/*.svg'
        ]
        ,
        dest: 'assets/images/min/'
      }
    ]
  },
  icons: {
    files: [
      {
        expand: true,
        cwd: 'assets/icons',
        src: [
          'png/**/*.png',
          'svg/**/*.svg'
        ]
        ,
        dest: 'assets/icons/min/'
      }
    ]
  }
};
