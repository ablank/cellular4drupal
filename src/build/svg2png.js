const _ = require('lodash');
const fs = require('fs');
const svg2png = require("svg2png");
const directories = ['src/assets/icons/svg/'];
const destination = 'dist/assets/icons/png/';

var files = _.each(directories, directory => {
  fs.readdir(directory, (err, files) => {
    /*
     var filenames = filenames => {
     return Promise.all(
     filenames.map(f => fsPromises.readFile(f))
     )
     }

     filenames(files)
     .then(res => )
     .catch(console.log);
     };*/
    _.each(files, file => {
      var name = file.replace(/.svg/g, '');
      console.log(name);

      fs.readFile(file, value => svg2png)
              .then(fs.writeFile('${destination}${name}', buffer))
              .catch(e => console.error(e));
    });
  });
});