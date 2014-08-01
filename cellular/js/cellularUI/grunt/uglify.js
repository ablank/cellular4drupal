module.exports = {
    prod: {
        options: {
            mangle: true,
            beautify: false,
            preserveComments: 'some',
            compress: true,
            expand: true,
        },
        files: {
            'jquery.cellular.min.js': ['jquery.cellular.js'],
        },
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
        files: {
            'jquery.cellular.js': ['jquery.cellular.js'],
        }
    }
};

