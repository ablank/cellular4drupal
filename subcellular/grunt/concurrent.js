/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  watch: ['watch'],
<<<<<<< HEAD
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
=======
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
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
};
