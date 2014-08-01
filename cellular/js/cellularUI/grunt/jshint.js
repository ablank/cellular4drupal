module.exports = {
    options: {
        force: true,
        curly: true,
        eqeqeq: true,
        eqnull: true,
        browser: true,
        globals: {
            jQuery: true
        },
    },
    prod: ['jquery.cellular.min.js'],
    dev: ['jquery.cellular.js']

};