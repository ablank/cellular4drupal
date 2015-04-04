/**
 * @file
 * Configure grunt copy.
 */

module.exports = {
  build: {
    expand: true,
    cwd: 'buildtest',
    src: ['**/*'],
    dest: 'build/',
    //flatten: true,
    filter: 'isFile'
  },
  buildtestcss: {
    expand: true,
    cwd: 'src/css',
    src: ['**/*'],
    dest: 'buildtest/css/',
    //flatten: true,
    filter: 'isFile'
  }
};
