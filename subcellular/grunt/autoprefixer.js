/**
 * @file
 * Configure grunt autoprefixr.
 */

module.exports = {
  all: {
    expand: true,
    flatten: true,
    cwd: "src/css",
    src: "*.css",
    dest: "css/",
  },
};
