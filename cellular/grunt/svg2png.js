/**
 * @file
 * Configure grunt svg2png.
 */

module.exports = {
  icons: {
    files: [
      {
        cwd: 'src/assets/icons/svg/',
        src: ['**/*.svg'],
        dest: 'src/assets/icons/png/'
      }
    ]
  },
  images: {
    files: [
      {
        cwd: 'src/assets/images/svg/',
        src: ['**/*.svg'],
        dest: 'src/assets/images/png/'
      }
    ]
  }
};
