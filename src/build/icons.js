const _ = require('lodash');
const fs = require('fs');
const path = require('path');
const sharp = require('sharp');

const src = [path.resolve('src', 'assets', 'icons', 'svg')];
const destination = path.resolve('dist', 'assets', 'icons', 'png');

async function process(dir, svg) {
  // console.log(`\nFull Path: ${dir}${svg}`);
  // console.log(`\nName: ${name}`);
  const input = `${dir}${svg}`;
  await fs.readFile(input, processSharp(input));
}
process().catch((error) => {console.error(error)});

function processSharp(input) {
  console.log(destination, input.replace(/.svg/g, '.png'));
  sharp(input)
  //.png()
  .toFile(path.resolve(destination, input.replace(/.svg/g, '.png')))
  .catch((error) => { console.error(error) } );
}

src.forEach((directory) => {
  fs.readdir(directory, (e, files) => {
    files.forEach((svg) => {
      process(directory, svg);
    });
  });
});

/**
 * movies.forEach(function(movie) {
  var downloadPath = './img/posters/' + movie.id + '-300x446.jpg';

  fs.stat(downloadPath, function(err, stat) {
    if(err == null) {
      console.log('file exists');
      return;
    }

    download(movie.poster, downloadPath, function(){
      var resizePath = './img/posters/' + movie.id + '-150x223.jpg'; 

      sharp(downloadPath)
       .resize(150, 223)
       .toFile(resizePath, function(err) {
        // output.jpg is a 300 pixels wide and 200 pixels high image
        // containing a scaled and cropped version of input.jpg
       });
    });
  });
});
 */
