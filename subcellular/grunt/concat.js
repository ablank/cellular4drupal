/**
 * @file
 * Configure grunt concat
 */

module.exports = {
    options: {
        banner: '/**\n' +
            '* @file\n' +
            '* Javascript\n' +
            '* \n' +
            '* @author \n' +
            '*/\n',
        separator: '\n\n // :)\n',
    },
    script: {
        src: [
            'js/script1.js',
            'js/script2.js',
            'js/etc.js',
        ],
        dest: 'js/concat.js',
    },
};
