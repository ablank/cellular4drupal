module.exports = {
    watch: ['watch'],
    prod1: [
        'compass:prod',
        'concat',
        'svgmin'
    ],
    prod2: [
        //'jshint',
        //'grunticon',
        //'svg2png',        
    ],
    prod3: [
        'uglify:prod'
    ],
    // prod4: [],

    dev1: [
        'concat',
        'compass:dev',
        'svgmin',
                //'imagemin'
    ],
    dev2: [
        'newer:uglify:dev',
    ],
    dev3: [
        'svg2png',
                //'grunticon'
    ],
    // dev4: [],
};