/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  front: {
    options: {
      url: 'http://dev/drupal7',//'http://localhost:90/drupal7/',
      width: 1400,
      height: 900,
      filename: 'css/style.css',
      outputfile: 'css/critical-front.css'
    }
  },
  standard: {
    options: {
      url: 'http://dev/drupal7/content/abluo', //'http://localhost:90/drupal7/node/120',
      width: 1400,
      height: 900,
      filename: 'css/style.css',
      outputfile: 'css/critical.css'
    }
  }
};
