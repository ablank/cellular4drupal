/**
 * @file
 * Configure grunt svgmin.
 */

module.exports = {
    images: {// Dictionary of files
        expand: true, // Enable dynamic expansion.
        cwd: 'assets/images/svg/',
        src: ['*.svg'], // Actual pattern(s) to match.
        dest: 'assets/images/min/svg/', // Destination path prefix.
        ext: '.svg' // Dest filepaths will have this extension.
    },
    icons: {// Dictionary of files
        expand: true, // Enable dynamic expansion.
        cwd: 'assets/icons/svg/',
        src: ['*.svg'], // Actual pattern(s) to match.
        dest: 'assets/icons/min/svg/', // Destination path prefix.
        ext: '.svg' // Dest filepaths will have this extension.
    }
};
