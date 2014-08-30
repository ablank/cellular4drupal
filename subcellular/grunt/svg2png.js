/**
 * @file
 * Configure grunt svg2png.
 */

module.exports = {
    images: {
        files: [
            {
                cwd: 'assets/images/svg/',
                src: ['*.svg'],
                dest: 'assets/images/png/',
            }
        ]
    },
    icons: {
        files: [
            {
                cwd: 'assets/icons/svg/',
                src: ['*.svg'],
                dest: 'assets/icons/png/'
            }
        ]
    }
};
