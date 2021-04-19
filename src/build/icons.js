const fs = require('fs');
const path = require('path');
const sharp = require('sharp');

const createDir = (pathname) => {
  try {
    fs.mkdir(pathname, {
      recursive: true
    }, (e) => {
      if (e) {
        console.error(e)
      } else {
        process.chdir(pathname)
        console.log(`\ndestination: ${pathname}`)
      }
    });
  } catch (e) {
    console.error(e)
  }
};

const processIcon = async (imagepath, name) => {
  const destination = path.resolve(__dirname, '..', '..', 'dist', 'assets', 'icons', 'png')

  if (!fs.existsSync(destination)) {
    await createDir(destination);
  }
  
    await sharp(path.resolve(imagepath, name))
      .png()
      .toFile(path.resolve(destination, name.replace(/.svg/, '.png')))
      .then((info) => {
        console.log(info)
      })
      .catch((e) => {
        console.error(e)
      });
      
};

[path.resolve(__dirname, '..', 'assets', 'icons', 'svg')].forEach((directory) => {
  //console.log(directory);
  fs.readdir(directory, (e, files) => {
    files.forEach((svg) => {
      processIcon(directory, svg)
    });
  });
});
