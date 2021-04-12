const fs = require('fs');
const path = require('path');
const sharp = require('sharp');
const { replace } = require('lodash');

const src = [path.resolve('src', 'assets', 'icons', 'svg')];

<<<<<<< Updated upstream
const process = async (imagepath, name) => {
  const destination = path.resolve('dist', 'assets', 'icons', 'png', name.replace(/.svg/, '.png'));
 // const destination = name.replace('.svg', '.png');

 console.log(`Imagepath: ${imagepath}`);
 console.log(`Name: ${name}`);
 console.log(`Destination: ${destination}`);
 
  await sharp(path.resolve(imagepath, name))
    .toFile(destination)
    .then((info) => {
      console.log(info);
    })
    .catch((e) => {
      console.error(e);
    });
};
=======
async function process(dir, svg) {
  // console.log(`\nFull Path: ${dir}${svg}`);
  // console.log(`\nName: ${name}`);
  const input = `${dir}${svg}`;
  await fs.readFile(input, processSharp(input));
}
process().catch((error) => {
  console.error(error)
});

function processSharp(input) {
  console.log(destination, input.replace(/.svg/g, '.png'));
  sharp(input)
    //.png()
    .toFile(path.resolve(destination, input.replace(/.svg/g, '.png')))
    .catch((error) => {
      console.error(error)
    });
}
>>>>>>> Stashed changes

src.forEach((directory) => {
  fs.readdir(directory, (e, files) => {
    files.forEach((svg) => {
      process(directory, svg);
    });
  });
});
