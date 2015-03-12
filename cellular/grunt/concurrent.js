/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  watch: ['watch'],
  // Production
  dist: [
    'concat',
    'compass',
    'autoprefixer',
      // 'uglify:prod'
      // 'svg2png'
    'csscomb',
    'closurecompiler',
    'cssmin',
    'jshint:js'
    //'svgmin',
  ],
  dev: [
    'concat',
    'closurecompiler',
    // 'imagemin',
    'compass',
    'uglify:dev',
    'autoprefixer',
    'csscomb'
  ]
};
