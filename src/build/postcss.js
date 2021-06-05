const config = require('./postcss.config');
const fs = require('fs');
const path = require('path');
const glob = require('glob');
const postcss = require('postcss');
const autoprefixer = require('autoprefixer')(config.plugins.autoprefixer);
const cssnano = require('cssnano')(config.plugins.cssnano);
const stylelint = require('stylelint')(config.plugins.stylelint);
const sort = require('postcss-sorting')(config.plugins.sorting);
const reporter = require('postcss-reporter')(config.plugins.reporter);

const src = path.resolve(__dirname, '..', '..', 'dist', 'css');

const err = (e, callback) => {
  if (e) {
    console.error(`\nEROR: ${e}\n`);
  } else {
    callback();
  }
};
/*
 fs.readFile('src/app.css', (err, css) => {
  postcss([precss, autoprefixer])
    .process(css, { from: 'src/app.css', to: 'dest/app.css' })
    .then(result => {
      fs.writeFile('dest/app.css', result.css, () => true)
      if ( result.map ) {
        fs.writeFile('dest/app.css.map', result.map.toString(), () => true)
      }
    })
}) 
*/
const mincss = async (asset) => {
  const srcFile = `${path.resolve(src, asset)}`;
  const distFile = `${path.resolve(src, asset.replace(/.css/, '.min.css'))}`;

  console.log(`Minifying ${asset}`);

  try {
    await fs.readFile(srcFile, (error, css) => {
      postcss([cssnano])
        .process(css, {
          from: srcFile,
        })
        .then((result) => {
          fs.writeFile(distFile, result.css, () => true);
          if (result.map) {
            fs.writeFile(`${distFile}.map`, result.map.toString(), () => true);
          }
        });
    });
  } catch (e) {
    err(e);
  }
};

const processCss = async (asset) => {

  console.log(`Processing ${asset}`);

  const srcFile = `${path.resolve(src, asset)}`;
  await fs.readFile(srcFile, (err, css) => {
    postcss([autoprefixer, sort, reporter])
      .process(css, {
        from: srcFile,
      })
      .then((result) => {
        fs.writeFile(srcFile, result.css, () => true);
        if (result.map) {
          fs.writeFile(`${srcFile}.map`, result.map.toString(), () => true);
        }
      })
      .then(mincss(asset))
      .catch((e) => err(e));
  });
};

glob(
  '**/*.css', {
    cwd: src,
    noext: 'min.css',
  },
  (e, files) => {
    err(e, () => {
      files.forEach((stylesheet) => {
        processCss(stylesheet);
      });
    });
  },
);
