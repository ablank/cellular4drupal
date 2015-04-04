/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  watch: ['watch'],
  // Production Build.
  build: [
    'compass',
    'concat',
    'uglify',
    'imagemin'
    // 'svg2png'
  ],
  // Test Build.
  buildtest: [
    'compass',
    'concat',
    'uglify',
    'newer:imagemin'
    // 'svg2png'
  ],
  style: [
    'compass',
    'newer:imagemin',
    'autoprefixer',
    'csscomb'
  ]
};
