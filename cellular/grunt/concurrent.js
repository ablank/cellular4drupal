/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  // Prep files for further processing.
  prep: [
    'concat',
    'compass'
  ]
};
