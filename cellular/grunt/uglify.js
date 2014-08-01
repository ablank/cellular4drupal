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
            'js/plugins/jquery.cellular.min.js': ['js/plugins/jquery.cellular.js'],
            'js/plugins/jquery.form.min.js': ['js/plugins/jquery.form.js'],
            'js/plugins/jquery.masonry.min.js': ['js/plugins/jquery.masonry.js'],
            'js/plugins/prism.min.js': ['js/plugins/prism.js'],
            'js/plugins/d3.min.js': ['js/plugins/d3.js'],
            'js/plugins/three.min.js': ['js/plugins/three.js'],
        },
    },
    dev: {
        options: {
            mangle: false,
            beautify: true,
            preserveComments: 'all'
        },
        files: {
            'js/plugins/jquery.cellular.min.js': ['js/plugins/jquery.cellular.js'],
            'js/plugins/jquery.form.min.js': ['js/plugins/jquery.form.js'],
            'js/plugins/jquery.masonry.min.js': ['js/plugins/jquery.masonry.js'],
            'js/plugins/prism.min.js': ['js/plugins/prism.js'],
            'js/plugins/d3.min.js': ['js/plugins/d3.js'],
            'js/plugins/three.min.js': ['js/plugins/three.js'],
        }
    }
};
