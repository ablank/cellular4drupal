/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
<<<<<<< HEAD
  buildtest: {
    options: {
      compress: true,
      mangle: true,
      beautify: false,
      preserveComments: 'some',
      wrap: true
      // screwIE8: true
    },
    files: [{
      'buildtest/js/script.min.js': [ 
        'buildtest/js/jquery.cellularUI.js',
        'buildtest/js/plugins.js',
        'buildtest/js/script.js'
      ]
      }]
  },
  prettybuildtest: {
=======
  dev: {
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
    options: {
      compress: false,
      mangle: false,
      beautify: true,
      preserveComments: 'all',
      wrap: true
      // screwIE8: true
    },
    files: [{
<<<<<<< HEAD
      'buildtest/js/jquery.cellularUI.js': 'src/js/CellularUI/jquery.cellularUI.js',
      'buildtest/js/plugins.js': 'src/js/plugins.js',
      'buildtest/js/script.js': 'src/js/script.js'
=======
        expand: true,
        cwd: 'js',
        src: ['**/*.js', '!**/*.min.js', '!**/CellularUI/**', '!**/dev/**'],
        dest: 'js/dev'
>>>>>>> 4c489d9f146a4f8d4141b82e7832038e24d68893
      }]
  }
};
