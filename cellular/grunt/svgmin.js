module.exports = {
    options: { // Configuration that will be passed directly to SVGO
        plugins: [{
            removeViewBox: false
            }, {
            removeUselessStrokeAndFill: true
            }, {
            convertPathData: {
                straightCurves: false // advanced SVGO plugin option
            }
            }]
    },
    images: { // Dictionary of files
        expand: true, // Enable dynamic expansion.
        cwd: 'assets/images/svg', // Src matches are relative to this path.
        src: ['*.svg'], // Actual pattern(s) to match.
        dest: '/assets/images/svg/', // Destination path prefix.
        ext: '.svg' // Dest filepaths will have this extension.
    },
    icons: { // Dictionary of files
        expand: true, // Enable dynamic expansion.
        cwd: 'assets/icons/svg', // Src matches are relative to this path.
        src: ['*.svg', '**/*.svg'], // Actual pattern(s) to match.
        dest: '/assets/icons/svg/', // Destination path prefix.
        ext: '.svg' // Dest filepaths will have this extension.
    }
};