module.exports = {
    options: {
        defaultWidth: '32px',
        defaultHeight: '32px',
        pngfolder: 'png',
        template: 'grunt/templates/icon-template.hbs'
    },
    prod: {
        options: {
            datasvgcss: 'icons-svg-data.css',
            datapngcss: 'icons-png-data.css',
            urlpngcss: 'icons-png.css'
        },
        files: [{
                expand: true,
                cwd: 'assets/icons/svg/',
                src: ['*.svg'],
                dest: 'grunt/grunticons/'
            }]
    }
};
