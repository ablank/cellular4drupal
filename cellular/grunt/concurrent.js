/**
 * @file
 * Define grunt tasks to run concurrently..
 */

module.exports = {
  watch: ['watch'],
  prod1: [
    'compass:prod',
    'imagemin',
    'svgmin'
            // 'concat',
  ],
  prod2: [
    'uglify:prod'
            // 'grunticon',
            // 'svg2png',
  ],
  prod3: [
    'jshint'
  ],
  // prod4: [],
  dev1: [
    // 'newer:concat',
    'compass:dev'
  ],
  dev2: [
    'newer:uglify:dev'
  ],
  dev3: [
    'newer:svg2png',
    'newer:jshint'
    // 'grunticon'
  ]
  // dev4: [],
};
