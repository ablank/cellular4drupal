module.exports = {
    watch: ['watch'],
    /////
    prod1: [
            'compass:prod',
            'jshint'
           ],
    prod2: [
            'svgmin',
           'imagemin'
       ],
    prod3: [
            'uglify:prod', 
            'svg2png'
           ],
    prod4: [
        //'grunticon'
        ],
    
    /////
    dev1: [
            'compass:dev'
          ],
    dev2: [
            'newer:svgmin',
            'newer:uglify:dev'
          ],
    dev3: [
            'newer:svg2png'
          ],
    dev4: [
            //'grunticon'
            ],
};