module.exports = {
    options: {// Configuration that will be passed directly to SVGO
        plugins: [{
                removeViewBox: false
            }, {
                removeUselessStrokeAndFill: false
            }, {
                convertPathData: {
                    straightCurves: false // advanced SVGO plugin option
                }
            }]
    },
    files: {
        images: [{// Dictionary of files
                expand: true, // Enable dynamic expansion.
                cwd: 'assets/images/svg/', // Src matches are relative to this path.
                src: ['*.svg'], // Actual pattern(s) to match.
                dest: 'assets/images/svg/min/', // Destination path prefix.
                ext: '.svg' // Dest filepaths will have this extension.
                        // ie: optimise img/_in/branding/logo.svg and store it in img/branding/logo.min.svg
            }],
        icons: [{// Dictionary of files
                expand: true, // Enable dynamic expansion.
                cwd: 'assets/icons/svg/', // Src matches are relative to this path.
                src: ['*.svg'], // Actual pattern(s) to match.
                dest: 'assets/icons/svg/min/', // Destination path prefix.
                ext: '.svg' // Dest filepaths will have this extension.
                        // ie: optimise img/_in/branding/logo.svg and store it in img/branding/logo.min.svg
            }]
    }
};