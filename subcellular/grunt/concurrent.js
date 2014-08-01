module.exports = {
    watch: ['watch'],
    
    prod1: ['compass:prod', 'newer:imagemin'],
    prod2: ['newer:jshint', 'newer:svgmin' ],
    prod3: ['uglify:prod', 'newer:svg2png'],
    prod4: ['grunticon'],

    dev1: ['compass:dev', 'newer:imagemin'],
    dev2: ['newer:uglify:dev','newer:svgmin'],
    dev3: ['newer:svg2png'],
    dev4: ['grunticon'],
};