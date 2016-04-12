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
          '**/*.gif',
          '**/*.jpg',
          '**/*.png',
          '**/*.svg'
        ],
        dest: 'assets/images/'
      }
    ]
  },
  icons: {
    files: [
      {
        expand: true,
        cwd: 'assets/icons',
        src: [
          '**/*.gif',
          '**/*.png',
          '**/*.svg'
        ],
        dest: 'assets/icons/'
      }
    ]
  },
  favicons: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/favicons',
        src: [
          '**/*.png',
          '**/*.ico'
        ],
        dest: 'assets/favicons/'
      }
    ]
  }
};
