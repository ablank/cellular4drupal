/**
 * @file
 * Pull in required grunt modules
 *
 * @param grunt
 */
module.exports = function(grunt) {

// measure the time each task takes
    require('time-grunt')(grunt);

// load grunt config
    require('load-grunt-config')(grunt);

};
