module.exports = {
    scripts: {
        files: 'js/*.js',
        tasks: ['concat', 'uglify:dev'],
        options: {
            interrupt: true,
        },
    },
};