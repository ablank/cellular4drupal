const fs = require('fs');
const path = require('path');
const glob = require('glob');
const sharp = require('sharp');

const src = path.resolve(__dirname, '..', 'assets', 'images');

console.log(`\nSrc: ${src}`);

const err = (error) => {
  console.error(`\nError: ${error}`);
};

const createDir = (pathname) => {
  try {
    fs.mkdir(pathname, (e) => {
      if (e) {
        err(e);
      } else {
        console.log(`\n Creating directory: ${pathname}\n`);
      }
    });
  } catch (e) {
    err(e);
  }
};

const processImage = (image) => {
  console.log(image);
};

glob(
  `**/*.{gif, jpg, jpeg, png}`,
  {
    cwd: src,
  },
  (e, files) => {
    err(e, () => {
      files.forEach((image) => {
        console.log(`\nFiles: ${files}`);
        processImage(image);
      });
    });
  },
);

/*
const processIcon = async (imagepath, name) => {
  const destination = path.resolve(
    __dirname,
    '..',
    '..',
    'dist',
    'assets',
    'icons',
    'png',
  );

  if (!fs.existsSync(destination)) {
    await createDir(destination);
  }

  process.chdir(destination);

  await sharp(path.resolve(imagepath, name))
    .png()
    .toFile(path.resolve(destination, name.replace(/.svg/, '.png')))
    .then((data) => {
      console.log(`${name.replace(/.svg/, '.png')} created`);
    })
    .catch((e) => {
      err(e);
    });
};

*/
