const fs = require('fs');
const path = require('path');
const glob = require('globby');
const autoprefixer = require('autoprefixer');
const postcss = require('postcss');
const precss = require('precss');

fs.readFile('src/app.css', (err, css) => {
  postcss([precss, autoprefixer])
    .process(css, {
      from: 'dest/style.css',
      to: 'dest/style.css'
    })
    .then(result => {
      fs.writeFile('dest/app.css', result.css, () => true)
      if (result.map) {
        fs.writeFile('dest/app.css.map', result.map.toString(), () => true)
      }
    })
})
