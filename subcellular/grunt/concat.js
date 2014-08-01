module.exports = {
    options: {
        separator: '\n \n ///// \n',
    },
    prod: {
        src: [
            'js/init.js',
            'js/functions.js',
            'js/close.js'
        ],
        dest: 'js/concatScript.js',
    },
};