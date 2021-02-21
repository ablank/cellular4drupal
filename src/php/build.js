const concat = require('concat'),
fs = require('fs'),
path = require('path');
const { forEach } = require('lodash');


var build = [],
files = [
    'alter.inc', 
    'preprocess.inc', 
    'settings.inc'
];

files.forEach(function(filename){
    build.push(path.join(__dirname, filename));
});

concat(build, path.join(__dirname, 'test.php'));