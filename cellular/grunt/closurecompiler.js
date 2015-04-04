/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  all: {
    options: {
      compilation_level: 'SIMPLE_OPTIMIZATIONS' // 'WHITESPACE_ONLY'
    },
    files: {
      'js/script.min.js': ['js/*.js', '!js/*min.js', 'js/cellularUI/jquery.cellularUI.js'] // ['js/plugin.js','js/script.js']
    }
  },
  cellularUI: {
    options: {
      compilation_level: 'SIMPLE_OPTIMIZATIONS' // 'WHITESPACE_ONLY'
    },
    files: {
      'js/cellularUI/jquery.cellularUI.min.js': ['js/cellularUI/jquery.cellularUI.js']
    }
  }
};
