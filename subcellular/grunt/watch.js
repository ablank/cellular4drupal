/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
    scripts: {
        files: ['js/**/*.js'],
        tasks: [
            'uglify'
            'jshint',
        ],
        options: {
            interrupt: true,
        },
    },
    styles: {
        files: 'sass/**/*.scss',
        tasks: ['compass:dev']
    },
};