/**
 * @file
 * Configure grunt compass.
 */

module.exports = {
  options: {
    config: 'config/compass.rb',
    sassDir: 'sass',
    cssDir: 'css'
  },
  dev: {
    options: {
      noLineComments: false,
      // clean: false,
      environment: 'development',
      outputStyle: 'expanded' // | nested | compact | compressed
    }
  },
  prod: {
    options: {
      noLineComments: true,
      clean: true,
      environment: 'production',
      outputStyle: 'compressed'
    }
  }
};
