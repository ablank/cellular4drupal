const fs = require('fs');
const path = require('path');
const sharp = require('sharp');

const createDir = (pathname) => {
  try {
    fs.mkdir(pathname, (e) => {
      if (e) {
        console.error(e)
      } else {
        console.log(`\n Creating directory: ${pathname}`)
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

  process.chdir(destination);

  await sharp(path.resolve(imagepath, name))
    .png()
    .toFile(path.resolve(destination, name.replace(/.svg/, '.png')))
    .then((data) => {
      console.log(`${name.replace(/.svg/, '.png')} created`)
    })
    .catch((e) => {
      console.error(e)
    });
};

[path.resolve(__dirname, '..', 'assets', 'icons', 'svg')].forEach((directory) => {
  fs.readdir(directory, (e, files) => {
    files.forEach((svg) => {
      processIcon(directory, svg)
    });
  });
});
