/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
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
    options: {
      compress: false,
      mangle: false,
      beautify: true,
      preserveComments: 'all',
      wrap: true
      // screwIE8: true
    },
    files: [{
      'buildtest/js/jquery.cellularUI.js': 'src/js/CellularUI/jquery.cellularUI.js',
      'buildtest/js/plugins.js': 'src/js/plugins.js',
      'buildtest/js/script.js': 'src/js/script.js'
      }]
  }
};
