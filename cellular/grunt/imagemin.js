module.exports = {
    options: {
        cache: false,
    },
    images: {
        files: [{
                expand: true,
                cwd: 'assets/images',
                src: ['*.{png,jpg,gif,svg}', '**/*.{png,jpg,gif,svg}'],
                dest: 'assets/images'
            }]
    }
};