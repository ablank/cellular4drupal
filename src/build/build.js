const fs = require('fs');
const path = require('path');
const glob = require('globby');
const autoprefixer = require('autoprefixer');
const postcss = require('postcss');
const precss = require('precss');

fs.readFile('dist/style.css', (err, css) => {
  postcss([precss, autoprefixer])
    .process(css, {
      from: 'dist/style.css',
      to: 'dist/style.css'
    })
    .then(result => {
      console.log(result);
      fs.writeFile('dist/style.css', result.css, () => true)
      if (result.map) {
        fs.writeFile('dist/style.css.map', result.map.toString(), () => true)
      }
    })
})
