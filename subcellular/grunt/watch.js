/**
 * @file
 * Configure grunt watch.
 */

module.exports = {
    scripts: {
        files: ['js/*.js', 'js/**/*.js'],
        tasks: [
            'uglify',
            'jshint'
        ],
        options: {
            interrupt: true,
        }
    },
    styles: {
        files: ['sass/*.scss', 'sass/**/*.scss'],
        tasks: ['compass:dev']
    }
};
