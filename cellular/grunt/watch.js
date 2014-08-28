/**
 * @file
 * Configure grunt watch
 */

module.exports = {
    scripts: {
        files: ['js/cellularUI/js/*.js'],
        tasks: [
            //'jshint',
            'concat',
            'uglify'
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