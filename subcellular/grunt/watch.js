module.exports = {
    scripts: {
        files: ['js/**/*.js'],
        tasks: [
            //'jshint',
            //'concat',
            'uglify:dev'
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