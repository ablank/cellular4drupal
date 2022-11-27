/**
 * @file
 * Define grunt tasks to run concurrently.
 */

module.exports = {
  // Prep files for further processing.
  dist: ["concat", "compass", "svg2png"],
};
