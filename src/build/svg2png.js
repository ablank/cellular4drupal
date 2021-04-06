const _ = require('lodash');
const fs = require('fs');
const svg2png = require("svg2png");

const directories = ['src/assets/icons/svg/'];
const destination = 'dist/assets/icons/png/';

_.each(directories, directory => {
  fs.readdir(directory, (err, files) => {
    _.each(files, (file) => {
      const name = file.replace(/.svg/g, '');
      console.log(file);
      fs.readFile(file, (e, data) => {
        svg2png(data)
        .then((data) => {
          fs.writeFile(`${destination}${name}`, data);
        })
        .catch(e => console.error(e));
      });
    });
  });
});
