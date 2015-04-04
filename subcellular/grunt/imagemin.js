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
        cwd: 'src/assets/',
        src: ['**/*.jpg'],
        dest: 'buildtest/assets/'
      }
    ]
  },
  png: {
    files: [
      {
        expand: true,
        cwd: 'src/assets/',
        src: ['**/*.png'],
        dest: 'buildtest/assets/'
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
