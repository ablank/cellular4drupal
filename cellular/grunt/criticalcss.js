/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  front: {
    options: {
      url: 'http://localhost/sitename', // Index page to test.
      width: 1400,
      height: 900,
      filename: 'css/style.css',
      outputfile: 'css/critical-front.css'
    }
  },
  standard: {
    options: {
      url: 'http://localhost/sitename/page', // Standard page to test.
      width: 1400,
      height: 900,
      filename: 'css/style.css',
      outputfile: 'css/critical.css'
    }
  }
};
