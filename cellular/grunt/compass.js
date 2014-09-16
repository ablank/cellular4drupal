/**
 * @file
 * Configure grunt compass.
 */

module.exports = {
  dev: {
    options: {
      config: 'config/compass.rb',
      noLineComments: false,
      // clean: false,
      environment: 'development',
      outputStyle: 'expanded' // | nested | compact | compressed
    }
  },
  prod: {
    options: {
      config: 'config/compass.rb',
      noLineComments: true,
      // clean: true,
      environment: 'production',
      outputStyle: 'compressed'
    }
  }
};
