/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  dev: {
    options: {
      config: 'config/compass.rb',
      environment: 'development',
      outputStyle: 'expanded',
      noLineComments: false,
      trace: true
    }
  },
  prod: {
    options: {
      config: 'config/compass.rb',
      environment: 'production',
      outputStyle: 'compressed',
      noLineComments: true,
      trace: true
    }
  }
};