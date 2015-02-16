/**
 * @file
 * Configure grunt svgmin.
 */

module.exports = {
  images: {
    expand: true,
    cwd: 'assets/images/svg/',
    src: ['*.svg'],
    dest: 'assets/images/min/svg/',
    ext: '.svg'
  },
  icons: {
    expand: true,
    cwd: 'assets/icons/svg/',
    src: ['*.svg'],
    dest: 'assets/icons/min/svg/',
    ext: '.svg'
  }
};
