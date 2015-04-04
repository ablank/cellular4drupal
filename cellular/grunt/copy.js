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
  }
};
