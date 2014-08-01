module.exports = {
    options: {
        cache: false,
    },
    images: {
        files: [{
                expand: true,
                cwd: 'assets/images',
                src: ['*.{png,jpg,gif}', '**/*.{png,jpg,gif}'],
                dest: '/assets/images/'
            }]
    }
};