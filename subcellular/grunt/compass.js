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
      noLineComments: false,
        trace: true,
      environment: 'development',
      outputStyle: 'expanded'
    }
  },
  prod: {
    options: {
      config: 'config/compass.rb',
      noLineComments: true,
        trace: true,
      outputStyle: 'expanded'
    }
  }
};
