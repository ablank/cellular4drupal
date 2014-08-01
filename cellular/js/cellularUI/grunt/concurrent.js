module.exports = {
    watch: ['watch'],
    prod1: ['concat'],
    prod2: ['uglify:prod'],
    prod3: ['jshint:prod'],
    dev1: ['concat'],
    dev2: [
        //'uglify:dev'
    ],
    dev3: ['jshint:dev'],
};