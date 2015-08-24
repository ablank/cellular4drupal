/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  script: {
    options: {
      compilation_level: 'SIMPLE_OPTIMIZATIONS' // 'WHITESPACE_ONLY'
    },
    files: {
      'js/script.min.js': ['js/script.js']
    }
  },
  plugins: {
    options: {
      compilation_level: 'SIMPLE_OPTIMIZATIONS' // 'WHITESPACE_ONLY'
    },
    files: {
      'js/plugins.min.js': ['js/plugins.js']
    }
  },
  cellularUI: {
    options: {
      compilation_level: 'SIMPLE_OPTIMIZATIONS' // 'WHITESPACE_ONLY'
    },
    files: {
      'js/cellular-ui/jquery.cellular-ui.min.js': ['js/cellular-ui/jquery.cellular-ui.js']
    }
  }
};
