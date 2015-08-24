/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  prod: {
    files: {
      "css/tidy.css": ['test/*.htm','test/*.html']
    }
  }
};
