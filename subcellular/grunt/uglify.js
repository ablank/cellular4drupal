module.exports = {
    prod: {
        options: {
            mangle: true,
            beautify: false,
            preserveComments: 'some',
            compress: true,
        },
        files: [{
                expand: true,
                cwd: 'js/',
                src: ['**/*.js'],
                dest: 'js/min/'
            }, ]
    },
    dev: {
        options: {
            mangle: false,
            beautify: true,
            mangle: false,
                    beautify: true,
                    preserveComments: 'all',
            comments: 'all'
        },
        files: [{
                expand: true,
                cwd: 'js/',
                src: ['**/*.js'],
                dest: 'js/dev/'
            }]
    }
};
