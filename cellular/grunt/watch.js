module.exports = {
    scripts: {
        files: 'js/*.js',
        tasks: [
            //'jshint',
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