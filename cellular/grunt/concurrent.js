/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  watch: ['watch'],
  // Production
  dist1: [
    'compass',
    'concat',
    'imagemin'
    // 'svg2png'
  ],
  dist2: [
    'autoprefixer',
    'closurecompiler'
    // 'svgmin'
  ],
  dist3: [
    'csscomb'
  ],
  dist4: [
    'jshint:js',
    'cssmin'
  ],
  dev1: [
    'compass',
    // 'concat',
    'imagemin:newer'
  ],
  dev2: [
    'uglify',
    'autoprefixer'
  ],
  dev3: [
    'csscomb'
  ],
  dev4: []
};
