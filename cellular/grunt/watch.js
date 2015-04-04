/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
  php: {
    files: ['src/preprocess/**/*.inc'],
    tasks: ['concat']
  }
};
