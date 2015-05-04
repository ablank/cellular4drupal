/**
 * @file
 * Configure grunt imagemin.
 */

module.exports = {
  options: {
    cache: false
  },
  gif: {
    files: [
      {
        expand: true,
        cwd: 'assets/images',
        src: [
          'gif/**/*.gif'
        ],
        dest: '/assets/images/min/gif'
      }
    ]
  },
  jpg: {
    files: [
      {
        expand: true,
        cwd: 'assets/images',
        src: [
          'jpg/**/*.[jpg, jpeg]'
        ],
        dest: '/assets/images/min/jpg'
      }
    ]
  },
  png: {
    files: [
      {
        expand: true,
        cwd: 'assets/images',
        src: [
          'png/**/*.png'
        ],
        dest: '/assets/images/min/png'
      }
    ]
  },
  svg: {
    files: [
      {
        expand: true,
        cwd: 'assets/images',
        src: [
          'svg/**/*.svg'
        ],
        dest: '/assets/images/min/svg'
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
        dest: '/assets/icons/min/'
      }
    ]
  }
};
