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
      // clean: false,
      environment: 'development',
      outputStyle: 'expanded' 
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
