module.exports = {
    watch: ['watch'],
    prod1: [
        'compass:prod',
        'concat',
        'imagemin'
    ],
    prod2: [
        //'jshint',
        //'svgmin'
    ],
    prod3: [
        'uglify:prod',
                //'svg2png',
                //'grunticon'
    ],
    // prod4: [],

    dev1: [
        'concat',
        'compass:dev',
        'newer:imagemin'
    ],
    dev2: [
        'newer:uglify:dev',
        'newer:svgmin'
    ],
    dev3: [
        //'newer:svg2png',
        //'grunticon'
    ],
    // dev4: [],
};