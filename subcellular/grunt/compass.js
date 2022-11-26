/**
 * @file
 * Configure grunt compass.
 *
 * OutputStyle: expanded | nested | compact | compressed
 */

module.exports = {
  compile: {
    options: {
      config: 'grunt/config/compass.rb'
    }
  },
  dist: {
    options: {
      config: 'grunt/config/compass.dist.rb'
    }
  }
};
