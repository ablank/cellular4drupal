/**
 * @file
 * Configure grunt uglify.
 */

module.exports = {
  build: {
    options: {
      beautify: true,
      mangle: {
        reserved: ["$"],
      },
      output: {
        comments: false,
      },
    },
    files: [
      {
        expand: true,
        cwd: "src/js",
        src: "*.js",
        dest: "js",
      },
    ],
  },
  dist: {
    options: {
      compress: true,
      mangle: {
        reserved: ["$"],
      },
      output: {
        comments: false,
      },
      /*
    annotations: true,
    arguments: true,
    arrows: true,
    assignments: true,
    awaits: true,
    booleans: true,
    collapse_vars: true,
    comparisons: true,
    conditionals: true,
    dead_code: true,
    default_values: true,
    directives: true,
    drop_console: false,
    drop_debugger: true,
    evaluate: true,
    expression: false,
    functions: true,
    global_defs: false,
    hoist_exports: true,
    hoist_funs: false,
    hoist_props: true,
    hoist_vars: false,
    ie: false,
    if_return: true,
    imports: true,
    inline: true,
    join_vars: true,
    keep_fargs: undefined,
    keep_fnames: false,
    keep_infinity: false,
    loops: true,
    merge_vars: true,
    module: false,
    negate_iife: true,
    objects: true,
    optional_chains: true,
    passes: 1,
    properties: true,
    pure_funcs: null,
    pure_getters: 'strict',
    reduce_funcs: true,
    reduce_vars: true,
    rests: true,
    sequences: true,
    side_effects: true,
    spreads: true,
    strings: true,
    switches: true,
    templates: true,
    top_retain: null,
    toplevel: false,
    typeofs: true,
    unsafe: false,
    unsafe_comps: false,
    unsafe_Function: false,
    unsafe_math: false,
    unsafe_proto: false,
    unsafe_regexp: false,
    unsafe_undefined: false,
    unused: true,
    varify: true,
    webkit: false,
    yields: true
      */
    },
    files: [
      {
        expand: true,
        cwd: "src/js",
        src: "*.js",
        dest: "js",
      },
    ],
  },
};
